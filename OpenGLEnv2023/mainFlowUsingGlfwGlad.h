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
};