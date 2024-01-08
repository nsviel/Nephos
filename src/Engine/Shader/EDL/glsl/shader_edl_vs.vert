#version 450
//#extension GL_EXT_debug_printf : enable

layout(location = 0) in vec3 in_position;
layout(location = 4) in vec2 in_tex_coord;
layout(location = 4) out vec2 frag_tex_coord;

void main(){
  //---------------------------

  gl_Position = vec4(in_position.xy, 0.0, 1.0);
  frag_tex_coord = in_tex_coord;

//  float myfloat = 999;
//debugPrintfEXT("[SHADER] Shader value is %f", myfloat);

    //---------------------------
}
