#include "World.h"
#include "GameManager.h"
#include "PlatEngine.h"
#include "../Physics/PhysicsManager.h"
#include "Box2D.h"
#include "Time.h"
#include "Macros.h"

#include "../../Application/TiledMapEditor/TiledMapEditor.h"
#include "../Graphics/Rendering/RenderManager.h"
#include "../Graphics/Rendering/RenderQueue.h"
#include "../Graphics/Camera.h"

#include "../GameObject/GameObject.h"
#include "../GameObject/GameObjectComponents/RenderComponent.h"
#include "../GameObject/GameObjectComponents/TransformComponent.h"
#include "../GameObject/GameObjectComponents/RigidBodyComponent.h"

#include "../GameObject/Player.h"

class RenderComponent;


void World::SpawnCamera()
{
	// Setting up the necessary properties for a functioning camera.
	m_pMainCamera = new Camera(k_windowWidth, k_windowHeight, m_worldWidth, m_worldHeight);
}

World::~World()
{
	ShutDownWorld();
}

void World::ShutDownWorld()
{
	SAFE_DELETE(m_pWorldMap);
	SAFE_DELETE(m_pMainCamera);
	SAFE_DELETE(m_pPlayer);
}

void World::SpawnGameObjectInWorld(GameObject* pGameObject)
{ 
	// PlatEngine spawns an already pre-constructed gameObject into the world,
	// by added it to the list of all gameObjects, and returns the result of its
	// success if it was added it to a renderQueue.
	 m_pAllObjectsInWorld.push_back(pGameObject);

	 bool result = GetRenderManager()->AddGameObjectToRender(pGameObject);
	 
	 if (!result)
		 LOG("ERROR: Failed to spawn GameObject");
}


void World::Update()
{
	//UpdateCamera();
	
	// TODO: Make GameObject.Update() functional!
	// Go through all the game objects in the world
	// If m_isTickable = true than call GameObject.Update();
}

void World::DestoryGameObject(GameObject* pGameObject)
{
	// Search for our object we wish to destroy,
	// destroy it, and remove it from world's existance.
	for (std::vector<GameObject*>::iterator it = m_pAllObjectsInWorld.begin(); it != m_pAllObjectsInWorld.end(); it++)
	{
		if (*it == pGameObject)
		{
			SAFE_DELETE(*it);
			m_pAllObjectsInWorld.erase(it);
			break;
		}
	}
}

RenderManager* World::GetRenderManager()
{
	if (!m_pRenderManager)
	{
		// Returns the renderManager that PlatEngine is running on.
		m_pRenderManager = dynamic_cast<RenderManager*>(PlatEngine::GetEngine()->GetRenderManager());
	}
	return m_pRenderManager;
}

GameObject* World::CreateGameObject(char* renderFile)
{
	GameObject* pNewGameObject = new GameObject();

	// Setting up the renderer
	RenderComponent* renderer = (RenderComponent*)pNewGameObject->GetComponent(ComponentType::k_RendererComponent);
	renderer->SetFileName(renderFile);
	
	return pNewGameObject;
}

GameObject* World::CreateGameObjectWithRigidBody(int x, int y, int w, int h)
{
	GameObject* pNewGameObject = new GameObject();

	// Setting up the transform
	TransformComponent* pTransform = (TransformComponent*)pNewGameObject->GetComponent(ComponentType::k_TransformComponent);
	pTransform->SetX((float)x);
	pTransform->SetY((float)y);
	pTransform->SetHeight((float)h);
	pTransform->SetWidth((float)w);

	// Setting up the rigidBody
	pNewGameObject->AttachComponent(ComponentType::k_RigidBodyComponent);
	RigidBodyComponent* pRigidBody = (RigidBodyComponent*)pNewGameObject->GetComponent(ComponentType::k_RigidBodyComponent);
	pRigidBody->Initialize(this, pTransform, false);
	
	return pNewGameObject;
}

GameObject* World::CreateGameObject(char* renderFile, int x, int y)
{
	GameObject* pNewGameObject = new GameObject();

	// Setting up the renderer
	RenderComponent* renderer = (RenderComponent*)pNewGameObject->GetComponent(ComponentType::k_RendererComponent);
	renderer->SetFileName(renderFile);
	
	// Setting up the transform
	TransformComponent* pTransform = (TransformComponent*)pNewGameObject->GetComponent(ComponentType::k_TransformComponent);
	pTransform->SetX((float)x);
	pTransform->SetY((float)y);

	return pNewGameObject;
}

