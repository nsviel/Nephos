#include "Arcball.h"


namespace eng::camera::mode{

//Constructor / Destructor
Arcball::Arcball(util::element::Window* utl_window) : Base(utl_window){
  //---------------------------

  this->origin = vec3(0, 0, 0);

  //---------------------------
}
Arcball::~Arcball(){}

//Camera movement
void Arcball::camera_forward(eng::data::Camera* camera, float speed){
  //---------------------------

  //camera->cam_P += camera->cam_F * speed;
  this->displace_camera_COM(camera, vec3(0, speed, 0));

  //---------------------------
}
void Arcball::camera_backward(eng::data::Camera* camera, float speed){
  //---------------------------

  //camera->cam_P -= camera->cam_F * speed;
  this->displace_camera_COM(camera, vec3(0, -speed, 0));

  //---------------------------
}
void Arcball::camera_right(eng::data::Camera* camera, float speed){
  //---------------------------

  //vec2 angle =vec2(-speed / 10, 0);
  //this->rotate_by_angle(camera, angle);
  this->displace_camera_COM(camera, vec3(speed, 0, 0));

  //---------------------------
}
void Arcball::camera_left(eng::data::Camera* camera, float speed){
  //---------------------------

  //vec2 angle =vec2(speed / 10, 0);
  //this->rotate_by_angle(camera, angle);
  this->displace_camera_COM(camera, vec3(-speed, 0, 0));

  //---------------------------
}
void Arcball::camera_up(eng::data::Camera* camera, float speed){
  //---------------------------

  this->displace_camera_COM(camera, vec3(0, 0, speed));

  //---------------------------
}
void Arcball::camera_down(eng::data::Camera* camera, float speed){
  //---------------------------

  this->displace_camera_COM(camera, vec3(0, 0, -speed));

  //---------------------------
}
void Arcball::camera_mouse(eng::data::Camera* camera){
  //---------------------------

  vec2 mouse_pose = utl_window->get_mouse_pose();
  vec2 window_dim = utl_window->get_window_dim();
  vec2 window_center = utl_window->get_window_center();

  // step 1 : Calculate the amount of rotation given the mouse movement.
  float deltaAngleX = (2 * M_PI / window_dim.x); // a movement from left to right = 2*PI = 360 deg
  float deltaAngleY = (M_PI / window_dim.y);  // a movement from top to bottom = PI = 180 deg
  float xAngle = float(window_center.x - mouse_pose.x) * deltaAngleX * camera->arcball_mouse_sensibility.x;
  float yAngle = float(window_center.y - mouse_pose.y) * deltaAngleY * camera->arcball_mouse_sensibility.y;
  vec2 angle = vec2(xAngle, yAngle);

  //Apply movement
  utl_window->set_mouse_pose(utl_window->get_window_center());
  this->rotate_by_angle(camera, angle);

  //---------------------------
}
void Arcball::camera_zoom(eng::data::Camera* camera, float speed){
  //---------------------------

  // Perspective zoom
  vec3 cam_forwardMove = camera->cam_F * speed * camera->speed_move * vec3(0.1, 0.1, 0.1);

  vec3 new_pose = camera->cam_P + cam_forwardMove;

  // Define the minimum distance to the COM to avoid getting too close
  float minDistanceToCOM = 0.1;

  // Check if the new pose is within the allowed range
  if (glm::distance(new_pose, camera->cam_COM) > minDistanceToCOM) {
      camera->cam_P = new_pose;
  }

  //---------------------------
}

//Camera matrix
mat4 Arcball::compute_camera_view(eng::data::Camera* camera){
  mat4 cam_view;
  //---------------------------

  //Compute camera
  camera->cam_F = camera->cam_COM - camera->cam_P;
  camera->cam_U = normalize(cross(camera->cam_R, camera->cam_F));

  //Compute view matrix
  cam_view = lookAt(camera->cam_P, camera->cam_COM, camera->cam_U);

  //---------------------------
  return cam_view;
}

//Subfunction
void Arcball::rotate_by_angle(eng::data::Camera* camera, vec2 angle){
  //---------------------------

  // Get the homogenous position of the camera and pivot point
  vec4 cam_P(camera->cam_P.x, camera->cam_P.y, camera->cam_P.z, 1);
  vec4 cam_COM(camera->cam_COM.x, camera->cam_COM.y, camera->cam_COM.z, 1);
  vec4 cam_R(camera->cam_R.x, camera->cam_R.y, camera->cam_R.z, 1);

  // step 2: Rotate the camera around the pivot point on the first axis.
  mat4x4 Rz(1.0f);
  Rz = glm::rotate(Rz, angle.x, vec3(0, 0, 1));
  cam_P = (Rz * (cam_P - cam_COM)) + cam_COM;
  camera->cam_R = Rz * cam_R;

  // Ensure bottom of camera viewport stays above z = 0
  if (cam_P.z - camera->clip_near < 0.0f) {
    cam_P.z = camera->clip_near;
  }

  // Step 3: Rotate the camera around the pivot point on the second axis.
  mat4x4 Rr(1.0f);
  // Consider the offset in rotation by using cam_COM as the rotation pivot
  Rr = glm::rotate(Rr, angle.y, vec3(cam_R.x, cam_R.y, 0));
  camera->cam_P = (Rr * (cam_P - cam_COM)) + cam_COM;

  // Ensure bottom of camera viewport stays above z = 0
  if (camera->cam_P.z - camera->clip_near < 0.0f) {
    camera->cam_P.z = camera->clip_near;
  }

  //---------------------------
}
void Arcball::displace_camera_COM(eng::data::Camera* camera, const vec3& displacement){
  //---------------------------

  // Extract the camera's forward, right, and up vectors
  vec3 forward = normalize(camera->cam_F);
  vec3 right = normalize(camera->cam_R);
  vec3 up = normalize(camera->cam_U);

  // Displace camera COM
  vec3 local_displacement = vec3(0);
  local_displacement += displacement.y * forward;
  local_displacement += displacement.x * right;
  local_displacement += displacement.z * vec3(0.0f, 0.0f, 1.0f);

  // Keep the z position constant
  if(displacement.z == 0){
    local_displacement.z = 0.0f;
  }
  vec3 COM_new = camera->cam_COM + local_displacement;

  // Displace camera accordingly
  if(COM_new.z >= 0){
    camera->cam_P += local_displacement;
    camera->cam_COM = COM_new;
  }

  //---------------------------
}


}
