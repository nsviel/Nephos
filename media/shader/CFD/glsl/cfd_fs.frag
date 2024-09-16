#version 450

//Input
layout(location = 0) in vec3 frag_rgb;

//Ouput
layout(location = 0) out vec4 out_rgb;


void main(){
  //---------------------------

  out_rgb = vec4(frag_rgb, 1);

  //---------------------------
}