// Loading the world will parse your TMX map and spawn a camera.
void World::LoadTheWorld(const char* fileName, char* path)
{
	// Spawn a camera ----------------------------------------------------------------------------------------------------
	SpawnCamera();

	// Making sure we have a valid world map.
	if (!m_pWorldMap)
		m_pWorldMap = new TMXMap();

	// LoadMap takes in the file name, and the data map to store its data.
	TiledMapEditor mapEditor;
	bool loadResult = mapEditor.LoadMap(fileName, m_pWorldMap);
	
	if (!loadResult)
		return;

	// Creating a list of RenderComponents that is needed to create the background image
	size_t size = m_pWorldMap->m_layers[0].m_tileCollection.size();
	std::vector<RenderComponent*> renders;
	renders.resize(size, nullptr);

	// Background Tiles -----------------------------------------------------------------------------------------------
	int i = 0;
	for (auto it : m_pWorldMap->m_layers[0].m_tileCollection)
	{
		// A rect to store positions, size, and texture coordinates will be
		// needed to store in a new rendercomponent for the data that is being parsed
		// by TiledMapEditor.
		TMXRect rect;
		RenderComponent* renderer = new RenderComponent();
				
		// Getting the x, y, w, h, and texture UV's of the tile.  
		// Also getting the filename that the texture is using and setting it to the render component
		mapEditor.CalculateSDLCoordinates(rect, m_pWorldMap->m_tileSets[it.m_tilesetIndex], it, m_pWorldMap->m_width);
		const char* sourceFile = &(m_pWorldMap->m_tileSets[it.m_tilesetIndex].m_sourceFile)[0u];
		
		// If a sourceFile is saved on the tiled object, then set the file name on the 
		// renderer and Load up the image now because the data gets flushed.
		if (sourceFile)
		{
			std::string source = std::string(path) + std::string(sourceFile);
			renderer->SetFileName(source.c_str());
			renderer->GetSprite()->LoadImage();
		}
		// extracting the x, y, w, h, tU, tV data to the renderer component
		renderer->m_x = rect.m_posX;
		renderer->m_y = rect.m_posY;
		renderer->m_w = rect.m_width;
		renderer->m_h = rect.m_height;
		renderer->m_textureX = rect.m_textureU;
		renderer->m_textureY = rect.m_textureV;
		
		// Add this RenderCompoment to a list of objects that need to be rendered.
		renders[i] = renderer;
		++i;
	}
	
	// We have finished parsing through all the background tiles and their data,
	// Now the renderQueue will need to know which tiles it will have to be rendering
	// so set the tiles we just worked on.
	GetRenderManager()->GetRenderQueue()->SetTiles(renders);

	// Objects -----------------------------------------------------------------------------------------------------------
	// Tiled can support multiple groups of multiple objects, so for each object in each objectGroup,
	// Create a GameObject that has a rigiBody.  Future updates will support creating overlap triggers,
	// the player itself, hurtful objects, etc.
	for (auto groupIt : m_pWorldMap->m_objectGroups)
	{
		for (auto objectIt : groupIt.m_objects)
		{
			// Creating a gameObject for each object in each group of objects.
			// The objects position and size are something the rigidBody and transformComponent
			// Will need to know, and CreateGameObject, takes of that for you!
			GameObject* pTMXObject = CreateGameObjectWithRigidBody(objectIt.x, objectIt.y, objectIt.width, objectIt.height);
			// In order for the object to be apart of the world, you must explicitly
			// call SpawnGameObjectInWorld with the new GameObject.
			SpawnGameObjectInWorld(pTMXObject);
		}
	}

	// Level data --------------------------------------------------------------------------------------------------------
	// Saving some world "data" which is currently just the size of the world.
	m_worldHeight = m_pWorldMap->m_height * m_pWorldMap->m_tileHeight;
	m_worldWidth = m_pWorldMap->m_width * m_pWorldMap->m_tileWidth;

}

Player* World::CreatePlayer(char* renderFile = nullptr, Player* pPlayer = nullptr)
{
	if (!pPlayer)
	{
		LOG("ERROR: Failed to create a new player!")
		return nullptr;
	}

	GameObject* playerObj = (GameObject*)pPlayer;

	// Setting up the renderer
	// If no render file was specified, there is no need to connect to the RenderComponent.
	if (renderFile)
	{
		RenderComponent* renderer = (RenderComponent*)playerObj->GetComponent(ComponentType::k_RendererComponent);
		renderer->SetFileName(renderFile);
	}

	// InitializePlayer, initializes properties of the player.
	// This is similar to Unity's BeginPlay()
	pPlayer->InitializePlayer(this);

	return pPlayer;
}
