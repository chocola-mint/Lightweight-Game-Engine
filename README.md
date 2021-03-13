# Lightweight Game Engine
#### (Name subject to be changed)
---
To use the game engine:
1. Add a .cpp file of your own.
2. Add a scene class of your own, inheriting from libgame::Scene.
3. Implement the constructor and the destructor of the scene class. This is where you can set up your scene.
4. Implement the GameInit() function in your cpp file and call LoadScene on "new (YourScene)".
5. Done!

The API is very much subject to change, but here is the gist of it right now:
- Every Game Object should inherit from libgame::Object. This gives it the Start, Update, FixedUpdate, and Draw functions.
	- Upon instantiation, it should be registered into the game engine using RegisterObject(object's pointer).
	- The object will be deleted when it is deactivated or when the scene is unloaded.
- You can use the DefaultCamera class or make a camera of your own by inheriting from libgame::Camera. The camera, once instantiated, should be assigned to the scene's MainCamera pointer. This lets the game engine know which camera to use for the View and Projection matrices.

