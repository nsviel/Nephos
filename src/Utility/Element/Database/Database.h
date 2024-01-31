#pragma once

#include <string>
#include <vector>
#include <SQLiteCpp/SQLiteCpp.h>

using namespace std;


namespace utl::element{

class Database
{
public:
  //Constructor / Destructor
  Database(string path);
  ~Database();

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
