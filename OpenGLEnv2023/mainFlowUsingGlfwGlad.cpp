#define GLAD_GL_IMPLEMENTATION 
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#pragma comment(lib,"glfw3_mt.lib")
#include "mainFlowUsingGlfwGlad.h"

#include <iostream> // cout
#include <fstream>
#include <math.h>
#include "EasyImGui.h"
#include "EasyIO.h"
#include "EasyString.h"
#include "STLTrimLineGenerator.h"

#define M_PI       3.14159265358979323846   // pi
MainFlowUsingGlfwGlad& MainFlowUsingGlfwGlad::s() {
	static MainFlowUsingGlfwGlad r1;
	return r1;
}
void MainFlowUsingGlfwGlad::key_callbacks(GLFWwindow* window, int keycode, int scancode, int action, int mods) {
	s().key_callback(window, keycode, scancode, action, mods);
}
void MainFlowUsingGlfwGlad::mouse_callbacks(GLFWwindow* window, int button, int action, int mods) {
	s().mouse_callback(window, button, action, mods);
}
void MainFlowUsingGlfwGlad::cursor_callbacks(GLFWwindow* window, double xpos, double ypos) {
	s().cursor_callback(window, xpos, ypos);
}
void MainFlowUsingGlfwGlad::framebuffer_size_callbacks(GLFWwindow* window, int width, int height) {
	s().framebuffer_size_callback(window, width, height);
}
void MainFlowUsingGlfwGlad::guiMainMenu() {

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File", true)) {
			if (ImGui::MenuItem("Open", "Ctrl+O")) {
				this->key_callback(window, GLFW_KEY_O, 24, GLFW_PRESS, GLFW_MOD_CONTROL);
			}
			if (ImGui::MenuItem("Save", "Ctrl+S")) {
				this->key_callback(window, GLFW_KEY_S, 31, GLFW_PRESS, GLFW_MOD_CONTROL);
			}
			if (ImGui::MenuItem("Batch Process", "")) {
				STLTrimLineGeneratorBatchFlow flow;
				flow.main();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}
void MainFlowUsingGlfwGlad::glDrawXYZAxis() {
	// x-y-z 軸
	glBegin(GL_LINES);
	glColor3ub(255, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glColor3ub(0, 255, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glColor3ub(0, 0, 255);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glEnd();
}
bool MainFlowUsingGlfwGlad::mainloopPre() {
	GLFWwindow* window;
	if (!glfwInit())
		return false;

	window = glfwCreateWindow(cxwin, cywin, "Hello World", NULL, NULL);

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

	glfwSetKeyCallback(window, key_callbacks);
	glfwSetMouseButtonCallback(window, mouse_callbacks);
	glfwSetCursorPosCallback(window, cursor_callbacks);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callbacks);

	return true;
}
void MainFlowUsingGlfwGlad::mainloopAfter() {
	EasyImGUI::exit();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void MainFlowUsingGlfwGlad::key_callback(GLFWwindow* window, int keycode, int scancode, int action, int mods) {
	if (keycode == GLFW_KEY_O && mods == GLFW_MOD_CONTROL && action == GLFW_PRESS)
	{
		// 當 快速鍵 與 menu 綁定一起時，則在 menu 直接呼叫 callbackKey，參數要知道，就打開 print
		// printf("%d %d %d %d", keycode, scancode, action, mods); // 79 24 1 2
		auto path = EasyIO::OpenFileDialogEasy(_T("STL Files\0*.stl\0All Files(*.*)\0*.*\0"));
		std::cout << EasyString::toCout(path); 
	}
	else if (keycode == GLFW_KEY_S && mods == GLFW_MOD_CONTROL && action == GLFW_PRESS) {
		auto path = EasyIO::SaveFileDialog(_T("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0"),_T("txt"));
	}
}

void MainFlowUsingGlfwGlad::mouse_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		isPressedLButton = true;
		glfwGetCursorPos(window, &xPressedInstant, &yPressedInstant);
		xPressedLast = xPressedInstant;
		yPressedLast = yPressedInstant;
		
		ImGui::GetIO().MouseDown[0] = true; // 沒有的話，會使 ImGUI 的 Menu 按了卻無反應。
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		isPressedLButton = false;
		
		ImGui::GetIO().MouseDown[0] = false;// 沒有的話，會使 ImGUI 的 Menu 按了卻無反應。
	}
}

void MainFlowUsingGlfwGlad::cursor_callback(GLFWwindow* window, double xpos, double ypos) {
	ImGui::GetIO().MousePos = ImVec2(xpos, ypos);  // // 沒有的話，會使 ImGUI 的 Menu 按了卻無反應。 通知 ImGui 鼠標位置的變化
	if (isPressedLButton)
	{
		double deltaX = xpos - xPressedLast;
		double deltaY = ypos - yPressedLast;
		angleX += deltaY / cxwin * M_PI;
		angleY += deltaX / cywin * M_PI;
		xPressedLast = xpos;
		yPressedLast = ypos;
	}
}

void MainFlowUsingGlfwGlad::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	cxwin = width;
	cywin = height;

	glViewport(0, 0, width, height);  // 設置 OpenGL 視口大小為窗口大小

	glMatrixMode(GL_PROJECTION);  // 切換到投影矩陣模式
	glLoadIdentity();  // 重置矩陣

	// 計算新的投影矩陣，保持長寬比不變
	double aspect_ratio = (double)width / height;
	if (aspect_ratio > 1)
	{
		glOrtho(-aspect_ratio, aspect_ratio, -1, 1, 1, -1);
	}
	else
	{
		glOrtho(-1, 1, -1 / aspect_ratio, 1 / aspect_ratio, 1, -1);
	}
}

void MainFlowUsingGlfwGlad::mainLoop() {
	mainloopPre();
	while (!glfwWindowShouldClose(window))
	{
		EasyImGUI::callThisBeforeGLClear();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->guiMainMenu();
		EasyImGUI::callThisAfterGLClearBeforeSwapBuffer();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef(angleX * 180 / M_PI, 1, 0, 0);
		glRotatef(angleY * 180 / M_PI, 0, 1, 0);
		this->glDrawXYZAxis();
		
		glColor3ub(255, 255, 255);
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