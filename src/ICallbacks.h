#ifndef ICALLBACKS_H_
#define ICALLBACKS_H_

class GLFWwindow;

/**
 * Callbacks for GLFW
 */
class ICallbacks {
	public:
		virtual ~ICallbacks() {}

		virtual void SetupRC() = 0;
		virtual void OnRender() = 0;
		virtual void OnLoop() = 0;
		virtual void OnExit() = 0;

		// callbacki ki jih potrebuje GLFW
		virtual void OnResize(GLFWwindow* from, int width, int height) = 0;
		virtual void KeyboardEvent(GLFWwindow* from, int key, int scancode, int action, int mods) = 0;
		virtual void MouseEvent(GLFWwindow* from, int button, int action, int mods) = 0;
		virtual void MouseMove(GLFWwindow* from, double x, double y) = 0;
		virtual void OnScroll(GLFWwindow* from, double x, double y) = 0;
};

#endif /* ICALLBACKS_H_ */
