#version 450

//Input
layout(location = 1) in vec3 in_rgb;

//Ouput
layout(location = 0) out vec3 frag_rgb;

//Uniform
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float depth_scale; // Scale to convert depth values to meters
uniform float depth_offset; // Offset for depth correction
uniform int tex_depth_width; // Width of the point cloud (depth image width)
uniform int tex_depth_height; // Height of the point cloud (depth image height)

//Sampler
layout(binding = 0) uniform sampler2D tex_depth;
layout(binding = 1) uniform sampler2D tex_color;


void main(){
  //---------------------------

  // Convert pixel coordinates to normalized device coordinates
  vec2 tpos = vec2(float(ipos.x) / float(tex_depth_width), float(ipos.y) / float(tex_depth_height));


  // Compute color position in the color texture space
  vec2 color_pos = vec2(tpos.x, 1.0 - tpos.y);

  // Sample color from the color texture
  frag_rgb = texture(tex_color, color_pos).rgb;


  // Sample depth value from the depth texture and scale to meters
  float depth = texture(tex_depth, tpos).r * depth_scale + depth_offset;

  // Compute 3D position
  vec4 world_pos = model * vec4(depth * vec3(tpos.x, tpos.y, 1.0), 1.0);

  // Compute final position in clip space
  gl_Position = projection * view * world_pos;

  // Compute point size based on distance (optional)
  // gl_PointSize = clamp(10.0 - 0.1 * depth, 1.0, 10.0);

  //---------------------------
}
