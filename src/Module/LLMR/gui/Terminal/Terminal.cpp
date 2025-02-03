#include "Terminal.h"
#include "Structure.h"

#include <LLMR/Namespace.h>
#include <Utility/Namespace.h>


namespace llmr::gui{

//Constructor / Destructor
Terminal::Terminal(llmr::Node* node_llmr){
  //---------------------------

  this->ter_struct = new llmr::gui::terminal::Structure();
  this->llmr_interface = node_llmr->get_llmr_interface();

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

//Log function
void Terminal::add_log(const char* fmt, ...){
  //---------------------------

  // FIXME-OPT
  char buf[1024];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
  buf[IM_ARRAYSIZE(buf)-1] = 0;
  va_end(args);
  ter_struct->vec_item.push_back(Strdup(buf));

  //---------------------------
}
void Terminal::add_log(std::string& log){
  //---------------------------

  char* copy = ImStrdup(log.c_str());
  ter_struct->vec_item.push_back(copy);

  //---------------------------
}
void Terminal::add_file(std::string prefix, std::string path){
  //---------------------------

  //Retrieve file content
  std::ifstream inputFile(path.c_str());
  if(!inputFile.is_open()){
    std::cerr << "Failed to open the file for reading." << std::endl;
    return;
  }
  std::string content((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
  inputFile.close();

  //Add content into console
  if(content != ""){
    if(prefix == "error"){
      this->add_log("[error]");
    }
    this->add_log(content.c_str());
  }

  //Clear file
  std::ofstream outputFile(path.c_str(), std::ofstream::out);
  if(outputFile.is_open()){
    outputFile.close();
  }else{
    std::cerr << "Failed to open the file for clearing." << std::endl;
    return;
  }

  //---------------------------
}
void Terminal::clear_log(){
  //---------------------------

  for(int i = 0; i < ter_struct->vec_item.Size; i++){
    free(ter_struct->vec_item[i]);
  }
  ter_struct->vec_item.clear();

  //---------------------------
}

//Subfunction
void Terminal::draw_console(){
  //---------------------------

  // Reserve enough left-over height for 1 separator + 1 input text
  const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
  if(ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), ImGuiChildFlags_NavFlattened, ImGuiWindowFlags_HorizontalScrollbar)){
    if(ImGui::BeginPopupContextWindow()){
      if(ImGui::Selectable("Clear")){
        clear_log();
      }
      ImGui::EndPopup();
    }

    // Display every line as a separate entry so we can change their color or add custom widgets.
    // If you only want raw text you can use ImGui::TextUnformatted(log.begin(), log.end());
    // NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping
    // to only process visible items. The clipper will automatically measure the height of your first item and then
    // "seek" to display only items in the visible area.
    // To use the clipper we can replace your standard loop:
    //      for(int i = 0; i < Items.Size; i++)
    //   With:
    //      ImGuiListClipper clipper;
    //      clipper.Begin(Items.Size);
    //      while(clipper.Step())
    //         for(int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
    // - That your items are evenly spaced (same height)
    // - That you have cheap random access to your elements (you can access them given their index,
    //   without processing all the ones before)
    // You cannot this code as-is if a filter is active because it breaks the 'cheap random-access' property.
    // We would need random-access on the post-filtered list.
    // A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices
    // or offsets of items that passed the filtering test, recomputing this array when user changes the filter,
    // and appending newly elements as they are inserted. This is left as a task to the user until we can manage
    // to improve this example code!
    // If your items are of variable height:
    // - Split them into same height items would be simpler and facilitate random-seeking into your list.
    // - Consider using manual call to IsRectVisible() and skipping extraneous decoration from your items.
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
    for(const char* item : ter_struct->vec_item){
      if(!ter_struct->filter.PassFilter(item))
        continue;

      // Normally you would store more information in your item than just a string.
      // (e.g. make Items[] an array of structure, store color/type etc.)
      ImVec4 color;
      bool has_color = false;
      if(strstr(item, "[error]")){ color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f); has_color = true; }
      else if(strncmp(item, "# ", 2) == 0){ color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f); has_color = true; }
      if(has_color){
        ImGui::PushStyleColor(ImGuiCol_Text, color);
      }
      ImGui::TextUnformatted(item);
      if(has_color){
        ImGui::PopStyleColor();
      }
    }

    // Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
    // Using a scrollbar or mouse-wheel will take away from the bottom edge.
    if(ter_struct->scroll_to_bottom || (ter_struct->is_autoscroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
      ImGui::SetScrollHereY(1.0f);
    ter_struct->scroll_to_bottom = false;

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
  if(ImGui::InputText("##terminal_input", ter_struct->input_buffer, IM_ARRAYSIZE(ter_struct->input_buffer), flag, &TextEditCallbackStub, (void*)this)){
    char* s = ter_struct->input_buffer;
    Strtrim(s);
    if(s[0]){
      this->execute_command(s);
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
void Terminal::execute_command(const char* command_line){
  //---------------------------

  this->add_log("# %s\n", command_line);

  // Insert into history. First find match and delete it so it can be pushed to the back.
  // This isn't trying to be smart or optimal.
  ter_struct->history_pose = -1;
  for(int i = ter_struct->history.Size - 1; i >= 0; i--){
    if(Stricmp(ter_struct->history[i], command_line) == 0){
      free(ter_struct->history[i]);
      ter_struct->history.erase(ter_struct->history.begin() + i);
      break;
    }
  }

  ter_struct->history.push_back(Strdup(command_line));

  std::string input(command_line);
  this->process_input(input);

  // On command input, we scroll to bottom even if ter_struct->is_autoscroll==false
  ter_struct->scroll_to_bottom = true;

  //---------------------------
}
void Terminal::process_input(std::string command_line){
  //---------------------------
say(command_line);
  llmr_interface->send_llm_message(command_line);

  //---------------------------
}
int Terminal::TextEditCallback(ImGuiInputTextCallbackData* data){
  //---------------------------

  //add_log("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
  switch (data->EventFlag){
    case ImGuiInputTextFlags_CallbackCompletion:{
            // Example of TEXT COMPLETION

            // Locate beginning of current word
            const char* word_end = data->Buf + data->CursorPos;
            const char* word_start = word_end;
            while(word_start > data->Buf)
            {
                const char c = word_start[-1];
                if(c == ' ' || c == '\t' || c == ',' || c == ';')
                    break;
                word_start--;
            }

            // Build a list of candidates
            ImVector<const char*> candidates;
            for(int i = 0; i < ter_struct->vec_command.Size; i++)
                if(Strnicmp(ter_struct->vec_command[i], word_start, (int)(word_end - word_start)) == 0)
                    candidates.push_back(ter_struct->vec_command[i]);

            if(candidates.Size == 0)
            {
                // No match
                add_log("No match for \"%.*s\"!\n", (int)(word_end - word_start), word_start);
            }
            else if(candidates.Size == 1)
            {
                // Single match. Delete the beginning of the word and replace it entirely so we've got nice casing.
                data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
                data->InsertChars(data->CursorPos, candidates[0]);
                data->InsertChars(data->CursorPos, " ");
            }
            else
            {
                // Multiple matches. Complete as much as we can..
                // So inputing "C"+Tab will complete to "CL" then display "CLEAR" and "CLASSIFY" as matches.
                int match_len = (int)(word_end - word_start);
                for(;;)
                {
                    int c = 0;
                    bool all_candidates_matches = true;
                    for(int i = 0; i < candidates.Size && all_candidates_matches; i++)
                        if(i == 0)
                            c = toupper(candidates[i][match_len]);
                        else if(c == 0 || c != toupper(candidates[i][match_len]))
                            all_candidates_matches = false;
                    if(!all_candidates_matches)
                        break;
                    match_len++;
                }

                if(match_len > 0)
                {
                    data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
                    data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
                }

                // List matches
                add_log("Possible matches:\n");
                for(int i = 0; i < candidates.Size; i++)
                    add_log("- %s\n", candidates[i]);
            }

            break;
        }
    case ImGuiInputTextFlags_CallbackHistory:{
          // Example of HISTORY
          const int prev_history_pos = ter_struct->history_pose;
          if(data->EventKey == ImGuiKey_UpArrow)
          {
              if(ter_struct->history_pose == -1)
                  ter_struct->history_pose = ter_struct->history.Size - 1;
              else if(ter_struct->history_pose > 0)
                  ter_struct->history_pose--;
          }
          else if(data->EventKey == ImGuiKey_DownArrow)
          {
              if(ter_struct->history_pose != -1)
                  if(++ter_struct->history_pose >= ter_struct->history.Size)
                      ter_struct->history_pose = -1;
          }

          // A better implementation would preserve the data on the current input line along with cursor position.
          if(prev_history_pos != ter_struct->history_pose)
          {
              const char* history_str = (ter_struct->history_pose >= 0) ? ter_struct->history[ter_struct->history_pose] : "";
              data->DeleteChars(0, data->BufTextLen);
              data->InsertChars(0, history_str);
          }
      }
  }

  //---------------------------
  return 0;
}

}
