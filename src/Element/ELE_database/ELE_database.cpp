#include "ELE_database.h"


//Constructor / Destructor
ELE_database::ELE_database(string path){
  //---------------------------

  this->path_database = path;

  //---------------------------
}
ELE_database::~ELE_database(){}

//Management function
void ELE_database::create_table(string name){
  //---------------------------

  SQLite::Database db(path_database.c_str(), SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

  db.exec("DROP TABLE IF EXISTS " + name);
  db.exec("CREATE TABLE " + name + " (id INTEGER PRIMARY KEY, value TEXT)");

  //---------------------------
}
void ELE_database::remove_table(string name){
  //---------------------------

  SQLite::Database db(path_database.c_str(), SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

  db.exec("DROP TABLE IF EXISTS " + name);

  //---------------------------
}

//Retrieving function
vector<string> ELE_database::retrieve_all_table(){
  //---------------------------

  SQLite::Database db(path_database.c_str(), SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

  SQLite::Statement query(db, "SELECT * FROM sqlite_master where type='table'");
  vector<string> vec_table;
  while (query.executeStep()){
    vec_table.push_back(query.getColumn(1));
  }

  //---------------------------
  return vec_table;
}
