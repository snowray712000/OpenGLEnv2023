#define GLAD_GL_IMPLEMENTATION 
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#pragma comment(lib,"glfw3_mt.lib")
#include "mainFlowUsingGlfwGlad.h"

#include <iostream> // cout
#include "EasyImGui.h"
#include "EasyIO.h"
#include "EasyString.h"

MainFlowUsingGlfwGlad& MainFlowUsingGlfwGlad::s() {
	static MainFlowUsingGlfwGlad r1;
	return r1;
}
// callbackKey1
MainFlowUsingGlfwGlad* pObjectCallbackKey = nullptr;
void MainFlowUsingGlfwGlad::callbackGlfwKey(GLFWwindow* window, int keycode, int scancode, int action, int mods) {
	if (pObjectCallbackKey != nullptr) {
		pObjectCallbackKey->callbackKey(window, keycode, scancode, action, mods);
	}
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

	glfwSetKeyCallback(window, callbackGlfwKey);
	pObjectCallbackKey = this;

	return true;
}
void MainFlowUsingGlfwGlad::mainloopAfter() {
	EasyImGUI::exit();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void MainFlowUsingGlfwGlad::callbackKey(GLFWwindow* window, int keycode, int scancode, int action, int mods) {
	if (keycode == GLFW_KEY_O && mods == GLFW_MOD_CONTROL && action == GLFW_PRESS)
	{
		// 當 快速鍵 與 menu 綁定一起時，則在 menu 直接呼叫 callbackKey，參數要知道，就打開 print
		// printf("%d %d %d %d", keycode, scancode, action, mods); // 79 24 1 2
		auto path = EasyIO::OpenFileDialogEasyImage();
		std::cout << EasyString::stringwTostring(path); 
	}
}

void MainFlowUsingGlfwGlad::mainLoop() {
	mainloopPre();
	while (!glfwWindowShouldClose(window))
	{
		EasyImGUI::callThisBeforeGLClear();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("File", true)) {
				if (ImGui::MenuItem("Open", "Ctrl+O")) {
					this->callbackKey(window, GLFW_KEY_O, 24, GLFW_PRESS, GLFW_MOD_CONTROL);
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

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