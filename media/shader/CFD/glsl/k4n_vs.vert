#version 450

//Input
layout(location = 1) in vec3 in_rgb;

//Ouput
layout(location = 0) out vec4 frag_rgb;

//Uniform
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//Sampler
layout(binding = 0) uniform sampler2D tex_depth;


void main(){
  //---------------------------

  //Location
  ivec2 tex_size = imageSize(tex_depth);
  ivec2 coord_pixel = ivec2(gl_VertexID % tex_size.x, gl_VertexID / tex_size.x);
  vec3 xyz = imageLoad(tex_depth, coord_pixel).xyz;

  gl_Position = projection * view * vec4(xyz, 1);

  //Color
  frag_rgb = in_rgb;

  //---------------------------
}
