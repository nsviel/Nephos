#version 450

//Input
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;

//Ouput
layout(location = 0) out vec3 frag_color;

//Uniform
layout(binding = 0) uniform MVP{mat4 value;} uniform_mvp;


void main(){
  //---------------------------

  gl_Position = uniform_mvp.value * vec4(in_position, 1.0);
  frag_color = in_color;

  //---------------------------
}
