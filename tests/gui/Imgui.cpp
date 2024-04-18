#include "Imgui.h"

#include <GLFW/glfw3.h>
#include <imgui/core/imgui.h>
#include <imgui/core/imgui_impl_glfw.h>
#include <imgui/core/imgui_internal.h>
#include <imgui/opengl/imgui_impl_opengl3.h>



namespace test{

Imgui::Imgui(){
  //---------------------------


  //---------------------------
}
Imgui::~Imgui(){}

//Main function
void Imgui::run(){
  //---------------------------

  this->init();
  this->loop();
  this->clean();

  //---------------------------
}

//Subfunction
void Imgui::init(){
  //---------------------------

  // Initialize GLFW
  if(!glfwInit()){
    return;
  }

  // Create a windowed mode window and its OpenGL context
  GLFWwindow* window = glfwCreateWindow(1280, 720, "Test", NULL, NULL);
  if (!window){
    glfwTerminate();
    return;
  }

  // Make the window's context current
  glfwMakeContextCurrent(window);

  // Initialize ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;

  // Setup ImGui backend bindings
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 130");

  //---------------------------
}
void Imgui::loop(){
  //---------------------------

  while (!glfwWindowShouldClose(window)){
    // Poll and handle events
    glfwPollEvents();

    // Start the ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Create your ImGui window here
    ImGui::Begin("Hello, world!");
    ImGui::Text("This is some text.");
    ImGui::End();

    // Rendering
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap buffers
    glfwSwapBuffers(window);
  }

  //---------------------------
}
void Imgui::clean(){
  //---------------------------

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();

  //---------------------------
}

}
