#pragma once

#include "../../../Scene/Glyph/Base/Glyph_source.h"
#include "../Base/common.h"

class SLAM;
class SLAM_map;
class Object;


namespace slam::glyph{

class SLAM_glyph
{
public:
  //Constructor / Destructor
  SLAM_glyph(SLAM* slam);
  ~SLAM_glyph();

public:
  //Main function
  void update_glyph(Collection* collection, Cloud* cloud);
  void update_visibility(Cloud* cloud);
  void reset_glyph();

  //Subfunctions$
  void update_glyph_keypoint(Cloud* cloud);
  void update_glyph_nn(Cloud* cloud);
  void update_glyph_matching(Cloud* cloud);
  void update_glyph_normal(Cloud* cloud);
  void update_glyph_map();
  void update_glyph_car(Collection* collection);
  void update_glyph_trajectory(Collection* collection);

  //Accesseur
  Glyph* get_glyph_byName(std::string querry);

  inline bool* get_with_keypoint(){return &with_keypoint;}
  inline bool* get_with_neighbor(){return &with_neighbor;}
  inline bool* get_with_matching(){return &with_matching;}
  inline bool* get_with_trajectory(){return &with_trajectory;}
  inline bool* get_with_localmap(){return &with_localmap;}
  inline bool* get_with_localcloud(){return &with_localcloud;}
  inline bool* get_with_car(){return &with_car;}

private:
  SLAM_map* slam_map;
  Object* objectManager;

  std::list<Glyph*>* list_glyph;

  bool with_keypoint;
  bool with_neighbor;
  bool with_matching;
  bool with_trajectory;
  bool with_localmap;
  bool with_localcloud;
  bool with_car;
};


}
