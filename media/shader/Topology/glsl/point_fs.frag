#version 450

//Input
layout(location = 0) in vec3 frag_xyz;
layout(location = 1) in vec3 frag_rgb;

//Ouput
layout(location = 0) out vec4 out_rgb;


void main(){
  //---------------------------

  //Position
  //out_position = vec4(frag_xyz, 1);

  //Color
  out_rgb = vec4(frag_rgb, 1);

  //---------------------------
}
