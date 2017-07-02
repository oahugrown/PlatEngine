// World.h

#ifndef WORLD_H
#define WORLD_H
#include <vector>

#ifdef PLATENGINE_EXPORTS
#define WORLD_API __declspec(dllimport) 
#else
#define WORLD_API __declspec(dllexport) 
#endif

class Player;
class RigidBodyComponent;
class Camera;
struct TMXMap;
class GameObject;
class RenderManager;

class World
{

private:
	RenderManager* m_pRenderManager;
	// Spawns a Camera (rect) in the world after the world has been Loaded
	void SpawnCamera();

protected:
	TMXMap* m_pWorldMap;
	Player* m_pPlayer;
	float m_gravityForce;
	int m_worldWidth, m_worldHeight;
	Camera* m_pMainCamera;
	RenderManager* GetRenderManager();

	// A list of all the gameObjects that have been spawned into the world
	std::vector<GameObject*> m_pAllObjectsInWorld;
	
	// Cleans up the World when PlatEngine shuts down.
	void WORLD_API ShutDownWorld();

	// Loads the World by parsing the Tiled Map Editor's file.
	void WORLD_API LoadTheWorld(const char* fileName, char* path);

	// Creates a Player specific GameObject
	virtual WORLD_API Player* CreatePlayer(char* renderFile, Player* pPlayer);

public:
	virtual WORLD_API ~World();
	// A "BeginPlay()" state that meeds to be implemented.  Should be used to
	// LoadTheWorld() and create and spawn gameObjects into the level.
	virtual WORLD_API void InitializeWorld() = 0;
	// The camera position update that gets called every frame.
	virtual WORLD_API void UpdateCamera() = 0;
	// World update to be implemented for tick-able events.
	virtual WORLD_API void Update() = 0;
	
	// PlatEngine's process of how GameObjects get Destroyed in the World.
	// Currently, it removes the item from list of all gameObjects in the world,
	// and deallocates that memory.
	virtual WORLD_API void DestoryGameObject(GameObject* pGameObject);
	// Adds the gameObject to the list of all gameObjects in the world and
	// adds that object to the renderQueue.  PlatEngine will log an error if it
	// was unsuccessful in adding the gameObject to the queue.
	virtual WORLD_API void SpawnGameObjectInWorld(GameObject* pGameObject);
	// Creates and returns a gameObject and takes in a sourceFile for the texture to render.
	// World coordinates will be defaulted to 0, 0
	GameObject* CreateGameObject(char* renderFile);
	// Creates and returns a gameObject and takes in a source while with world coordinates.
	GameObject* CreateGameObject(char* renderFile, int x, int y);
	// Creates and returns a gameObject that has a rigidBodyComponent attached to it.
	// The position and size of the object gets set to both the Transform
	// and RigidBody components.
	GameObject* CreateGameObjectWithRigidBody(int x, int y, int w, int h);

	// Getters/Setters
	virtual float GetGravity() const { return m_gravityForce; };
	virtual std::vector<GameObject*> GetAllGameObjects() const { return m_pAllObjectsInWorld; };
	virtual void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; };
	virtual Player* GetPlayer() const { return m_pPlayer; };
	const virtual Camera* GetCamera() const { return m_pMainCamera; };
};


#endif // !WORLD_H
