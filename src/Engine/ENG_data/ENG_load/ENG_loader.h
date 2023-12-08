#ifndef LOADER_H
#define LOADER_H

#include <UTL_base/Struct_file.h>
#include <UTL_base/Struct_object.h>
#include <UTL_file/Directory.h>
#include <UTL_file/Zenity.h>
#include <string>
#include <vector>

class ENG_data;
class ENG_format;
class ENG_scene;


class ENG_loader
{
public:
  //Constructor / Destructor
  ENG_loader(ENG_data* eng_data);
  ~ENG_loader();

public:
  //Main functions
  data::Object* load_object(std::string path);
  std::vector<data::Object*> load_objects(std::vector<std::string> path);
  void load_by_zenity();

  //Subfunctions
  void transfert_data(data::Object* object, data::File* eng_data);

private:
  ENG_format* eng_format;
  ENG_scene* eng_scene;

  std::string path_current_dir;
  int ID;
};

#endif
