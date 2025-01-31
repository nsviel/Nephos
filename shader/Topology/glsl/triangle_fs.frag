#version 450

//Input
layout(location = 0) in vec3 frag_rgb;
layout(location = 1) in vec2 frag_uv;

//Ouput
layout(location = 0) out vec4 out_rgb;

//Uniform
layout(binding = 5) uniform Param{
  bool has_texture;
};

//Sampler
layout(binding = 10) uniform sampler2D tex_sampler;


void main(){
  //---------------------------

  if(has_texture){
    out_rgb = texture(tex_sampler, frag_uv);
    //out_rgb = vec4(0, 1, 0, 1.0);
  }else{
    out_rgb = vec4(frag_rgb, 1.0);
  }

  //---------------------------
}
