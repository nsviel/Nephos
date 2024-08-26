#pragma once

namespace cam{class Entity;}
namespace dat{class Node;}
namespace dat::gph{class Node;}
namespace dat::gph{class Structure;}
namespace dat::elm{class Set;}
namespace dat::elm{class Glyph;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace utl::base{class Element;}


namespace dat::gph{

class Graph
{
public:
  //Constructor / Destructor
  Graph(dat::gph::Node* node_graph);
  ~Graph();

  //Main function
  void init();
  void loop();
  void reset();
  void clean();

  //Accesseur
  std::shared_ptr<dat::base::Set>& get_set_main();
  std::shared_ptr<dat::base::Set>& get_set_graph();
  std::shared_ptr<dat::base::Set>& get_set_scene();

private:
  dat::elm::Glyph* dat_glyph;
  dat::elm::Set* dat_set;
  dat::gph::Structure* gph_struct;
};

}
