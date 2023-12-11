#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Shader/Namespace.h>

class Engine;


namespace eng::shader{

class Shader
{
public:
  Shader(Engine* engine);
  ~Shader();

public:
  inline eng::shader::EDL* get_edl_shader(){return edl_shader;}
  inline eng::shader::PSR* get_psr_shader(){return psr_shader;}
  inline eng::shader::SCE* get_sce_shader(){return sce_shader;}

private:
  eng::shader::EDL* edl_shader;
  eng::shader::PSR* psr_shader;
  eng::shader::SCE* sce_shader;
};

}
