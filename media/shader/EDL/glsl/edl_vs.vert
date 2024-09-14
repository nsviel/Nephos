#version 450
//#extension GL_EXT_debug_printf : enable

//Input
layout(location = 0) in vec3 in_xyz;
layout(location = 2) in vec2 in_uv;

//Ouput
layout(location = 4) out vec2 frag_uv;


void main(){
  //---------------------------

  gl_Position = vec4(in_xyz.xy, 0.0, 1.0);
  frag_uv = in_uv;

//  float myfloat = 999;
//debugPrintfEXT("[SHADER] Shader value is %f", myfloat);

    //---------------------------
}
