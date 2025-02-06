#include "Terminal.h"

#include <LLMR/Namespace.h>
#include <Utility/Namespace.h>


namespace llmr::gui{

//Constructor / Destructor
Terminal::Terminal(llmr::Node* node_llmr){
  //---------------------------

  this->llmr_struct = node_llmr->get_llmr_struct();
  this->llmr_interface = node_llmr->get_llmr_interface();
  this->llmr_terminal = node_llmr->get_llmr_terminal();

  //---------------------------
}
Terminal::~Terminal(){}

//Main function
void Terminal::draw_terminal(){
  //---------------------------

  this->draw_console();
  this->draw_input();

  //---------------------------
}

//Subfunction
void Terminal::draw_console(){
  //---------------------------

  // Reserve enough left-over height for 1 separator + 1 input text
  const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
  if(ImGui::BeginChild("ScrollingRegion", ImVec2(ImGui::GetContentRegionAvail().x, -footer_height_to_reserve), ImGuiChildFlags_NavFlattened, ImGuiWindowFlags_HorizontalScrollbar)){
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing

    // Start clipping and rendering the visible items
    ImGuiListClipper clipper;
    clipper.Begin(llmr_struct->terminal.vec_item.size());
    while (clipper.Step()) {
      for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++){
        // Get the string from the item
        llmr::structure::Item& item = llmr_struct->terminal.vec_item[i];
        std::string prefix = (item.prefix != "") ? "[" + item.prefix + "] " : "";
        std::string texte = prefix + break_lines(item.texte);

        // Render the text
        ImVec4 color = ImVec4(item.color.x, item.color.y, item.color.z, item.color.w);
        ImGui::PushStyleColor(ImGuiCol_Text, color);
        ImGui::TextUnformatted(texte.c_str());
        ImGui::PopStyleColor();
      }
    }
    clipper.End();

    // Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
    // Using a scrollbar or mouse-wheel will take away from the bottom edge.
    if(llmr_struct->terminal.scroll_to_bottom || (llmr_struct->terminal.is_autoscroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())){
      ImGui::SetScrollHereY(1.0f);
      llmr_struct->terminal.scroll_to_bottom = false;
    }

    ImGui::PopStyleVar();
  }
  ImGui::EndChild();

  //---------------------------
}
void Terminal::draw_input(){
  //---------------------------

  bool reclaim_focus = false;
  ImGuiInputTextFlags flag;
  flag |= ImGuiInputTextFlags_EnterReturnsTrue;
  flag |= ImGuiInputTextFlags_EscapeClearsAll;
  flag |= ImGuiInputTextFlags_CallbackCompletion;
  flag |= ImGuiInputTextFlags_CallbackHistory;
  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
  if(ImGui::InputText("##terminal_input", llmr_struct->terminal.input_buffer, IM_ARRAYSIZE(llmr_struct->terminal.input_buffer), flag, NULL, (void*)this)){
    char* s = llmr_struct->terminal.input_buffer;
    std::string str = std::string(s);

    if(!str.empty()){
      llmr_terminal->add_log(str, "#");
      this->process_input(str);
      llmr_struct->terminal.scroll_to_bottom = true;
    }
    strcpy(s, "");
    reclaim_focus = true;
  }

  // Auto-focus on window apparition
  ImGui::SetItemDefaultFocus();
  if(reclaim_focus){
    ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
  }

  //---------------------------
}
void Terminal::process_input(std::string command_line){
  //---------------------------

  //Command
  if(command_line == "clear"){
    llmr_terminal->clear_log();
    return;
  }

  //Chatbot
  llmr_interface->send_llm_message(command_line);

  //---------------------------
}
std::string Terminal::break_lines(const std::string& text){
  //---------------------------

  ImVec2 windowSize = ImGui::GetWindowSize();  // Get current window size
  int windowWidth = static_cast<int>(ImGui::GetContentRegionAvail().x);
  int maxCharsPerLine = windowWidth / 6.5;

  std::istringstream stream(text);
  std::string word;
  std::vector<std::string> lines;
  std::string line;

  int currentLineLength = 0;

  while (stream >> word) {
      // Check if adding the word would exceed the max length for the line
      if (currentLineLength + word.length() + (line.empty() ? 0 : 1) > maxCharsPerLine) {
          lines.push_back(line);  // Add the current line to the result
          line = word;  // Start a new line with the current word
          currentLineLength = word.length();
      } else {
          // If the line has space, add the word to the line
          if (!line.empty()) {
              line += " ";  // Add a space before the word (if it's not the first word in the line)
              currentLineLength += 1;  // Account for the space
          }
          line += word;  // Add the word to the line
          currentLineLength += word.length();
      }
  }

  // Add any remaining words as the last line
  if (!line.empty()) {
      lines.push_back(line);
  }

  // Combine the lines with newlines
  std::string result;
  for (const auto& l : lines) {
      result += l + "\n";
  }

  //---------------------------
  return result;
}

}
