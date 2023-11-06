#ifndef LOADER_H
#define LOADER_H

#include <ELE_specific/Struct/struct_data_file.h>
#include <ELE_specific/Struct/struct_object.h>
#include <ELE_specific/File/Directory.h>
#include <ELE_specific/File/Zenity.h>
#include <string>
#include <vector>

class ENG_data;
class Format;
class ENG_scene;


class Loader
{
public:
  //Constructor / Destructor
  Loader(ENG_data* eng_data);
  ~Loader();

public:
  //Main functions
  Object* load_object(std::string path);
  std::vector<Object*> load_objects(std::vector<std::string> path);
  void load_by_zenity();

  //Subfunctions
  void transfert_data(Object* object, Data_file* eng_data);

private:
  Format* formatManager;
  ENG_scene* eng_scene;

  std::string path_current_dir;
  int ID;
};

#endif
