#pragma once

#include <Utility/Specific/Common.h>
#include <git2.h>


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

  inline string get_last_tag(){return last_tag;}
  inline vector<string> get_vec_branch(){return vec_branch;}
  inline vector<pair<string, std::string>> get_vec_branch_formatted(){return vec_branch_format;}

private:
  vector<string> vec_branch;
  vector<pair<string, std::string>> vec_branch_format;
  git_repository* repo;
  string last_tag;
};

}