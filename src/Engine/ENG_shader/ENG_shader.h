#ifndef SHADER_H
#define SHADER_H

#include <ELE_specific/common.h>

class Engine;
class EDL_shader;
class PSR_shader;
class SCE_shader;


class ENG_shader
{
public:
  ENG_shader(Engine* engine);
  ~ENG_shader();

public:
  inline EDL_shader* get_edl_shader(){return edl_shader;}
  inline PSR_shader* get_psr_shader(){return psr_shader;}
  inline SCE_shader* get_sce_shader(){return sce_shader;}

private:
  EDL_shader* edl_shader;
  PSR_shader* psr_shader;
  SCE_shader* sce_shader;
};

#endif
