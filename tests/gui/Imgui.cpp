#include "Imgui.h"

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
void Imgui::design(){
  //---------------------------

  // Inside the while loop, before creating the ImGui window
  int width, height;
  glfwGetWindowSize(window, &width, &height);
  ImGui::SetNextWindowSize(ImVec2(width, height));
  ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);

  ImGuiWindowFlags flag;
  flag |= ImGuiWindowFlags_NoTitleBar;
  flag |= ImGuiWindowFlags_NoResize;
  flag |= ImGuiWindowFlags_NoMove;
  flag |= ImGuiWindowFlags_NoCollapse;

  // Create the ImGui window with a table
  ImGui::Begin("##table", nullptr, flag);

  // Begin the table
  ImGui::BeginTable("Table", 3); // 3 columns

  // Table headers
  ImGui::TableSetupColumn("Column 1");
  ImGui::TableSetupColumn("Column 2");
  ImGui::TableSetupColumn("Column 3");
  ImGui::TableHeadersRow();

  // Table content
  for(int row = 0; row < 5; row++){
    ImGui::TableNextRow();
    for(int col = 0; col < 3; col++){
      ImGui::TableSetColumnIndex(col);
      ImGui::Text("Row %d, Column %d", row + 1, col + 1);
    }
  }

  // End the table
  ImGui::EndTable();

  // End the ImGui window
  ImGui::End();

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
  this->window = glfwCreateWindow(410, 428, "Test", NULL, NULL);
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

    this->design();

    // Rendering
    glClearColor(0, 0, 0, 1.00f);
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
