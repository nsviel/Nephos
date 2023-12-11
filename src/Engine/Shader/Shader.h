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
  inline eng::shader::EDL_shader* get_edl_shader(){return edl_shader;}
  inline eng::shader::PSR_shader* get_psr_shader(){return psr_shader;}
  inline eng::shader::SCE_shader* get_sce_shader(){return sce_shader;}

private:
  eng::shader::EDL_shader* edl_shader;
  eng::shader::PSR_shader* psr_shader;
  eng::shader::SCE_shader* sce_shader;
};

}
