#include "Database.h"


namespace utl::element{

//Constructor / Destructor
Database::Database(string path){
  //---------------------------

  this->db_path = path;

  //---------------------------
}
Database::~Database(){}

//Management function
void Database::create_table(string name){
  if(name == "")return;
  //---------------------------

  SQLite::Database db(db_path.c_str(), SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

  db.exec("DROP TABLE IF EXISTS " + name);
  db.exec("CREATE TABLE " + name + " (id INTEGER PRIMARY KEY, value TEXT)");

  //---------------------------
}
void Database::remove_table(string name){
  if(name == "")return;
  //---------------------------

  SQLite::Database db(db_path.c_str(), SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

  db.exec("DROP TABLE IF EXISTS " + name);

  //---------------------------
}

//Retrieving function
vector<string> Database::retrieve_all_table(){
  //---------------------------

  SQLite::Database db(db_path.c_str(), SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

  SQLite::Statement query(db, "SELECT * FROM sqlite_master where type='table'");
  vector<string> vec_table;
  while (query.executeStep()){
    vec_table.push_back(query.getColumn(1));
  }

  //---------------------------
  return vec_table;
}

}
