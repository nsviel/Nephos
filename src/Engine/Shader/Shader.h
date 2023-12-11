#pragma once

#include <Utility/Specific/common.h>

class Engine;
class EDL_shader;
class PSR_shader;
class SCE_shader;


namespace eng::shader{

class Shader
{
public:
  Shader(Engine* engine);
  ~Shader();

public:
  inline EDL_shader* get_edl_shader(){return edl_shader;}
  inline PSR_shader* get_psr_shader(){return psr_shader;}
  inline SCE_shader* get_sce_shader(){return sce_shader;}

private:
  EDL_shader* edl_shader;
  PSR_shader* psr_shader;
  SCE_shader* sce_shader;
};

}
