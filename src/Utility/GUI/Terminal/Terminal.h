#pragma once

#include <imgui/core/imgui.h>
#include <imgui/core/imgui_internal.h>
#include <iostream>
#include <fstream>
#include <string>

namespace utl::gui::terminal{class Structure;}


namespace utl::gui::terminal{

class Terminal
{
public:
  //Constructor / Destructor
  Terminal();
  ~Terminal();

public:
  //Main function
  void draw_terminal();

  //Log function
  void clear_log();
  void add_log(const char* fmt, ...);
  void add_log(std::string& log);
  void add_file(std::string prefixe, std::string path);

  //Subfunction
  void draw_console();
  void draw_input();
  void execute_command(const char* command_line);
  int TextEditCallback(ImGuiInputTextCallbackData* data);

  // Portable helpers
  static int   Stricmp(const char* s1, const char* s2)         { int d; while((d = toupper(*s2) - toupper(*s1)) == 0 && *s1){ s1++; s2++; } return d; }
  static int   Strnicmp(const char* s1, const char* s2, int n){ int d = 0; while(n > 0 && (d = toupper(*s2) - toupper(*s1)) == 0 && *s1){ s1++; s2++; n--; } return d; }
  static char* Strdup(const char* s)                           { IM_ASSERT(s); size_t len = strlen(s) + 1; void* buf = malloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)s, len); }
  static void  Strtrim(char* s)                                { char* str_end = s + strlen(s); while(str_end > s && str_end[-1] == ' ') str_end--; *str_end = 0; }
  static int TextEditCallbackStub(ImGuiInputTextCallbackData* data){
    Terminal* console = (Terminal*)data->UserData;
    return console->TextEditCallback(data);
  }

private:
  utl::gui::terminal::Structure* ter_struct;
};

}
