#version 450

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
layout(binding = 5) uniform Param{
  float depth_scale;
  float depth_offset;
  int tex_depth_width;
  int tex_depth_height;
};

//Sampler
layout(binding = 0) uniform sampler2D tex_depth;
layout(binding = 1) uniform sampler2D tex_color;


void main(){
  //---------------------------

  // Convert pixel coordinates to normalized device coordinates
  vec2 tpos = gl_FragCoord.xy / vec2(tex_depth_width, tex_depth_height);

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

  //---------------------------
}
