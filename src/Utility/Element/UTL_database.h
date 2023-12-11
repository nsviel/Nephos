#pragma once

#include <string>
#include <vector>
#include <SQLiteCpp/SQLiteCpp.h>

using namespace std;


namespace util::element{

class UTL_database
{
public:
  //Constructor / Destructor
  UTL_database(string path);
  ~UTL_database();

public:
  //Management function
  void create_table(string name);
  void remove_table(string name);

  //Retrieving function
  vector<string> retrieve_all_table();

private:
  string db_path;
};

}
