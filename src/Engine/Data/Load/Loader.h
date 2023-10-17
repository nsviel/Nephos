#ifndef LOADER_H
#define LOADER_H

#include <Specific/Struct/struct_data_file.h>
#include <Specific/Struct/struct_object.h>
#include <Specific/File/Directory.h>
#include <Specific/File/Zenity.h>
#include <string>
#include <vector>

class Data;
class Format;
class Scene;


class Loader
{
public:
  //Constructor / Destructor
  Loader(Data* data);
  ~Loader();

public:
  //Main functions
  Object* load_object(std::string path);
  std::vector<Object*> load_objects(std::vector<std::string> path);
  void load_by_zenity();

  //Subfunctions
  void transfert_data(Object* object, Data_file* data);

private:
  Format* formatManager;
  Scene* sceneManager;

  std::string path_current_dir;
  int ID;
};

#endif
