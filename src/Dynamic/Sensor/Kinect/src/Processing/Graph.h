#pragma once

namespace k4n{class Node;}
namespace k4n::base{class Sensor;}
namespace k4n::processing::cloud{class Data;}
namespace k4n::processing::image{class Data;}
namespace dyn::prc::image{class Operation;}
namespace dyn::prc::cloud{class Operation;}
namespace dat::sensor{class Pool;}


namespace k4n{

class Graph
{
public:
  //Constructor / Destructor
  Graph(k4n::Node* node_k4n);
  ~Graph();

public:
  //Main function
  void init(k4n::base::Sensor& sensor);
  void run(k4n::base::Sensor& sensor);

private:
  k4n::Node* node_k4n;
  k4n::processing::image::Data* k4n_image;
  k4n::processing::cloud::Data* k4n_cloud;

  dyn::prc::image::Operation* dyn_ope_image;
  dyn::prc::cloud::Operation* dyn_ope_cloud;
  dat::sensor::Pool* thr_pool;
};

}
