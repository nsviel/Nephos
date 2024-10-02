#version 450
#extension GL_EXT_debug_printf : enable

//Input
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

//Storage
layout(binding = 22, rgba32f) readonly uniform image2D tex_cloud;


void main(){
  //---------------------------

  ivec2 cloud_size = imageSize(tex_cloud);
  ivec2 pixel_coord = ivec2(gl_VertexIndex % cloud_size.x, gl_VertexIndex / cloud_size.x);
  vec3 vertex_position = imageLoad(tex_cloud, pixel_coord).xyz;
  gl_Position = projection * view * model * vec4(vertex_position, 1);
  gl_PointSize = point_size;

  frag_rgb = in_rgb;

  //---------------------------
}
