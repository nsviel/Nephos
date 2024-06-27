#pragma once

#include <git2.h>
#include <vector>
#include <string>


namespace utl::element{

class Git
{
public:
  //Constructor / Destructor
  Git();
  ~Git();

public:
  //Main function
  void open_repository();
  void close_repository();

  //Git function
  void retrieve_all_branch();
  void retrieve_last_tag();
  void up_tag_version();

  //Subfunction
  void format_branch();

  inline std::string get_last_tag(){return last_tag;}
  inline std::vector<std::string> get_vec_branch(){return vec_branch;}
  inline std::vector<std::pair<std::string, std::string>> get_vec_branch_formatted(){return vec_branch_format;}

private:
  std::vector<std::string> vec_branch;
  std::vector<std::pair<std::string, std::string>> vec_branch_format;
  std::string last_tag;
  git_repository* repo;
};

}
