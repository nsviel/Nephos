#include "Target.h"


namespace glyph::camera{

//Constructor / destructor
Target::Target(Engine* engine) : Glyph(engine){
  //---------------------------

  this->color = vec4(1.0f, 1.0f, 1.0f, 0.5f);
  this->scale = 0.025;

  //---------------------------
}
Target::~Target(){}

//Main function
void Target::create(){
  if(vec_object.size() != 0) return;
  //---------------------------

  entity::Object* object = new entity::Object(engine);
  object->name = "camera_target";
  object->data->draw_line_width = 2;
  object->is_visible = true;
  object->draw_type_name = "line";
  object->is_permanent = true;
  object->unicolor = vec4(1, 1, 1, 0.2f);
  this->vec_object.push_back(object);
  this->construct(object);

  //---------------------------
}
void Target::update_glyph(entity::Entity* entity){
  entity::Object* object = vec_object[0];
  //---------------------------

  if(entity::Camera* camera = dynamic_cast<entity::Camera*>(entity)){
    camera->mode == CAMERA_MODE_ARCBALL ? is_visible = true : is_visible = false;

    glm::mat4 translation(1.0);
    translation[0][3] = camera->cam_COM.x;
    translation[1][3] = camera->cam_COM.y;
    translation[2][3] = camera->cam_COM.z;
    object->model = translation;
    object->is_visible = is_visible;
  }

  //---------------------------
}
void Target::construct(entity::Object* object){
  vector<vec3>& XYZ = object->xyz;
  vector<vec4>& RGB = object->rgb;
  //---------------------------

  XYZ.clear();
  RGB.clear();

  //X axis
  XYZ.push_back(vec3(-1*scale, 0, 0));
  XYZ.push_back(vec3(1*scale, 0, 0));
  RGB.push_back(color);
  RGB.push_back(color);

  //Y axis
  XYZ.push_back(vec3(0, -1*scale, 0));
  XYZ.push_back(vec3(0, 1*scale, 0));
  RGB.push_back(color);
  RGB.push_back(color);

  //---------------------------
}

}
