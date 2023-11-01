#ifndef GIT_FUNCTION_H
#define GIT_FUNCTION_H

#include <Specific/common.h>
#include <git2.h>


class Git
{
public:
  //Constructor / Destructor
  Git();
  ~Git();

public:
  //Main functions
  void open_repository();
  void close_repository();

  //Git function
  void retrieve_all_branch();

  //Subfunction
  void format_branch();

  inline vector<string> get_vec_branch(){return vec_branch;}
  inline vector<pair<string, string>> get_vec_branch_formatted(){return vec_branch_format;}

private:
  vector<string> vec_branch;
  vector<pair<string, string>> vec_branch_format;
  git_repository* repo;
};

#endif
