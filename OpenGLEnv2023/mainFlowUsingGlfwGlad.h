#pragma once
#include <GLFW/glfw3.h>
class MainFlowUsingGlfwGlad {
public:
	GLFWwindow* window;
    static MainFlowUsingGlfwGlad& s();
protected:
    bool mainloopPre();
    void mainloopAfter();
public:
    void mainLoop();
private:
    void callbackKey(GLFWwindow* window, int keycode, int scancode, int action, int mods);
    static void callbackGlfwKey(GLFWwindow* window, int keycode, int scancode, int action, int mods);
};