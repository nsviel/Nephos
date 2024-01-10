#pragma once

#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>


namespace eng::camera::mode{

class Base
{
public:
  Base(util::element::Window* utl_window);
  ~Base();

public:

private:
  util::element::Window* utl_window;
};

}
