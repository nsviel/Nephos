#include "Keypoint.h"


namespace slam::glyph{

//Constructor / destructor
Keypoint::Keypoint(){
  //---------------------------

  this->name = "keypoint";
  this->color = glm::vec4(0.7f, 0.1f, 0.1f, 1.0f);
  this->is_visible = false;

  //---------------------------
}

void Keypoint::create_glyph(Cloud* cloud){
  Glyph keypoint;
  //---------------------------

  //Create glyph
  keypoint.name = "keypoint";
  keypoint.draw_point_size = 10;
  keypoint.draw_type = utl::topology::POINT;
  keypoint.unicolor = color;
  keypoint.is_visible = is_visible;

  //---------------------------
  cloud->glyphs.insert({"keypoint", keypoint});
}
void Keypoint::update_keypoint_location(Cloud* cloud){
  Glyph* keypoint = &cloud->glyphs["keypoint"];
  //---------------------------

  std::vector<glm::vec3>& XYZ_key = keypoint->xyz;
  std::vector<glm::vec4>& RGB_key = keypoint->rgb;
  std::vector<float>& ts_key = keypoint->ts;

  //Construct glyph
  RGB_key.clear();
  for(int i=0; i<ts_key.size(); i++){
    glm::vec4 rgb = glm::vec4(ts_key[i], 1 - ts_key[i], color[2], 1);
    RGB_key.push_back(rgb);
  }

  //---------------------------
}
void Keypoint::update_keypoint_normal(Cloud* cloud){
  Glyph* normal = &cloud->glyphs["normal"];
  Glyph* keypoint = &cloud->glyphs["keypoint"];
  //---------------------------

  //Get vector values
  std::vector<glm::vec3>& xyz_k = keypoint->xyz;
  std::vector<glm::vec3>& Nxyz_k = keypoint->Nxyz;
  std::vector<glm::vec3>& xyz_n = normal->xyz;
  std::vector<glm::vec4>& rgb_n = normal->rgb;

  //Check vector length
  if(xyz_k.size() == 0 || Nxyz_k.size() == 0 || Nxyz_k.size() != xyz_k.size()){
    return;
  }

  //Clear old normal values
  xyz_n.clear();
  rgb_n.clear();

  //Construct normal
  float lgt = 0.05 * normal->draw_point_size;
  for(int i=0; i<xyz_k.size(); i++){
    glm::vec3& xyz = xyz_k[i];
    glm::vec3& nxyz = Nxyz_k[i];

    glm::vec3 n_vec = glm::vec3(xyz.x + nxyz.x * lgt, xyz.y + nxyz.y * lgt, xyz.z + nxyz.z * lgt);

    xyz_n.push_back(xyz);
    xyz_n.push_back(n_vec);

    rgb_n.push_back(normal->unicolor);
    rgb_n.push_back(normal->unicolor);
  }

  //---------------------------
}

}
