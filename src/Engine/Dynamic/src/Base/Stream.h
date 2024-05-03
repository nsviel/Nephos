#pragma once

#include <GUI/Element/Media/Stream.h>
#include <Data/src/Base/Set.h>
#include <Utility/Specific/Common.h>

namespace dat::base{class Set;}
namespace gui::element{class Stream;}
namespace gui_element = gui::element;
namespace utl::media{class Image;}


namespace dyn::base{

class Stream
{
public:
  //Constructor / Destructor
  Stream(){}
  ~Stream(){}

  //Main function

protected:
  vector<gui_element::Stream*> vec_stream;
  vector<utl::media::Image*> vec_image;
};

}
