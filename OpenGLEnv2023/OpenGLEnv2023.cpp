#include <iostream>
#include <Eigen/Eigen>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <imgui/implot.h>
#include <imgui/implot_internal.h>

#define GLAD_GL_IMPLEMENTATION 
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#pragma comment(lib,"glfw3_mt.lib")

void init_imgui(GLFWwindow* window);
void exit_imgui();
void imgui_step1();
void imgui_step2();

void opengl_render();
int main(void)
{
    GLFWwindow* window;
    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Init glad (必須在 make current 之後)
    if (!gladLoadGL(glfwGetProcAddress)) {
        printf("Failed to load glad.");
        return -1; // RES_ERROR_LOAD_GLAD;
    }

    init_imgui(window);

    while (!glfwWindowShouldClose(window))
    {
        imgui_step1(); // glClear 前呼叫。其中描述 gui 長相。
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        imgui_step2(); // 繪 gui，
        opengl_render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    exit_imgui();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}


void init_imgui(GLFWwindow* window) {

    // Setup Dear ImGui context
    auto glsl_version = "#version 460";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext(); // 新增
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    //ImGui::StyleColorsDark();
    ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}
void exit_imgui() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImPlot::DestroyContext(); // 新增
    ImGui::DestroyContext();
}

bool show_demo_window = false;
void imgui_step1() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow(&show_demo_window);
    ImPlot::ShowDemoWindow(&show_demo_window); // 新增
}
void imgui_step2() {
    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void opengl_render() {

    glBegin(GL_TRIANGLES);
    glVertex2f(0, 0);
    glVertex2f(0.5, 0);
    glVertex2f(0.5, 0.5);
    glEnd();
}