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
layout(binding = 10) uniform sampler2D tex_color;
layout(binding = 11) uniform sampler2D tex_depth;


void main(){
  //---------------------------

  gl_Position = projection * view * model * vec4(in_xyz, 1.0);
  gl_PointSize = point_size;
  frag_rgb = in_rgb;

  debugPrintfEXT("[SHADER] %d", tex_depth_width);

/*
  vec4 colorSample = texture(tex_color, vec2(0.5));
  frag_rgb = colorSample.rgb;
*/



  // Convert pixel coordinates to normalized device coordinates
//  vec2 tpos = gl_FragCoord.xy / vec2(tex_depth_width, tex_depth_height);
/*
  // Compute color position in the color texture space
  vec2 color_pos = vec2(tpos.x, 1.0 - tpos.y); // Assuming the color texture uses a different coordinate system

  // Sample color from the color texture
  frag_rgb = texture(tex_color, color_pos).rgb;

  // Sample depth value from the depth texture and scale to meters
  float depth = texture(tex_depth, tpos).r * depth_scale + depth_offset;

  // Compute 3D position
  vec4 world_pos = model * vec4(depth * vec3(tpos.x, tpos.y, 1.0), 1.0);

  // Compute final position in clip space
  gl_Position = projection * view * world_pos;

  // Optional: Compute point size based on distance
  // gl_PointSize = clamp(10.0 - 0.1 * depth, 1.0, 10.0);
*/
  //---------------------------
}
