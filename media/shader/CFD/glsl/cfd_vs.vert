#version 450

//Input
layout(location = 0) in ivec2 ipos;

//Ouput
layout(location = 0) out vec3 frag_rgb;

//Uniform
uniform float tan_half_depth_hfov; // fovs for depth camera
uniform float tan_half_depth_vfov; // fovs for depth camera
uniform float tan_half_color_hfov; // fovs for color camera
uniform float tan_half_color_vfov; // fovs for color camera
uniform float offsX = 0.014;
uniform float offsY = -0.004;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float far_plane; // far plane distance given in meters
uniform vec3 f00; // far plane frustum corners
uniform vec3 f10; // far plane frustum corners
uniform vec3 f11; // far plane frustum corners
uniform vec3 f01; // far plane frustum corners
uniform int points_width; // number of points
uniform int points_height; // number of points
uniform mat4 mcubes_model_inv; // marching cubes info

//Sampler
layout(binding = 0) uniform sampler2D tex_depth;
layout(binding = 1) uniform sampler2D tex_color;


void main(){
  //---------------------------

  vec2 tpos = vec2(float(ipos.x) / float(points_width), float(ipos.y) / float(points_height));

  // depth is normalized into the range from the camera to the far plane
  // Note: 65.535m = (2^16 - 1)mm / 1000(mm/m)
  float depth = 65.535 * texture(tex_depth, vec2(tpos.x, 1 - tpos.y)).r / far_plane;

  // align
  // TODO: add bounds check?? texture wrap probably works for now
  vec2 cpos = vec2(0, 0);
  cpos.x = 0.5 + (tpos.x - 0.5) * tan_half_depth_hfov / tan_half_color_hfov + offsX / (2 * depth * tan_half_color_hfov);
  cpos.y = 0.5 + (tpos.y - 0.5) * tan_half_depth_vfov / tan_half_color_vfov + offsY / (2 * depth * tan_half_color_vfov);

  vec4 pos = model * vec4(depth * mix(mix(f00, f10, tpos.x), mix(f01, f11, tpos.x), tpos.y), 1);
  // TODO: consider moving 0.5 offset somewhere more sensible
  vec4 mcubes_pos = mcubes_model_inv * pos + vec4(0.5, 0.5, 0.5, 0);

  // adjust point size based on distance to camera
  //vec4 pos_cs = view * model * vec4(pos, 1);
  //gl_PointSize = clamp(10 - 0.1f * length(pos_cs.xyz), 1, 10);

  // direct point cloud rendering output
  frag_rgb = texture(tex_color, vec2(cpos.x, 1 - cpos.y));
  // color = mcubes_pos;
  gl_Position = projection * view * pos;

  //---------------------------
}
