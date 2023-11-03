#ifndef GPU_DATA_H
#define GPU_DATA_H

#include <ELE_specific/common.h>

class VK_engine;
class VK_data;


class GPU_data
{
public:
  //Constructor / Destructor
  GPU_data(VK_engine* vk_engine);
  ~GPU_data();

public:
  //Main function
  void insert_object_in_engine(Object* object);
  void insert_glyph_in_engine(Object* object);
  void remove_object_in_engine(Object* object);

  inline bool* get_update_scene(){return &update_scene;}

private:
  VK_data* vk_data;

  std::list<Object*> list_scene;
  std::list<Object*> list_glyph;
  bool update_scene;
};

#endif
