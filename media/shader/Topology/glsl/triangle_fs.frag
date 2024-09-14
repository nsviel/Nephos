#version 450

//Input
layout(location = 0) in vec3 frag_rgb;
layout(location = 1) in vec2 frag_uv;

//Ouput
layout(location = 0) out vec4 out_rgb;

//Sampler
layout(binding = 1) uniform sampler2D tex_sampler;


void main(){
  //---------------------------

  out_rgb = vec4(frag_rgb, 1.0);
  //out_rgb = vec4(frag_uv, 0.0, 1.0);
  //out_rgb = texture(tex_sampler, frag_uv);

  //---------------------------
}
