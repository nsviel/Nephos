#pragma once

#include <Render/src/Stream.h>
#include <Data/src/Base/Set.h>
#include <Utility/Specific/Common.h>

namespace dat::base{class Set;}
namespace rnd{class Stream;}
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
  vector<rnd::Stream*> vec_stream;
  vector<utl::media::Image*> vec_image;
};

}
