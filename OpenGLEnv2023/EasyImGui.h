#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <imgui/implot.h>
#include <imgui/implot_internal.h>

#include <GLFW/glfw3.h>

namespace EasyImGUI {
	// make current 之後呼叫
	void init(GLFWwindow* window, const char* glsl_version = "#version 460");
	// glfw terminate 之前呼叫
	void exit();
	// main loop 中，每次都要呼叫的
	void callThisBeforeGLClear();
	// 這行放的位置會決定，它會被什麼壓過去，放在 glClear 之後，就會是最後，不會蓋過 openGL；放在 繪圖程式碼 之後，就會蓋過
	void callThisAfterGLClearBeforeSwapBuffer();
}