#version 450

//Input
layout(location = 0) in vec3 in_xyz;
layout(location = 1) in vec3 in_rgb;

//Ouput
layout(location = 0) out vec3 frag_rgb;

//Uniform
layout(binding = 0) uniform MVP{
  mat4 model;
  mat4 view;
  mat4 projection;
};
layout(binding = 1) uniform width{float point_size;};
layout(binding = 5) uniform Param{
  float depth_scale;
  float depth_offset;
  int tex_depth_width;
  int tex_depth_height;
};

//Sampler
layout(binding = 10) uniform sampler2D tex_depth;
layout(binding = 11) uniform sampler2D tex_color;


void main(){
  //---------------------------

  gl_Position = projection * view * model * vec4(in_xyz, 1.0);
  gl_PointSize = point_size;
  frag_rgb = in_rgb;

  //---------------------------
}
