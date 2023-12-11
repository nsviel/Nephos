#include "UTL_database.h"


namespace util::element{

//Constructor / Destructor
UTL_database::UTL_database(string path){
  //---------------------------

  this->db_path = path;

  //---------------------------
}
UTL_database::~UTL_database(){}

//Management function
void UTL_database::create_table(string name){
  if(name == "")return;
  //---------------------------

  SQLite::Database db(db_path.c_str(), SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

  db.exec("DROP TABLE IF EXISTS " + name);
  db.exec("CREATE TABLE " + name + " (id INTEGER PRIMARY KEY, value TEXT)");

  //---------------------------
}
void UTL_database::remove_table(string name){
  if(name == "")return;
  //---------------------------

  SQLite::Database db(db_path.c_str(), SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

  db.exec("DROP TABLE IF EXISTS " + name);

  //---------------------------
}

//Retrieving function
vector<string> UTL_database::retrieve_all_table(){
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
