#include "Console.h"


namespace utl::gui::widget{

//Constructor / Destructor
Console::Console(){
  //---------------------------

  this->AutoScroll = true;

  //---------------------------
}
Console::~Console(){}

//Main function
void Console::draw_console(std::string title){
  //---------------------------

  // Reserve enough left-over height for 1 separator + 1 input text
  const float footer_height_to_reserve = ImGui::GetFrameHeightWithSpacing();
  if(ImGui::BeginChild("ScrollingRegion", ImVec2(0, 100), false, ImGuiWindowFlags_HorizontalScrollbar)){
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
    for(const char* item : Items){
      if(!Filter.PassFilter(item))
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
    if(ScrollToBottom || (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
      ImGui::SetScrollHereY(1.0f);
    ScrollToBottom = false;

    ImGui::PopStyleVar();
  }
  ImGui::EndChild();

  //---------------------------
}

//Add / clear function
void Console::add_log(const char* fmt, ...){
  //---------------------------

  // FIXME-OPT
  char buf[1024];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
  buf[IM_ARRAYSIZE(buf)-1] = 0;
  va_end(args);
  Items.push_back(Strdup(buf));

  //---------------------------
}
void Console::add_log(std::string& log){
  //---------------------------

  char* copy = ImStrdup(log.c_str());
  Items.push_back(copy);

  //---------------------------
}
void Console::add_file(std::string prefix, std::string path){
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
void Console::clear_log(){
  //---------------------------

  for(int i = 0; i < Items.Size; i++){
    free(Items[i]);
  }
  Items.clear();

  //---------------------------
}

//Subfunction
void Console::draw_command_line(){
  //---------------------------

  bool reclaim_focus = false;
  ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_EscapeClearsAll | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
  if(ImGui::InputText("Input", InputBuf, IM_ARRAYSIZE(InputBuf), input_text_flags, &TextEditCallbackStub, (void*)this)){
    char* s = InputBuf;
    Strtrim(s);
    if(s[0]){
      ExecCommand(s);
    }
    strcpy(s, "");
    reclaim_focus = true;
  }

  //---------------------------
}
void Console::ExecCommand(const char* command_line){
  //---------------------------

  add_log("# %s\n", command_line);

  // Insert into history. First find match and delete it so it can be pushed to the back.
  // This isn't trying to be smart or optimal.
  HistoryPos = -1;
  for(int i = History.Size - 1; i >= 0; i--)
      if(Stricmp(History[i], command_line) == 0)
      {
          free(History[i]);
          History.erase(History.begin() + i);
          break;
      }
  History.push_back(Strdup(command_line));

  // Process command
  if(Stricmp(command_line, "CLEAR") == 0)
  {
      clear_log();
  }
  else if(Stricmp(command_line, "HELP") == 0)
  {
      add_log("Commands:");
      for(int i = 0; i < Commands.Size; i++)
          add_log("- %s", Commands[i]);
  }
  else if(Stricmp(command_line, "HISTORY") == 0)
  {
      int first = History.Size - 10;
      for(int i = first > 0 ? first : 0; i < History.Size; i++)
          add_log("%3d: %s\n", i, History[i]);
  }
  else
  {
      add_log("Unknown command: '%s'\n", command_line);
  }

  // On command input, we scroll to bottom even if AutoScroll==false
  ScrollToBottom = true;

  //---------------------------
}
int Console::TextEditCallback(ImGuiInputTextCallbackData* data){
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
            for(int i = 0; i < Commands.Size; i++)
                if(Strnicmp(Commands[i], word_start, (int)(word_end - word_start)) == 0)
                    candidates.push_back(Commands[i]);

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
          const int prev_history_pos = HistoryPos;
          if(data->EventKey == ImGuiKey_UpArrow)
          {
              if(HistoryPos == -1)
                  HistoryPos = History.Size - 1;
              else if(HistoryPos > 0)
                  HistoryPos--;
          }
          else if(data->EventKey == ImGuiKey_DownArrow)
          {
              if(HistoryPos != -1)
                  if(++HistoryPos >= History.Size)
                      HistoryPos = -1;
          }

          // A better implementation would preserve the data on the current input line along with cursor position.
          if(prev_history_pos != HistoryPos)
          {
              const char* history_str = (HistoryPos >= 0) ? History[HistoryPos] : "";
              data->DeleteChars(0, data->BufTextLen);
              data->InsertChars(0, history_str);
          }
      }
  }

  //---------------------------
  return 0;
}

}
