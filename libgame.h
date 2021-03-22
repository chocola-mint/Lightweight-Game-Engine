#ifndef LIBGAME_DECL
#define LIBGAME_DECL

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>
#include <chrono>
#include <set>
#include <iostream>
#include <string>
#include <lua.hpp> // Library for Lua VM.

namespace libgame {
	typedef glm::vec2 Vector2;
	typedef glm::vec3 Vector3;
	typedef glm::mat4 Matrix4;
	typedef glm::mat3 Matrix3;
	typedef glm::vec4 Vector4;
	typedef glm::quat Quaternion;
	typedef GLFWwindow Window;
	const int VIEWPORT_WIDTH = 640;
	const int VIEWPORT_HEIGHT = 480;
	extern Matrix4 MVP;

	/// <summary>
	/// Class that describes an object's transformations.
	/// </summary>
	class Transform {
	public:
		Vector3 position, scale;
		Quaternion rotation;
		Transform() : position(0, 0, 0), rotation(Vector3(0.0f, 0.0f, 0.0f)), scale(1, 1, 1) {};
		Matrix4 Model();
		void SetRotation(const Vector3& eulerAngles);
		void Rotate(const float angle, const Vector3& axis);
		Vector3 Up();
		Vector3 Right();
		Vector3 Forward();

	};
	
	/// <summary>
	/// Base class for all game objects.
	/// The user should implement Update, FixedUpdate, Draw, and Start functions.
	/// </summary>
	class Object {
	public:
		bool isActive;
		Transform transform;
		Object() : isActive(false) {};


		virtual ~Object() = 0 {};
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Draw() = 0;
		virtual void Start() = 0;
	};

	/// <summary>
	/// A Subroutine Dispatcher that can act as a lightweight replacement for most Coroutine needs.
	/// To use, add the Dispatcher to the class as a member variable, and call it in the class'
	/// Update function. (Or FixedUpdate, if you want the dispatching to happen in fixed time rather than 
	/// on every frame)
	/// </summary>
	/// <typeparam name="T">The class that will use the Dispatcher.</typeparam>
	template<typename T>
	class Dispatcher {
	public:
		typedef bool (T::*Subroutine)();
	private:
		std::vector<Subroutine> _subroutineVec;
	public:

		void Add(Subroutine& s) {
			_subroutineVec.push_back(s);
		}

		void Clear() {
			_subroutineVec.clear();
		}

		bool Empty() const {
			return _subroutineVec.empty();
		}
		
		void Update() {
			for (int i = 0; i < _subroutineVec.size();) {
				if (_subroutineVec[i]()){
					std::swap(_subroutineVec[i], _subroutineVec.back());
					_subroutineVec.pop_back();
				}
				else ++i;
			}
		}
		
	};

	/// <summary>
	/// Base class for all cameras.
	/// </summary>
	class Camera : public Object {
	public:

		Vector3 forward;
		Vector3 up;
		Camera() : forward(0, 0, 0), up(0, 1, 0) {};
		Matrix4 View() {
			return glm::lookAt(transform.position, forward, up);
		}

		virtual Matrix4 Projection() = 0;

	};

	/// <summary>
	/// Base class for user-implemented scene objects.
	/// The user should implement the constructor, and optionally, the destructor.
	/// </summary>
	class Scene {
	public:
		Camera* mainCamera;
	};

	template<typename _objT>
	class ObjectPool : Object {
	private:
		struct __objPair {
			_objT obj;
			bool deactivated;
		};

		std::vector<__objPair> _pool;
		std::vector<int> _free_pos;
	public:
		void Start() override {

		}

		_objT& Instantiate() {
			_objT& ref = nullptr;
			if (_free_pos.size() == 0) {
				_pool.push_back(_objT());
				ref = _pool.back();
			}
			else {
				_pool[_free_pos.back()] = _objT();
				ref = _pool[_free_pos.back()];
				_free_pos.pop_back();
			}
			return ref;
		}

		void Update() override {
			for (int i = 0; i < _pool.size(); ++i) {
				_objT objp = _pool[i];
				if (!objp.deactivated)
					if (objp.obj.isActive)
						objp.obj.Update();
					else {
						objp.deactivated = true;
						_free_pos.push_back(i);
					}
			}
		}

		void FixedUpdate() override {
			for (auto objp : _pool)
				objp.obj.FixedUpdate();
		}

		void Draw() override {
			for (auto objp : _pool)
				objp.obj.Draw();
		}


	};

	extern double deltaTime;
	extern double fixedDeltaTime;
	void ErrorCallback(int error, const char* description);
	void RegisterObject(Object* newObject);
	void StartObjects();
	void UpdateObjects();
	void DrawObjects();
	void EngineInit();
	void GameInit();
	void LoadScene(Scene* newScene);
	void UnloadCurrentScene();
	void GameLoop();

}

#endif