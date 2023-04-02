#include "EasyImGui.h"

// make current 之後呼叫
namespace EasyImGUI {
	void init(GLFWwindow* window, const char* glsl_version) {

		// Setup Dear ImGui context
		//auto glsl_version = "#version 450";
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImPlot::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImFontConfig config;
		//config.OversampleH = 1; //设置水平方向的过采样量
		//config.OversampleV = 1; //设置垂直方向的过采样量
		// ImFont* font = io.Fonts->AddFontFromFileTTF("msjh.ttc", 18.0f, &config); //将字体文件加入到ImFontAtlas中
		// io.Fonts->AddFontFromFileTTF("msjh.ttc", 24.0f, &config, io.Fonts->GetGlyphRangesChineseFull());
		//io.FontDefault = font; //设置默认字体

		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);
	}
	// glfw terminate 之前呼叫
	void exit() {
		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImPlot::DestroyContext();
		ImGui::DestroyContext();
	}
	void callThisBeforeGLClear() {
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	void callThisAfterGLClearBeforeSwapBuffer() {
		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}

