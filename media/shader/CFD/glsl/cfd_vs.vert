#version 450

//Input
layout(location = 0) in ivec2 ipos;

//Ouput
layout(location = 0) out vec3 frag_rgb;

//Uniform
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 f00; // far plane frustum corners
uniform vec3 f10; // far plane frustum corners
uniform vec3 f11; // far plane frustum corners
uniform vec3 f01; // far plane frustum corners
uniform float tan_half_depth_hfov; // fovs for depth camera
uniform float tan_half_depth_vfov; // fovs for depth camera
uniform float tan_half_color_hfov; // fovs for color camera
uniform float tan_half_color_vfov; // fovs for color camera
uniform float offsX = 0.014;
uniform float offsY = -0.004;
uniform float z_far; // far plane distance given in meters
uniform int points_width; // number of points
uniform int points_height; // number of points

//Sampler
layout(binding = 0) uniform sampler2D tex_depth;
layout(binding = 1) uniform sampler2D tex_color;


void main(){
  //---------------------------

  vec2 tpos = vec2(float(ipos.x) / float(points_width), float(ipos.y) / float(points_height));

  // Sample the depth value from the depth texture and normalize to meters
  float depth = 65.535 * texture(tex_depth, vec2(tpos.x, 1 - tpos.y)).r / z_far;

  // Compute the aligned color position in the color texture space
  vec2 cpos;
  cpos.x = 0.5 + (tpos.x - 0.5) * tan_half_depth_hfov / tan_half_color_hfov + offsX / (2 * depth * tan_half_color_hfov);
  cpos.y = 0.5 + (tpos.y - 0.5) * tan_half_depth_vfov / tan_half_color_vfov + offsY / (2 * depth * tan_half_color_vfov);

  // Transform depth to 3D world position using the frustum corners and model matrix
  vec4 world_pos = model * vec4(depth * mix(mix(f00, f10, tpos.x), mix(f01, f11, tpos.x), tpos.y), 1);

  // Sample the color from the color texture
  frag_rgb = texture(tex_color, vec2(cpos.x, 1 - cpos.y));

  // Compute final position in clip space
  gl_Position = projection * view * world_pos;

  //---------------------------
}
