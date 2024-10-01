#version 450
#extension GL_EXT_debug_printf : enable

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
layout(binding = 22, rgba32f) readonly uniform image2D tex_cloud;


void main(){
  //---------------------------

  gl_Position = projection * view * model * vec4(in_xyz, 1.0);
  gl_PointSize = point_size;
  frag_rgb = in_rgb;

  //debugPrintfEXT("[SHADER] %d", tex_depth_width);


  ivec2 cloud_size = imageSize(tex_cloud);
  ivec2 pixel_coord = ivec2(gl_VertexIndex % cloud_size.x, gl_VertexIndex / cloud_size.x);
  vec3 vertex_position = imageLoad(tex_cloud, pixel_coord).xyz;
  gl_Position = projection * view * model * vec4(vertex_position, 1);





  //---------------------------
}
