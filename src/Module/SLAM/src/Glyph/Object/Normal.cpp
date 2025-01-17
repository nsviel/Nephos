#include "Normal.h"

#include "../../Base/SLAM_utility.h"


namespace slam::glyph{

//Constructor / destructor
Normal::Normal(){
  //---------------------------

  this->name = "normal";
  this->width = 1;
  this->size = 1;
  this->is_visible = false;
  this->color = glm::vec4(0.11f, 0.35f, 0.69f, 1.0f);

  //---------------------------
}
Normal::~Normal(){}

void Normal::create_glyph(Cloud* cloud){
  Glyph normal;
  //---------------------------

  //Create glyph
  normal.name = "normal";
  normal.draw_line_width = width;
  normal.draw_type = utl::topology::LINE;
  normal.unicolor = color;
  normal.is_visible = is_visible;

  //---------------------------
  cloud->glyphs.insert({"normal", normal});
}
void Normal::update_normal_cloud(Cloud* cloud){
  glyph->draw_point_size = size;
  //---------------------------

  //Get vector values
  std::vector<glm::vec3>& xyz_s = cloud->xyz;
  std::vector<glm::vec3>& Nxyz_s = cloud->Nxyz;
  std::vector<glm::vec3>& xyz_n = glyph->xyz;
  std::vector<glm::vec4>& rgb_n = glyph->rgb;

  //Check vector length
  if(xyz_s.size() == 0 || Nxyz_s.size() == 0 || Nxyz_s.size() != xyz_s.size()){
    return;
  }

  //Clear old glyph values
  xyz_n.clear();
  rgb_n.clear();

  //Construct glyph
  float lgt = 0.05 * glyph->draw_point_size;
  for(int i=0; i<xyz_s.size(); i++){
    glm::vec3& xyz = xyz_s[i];
    glm::vec3& nxyz = Nxyz_s[i];

    if(SLAM_utility::fct_is_nan(nxyz)) continue;

    glm::vec3 vec_n = glm::vec3(xyz.x + nxyz.x * lgt, xyz.y + nxyz.y * lgt, xyz.z + nxyz.z * lgt);

    xyz_n.push_back(xyz);
    xyz_n.push_back(vec_n);

    rgb_n.push_back(glyph->unicolor);
    rgb_n.push_back(glyph->unicolor);
  }

  //---------------------------
}
void Normal::update_normal_cloud(Cloud* cloud, std::vector<glm::vec3>& xyz_s, std::vector<glm::vec3>& Nxyz_s){
  Glyph* normal = &cloud->glyphs["normal"];
  normal->draw_point_size = size;
  //---------------------------

  //Get vector values
  std::vector<glm::vec3>& xyz_n = normal->xyz;
  std::vector<glm::vec4>& rgb_n = normal->rgb;

  //Check vector length
  if(xyz_s.size() == 0 || Nxyz_s.size() == 0 || Nxyz_s.size() != xyz_s.size()){
    return;
  }

  //Clear old normal values
  xyz_n.clear();
  rgb_n.clear();

  //Construct normal
  float lgt = 0.05 * normal->draw_point_size;
  for(int i=0; i<xyz_s.size(); i++){
    glm::vec3& xyz = xyz_s[i];
    glm::vec3& nxyz = Nxyz_s[i];

    if(SLAM_utility::fct_is_nan(nxyz)) continue;

    glm::vec3 vec_n = glm::vec3(xyz.x + nxyz.x * lgt, xyz.y + nxyz.y * lgt, xyz.z + nxyz.z * lgt);

    xyz_n.push_back(xyz);
    xyz_n.push_back(vec_n);

    rgb_n.push_back(normal->unicolor);
    rgb_n.push_back(normal->unicolor);
  }

  //---------------------------
}

}
