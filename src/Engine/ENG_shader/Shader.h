#ifndef SHADER_H
#define SHADER_H

#include <ELE_specific/common.h>

class Engine;
class EDL_shader;
class PSR_shader;
class CAN_shader;
class SCE_shader;


class Shader
{
public:
  Shader(Engine* engine);
  ~Shader();

public:
  inline EDL_shader* get_edl_shader(){return edl_shader;}
  inline PSR_shader* get_psr_shader(){return psr_shader;}
  inline CAN_shader* get_can_shader(){return can_shader;}
  inline SCE_shader* get_sce_shader(){return sce_shader;}

private:
  EDL_shader* edl_shader;
  PSR_shader* psr_shader;
  CAN_shader* can_shader;
  SCE_shader* sce_shader;
};

#endif
