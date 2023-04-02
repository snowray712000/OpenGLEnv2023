#define GLAD_GL_IMPLEMENTATION 
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#pragma comment(lib,"glfw3_mt.lib")
#include "mainFlowUsingGlfwGlad.h"

#include "EasyImGui.h"

MainFlowUsingGlfwGlad& MainFlowUsingGlfwGlad::s() {
	static MainFlowUsingGlfwGlad r1;
	return r1;
}

bool MainFlowUsingGlfwGlad::mainloopPre() {
	GLFWwindow* window;
	if (!glfwInit())
		return false;

	window = glfwCreateWindow(500, 500, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return false;
	}
	this->window = window;

	glfwMakeContextCurrent(window);

	// Init glad (必須在 make current 之後)
	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("Failed to load glad.");
		return false; // RES_ERROR_LOAD_GLAD;
	}

	EasyImGUI::init(window);

	return true;
}
void MainFlowUsingGlfwGlad::mainloopAfter() {
	EasyImGUI::exit();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void MainFlowUsingGlfwGlad::mainLoop() {
	mainloopPre();
	while (!glfwWindowShouldClose(window))
	{
		EasyImGUI::callThisBeforeGLClear();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		EasyImGUI::callThisAfterGLClearBeforeSwapBuffer();

		glBegin(GL_TRIANGLES);
		glVertex2f(0, 0);
		glVertex2f(0.5, 0);
		glVertex2f(0.5, 0.5);
		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	mainloopAfter();
}