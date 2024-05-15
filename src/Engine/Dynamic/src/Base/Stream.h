#pragma once

#include <GUI/Media/Stream.h>
#include <Data/src/Base/Set.h>
#include <Utility/Specific/Common.h>

namespace dat::base{class Set;}
namespace gui::media{class Stream;}
namespace utl::media{class Image;}
namespace gui_media = gui::media;


namespace dyn::base{

class Stream
{
public:
  //Constructor / Destructor
  Stream(){}
  ~Stream(){}

  //Main function

protected:
  vector<gui_media::Stream*> vec_stream;
  vector<utl::media::Image*> vec_image;
};

}
