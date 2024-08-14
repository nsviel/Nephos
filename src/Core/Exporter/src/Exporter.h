#pragma once

#include <IO/src/Export/Structure/Base.h>
#include <string>
#include <vector>

namespace io::exp{class Node;}
namespace io::exp{class Structure;}
namespace io::base{class Exporter;}
namespace io::base{class Recorder;}
namespace dat::base{class Entity;}


namespace io{

class Exporter
{
public:
  //Constructor / Destructor
  Exporter(io::exp::Node* node_exporter);
  ~Exporter();

public:
  //Main function
  void export_entity(dat::base::Entity* entity, std::string path);

  //Subfunction
  void init_path();
  void export_with_config(io::exporter::Base* exporter, dat::base::Entity* entity, std::string path);
  void insert_exporter(io::exporter::Base* exporter);
  void update_current_path(utl::base::Element* element);
  bool is_format_supported(std::string format);
  bool is_current_config(dat::base::Entity* entity);
  bool is_recording(utl::base::Element* element);
  std::vector<std::string> get_supported_format();
  std::vector<io::exporter::Encoding> get_supported_encoding(std::string format);

private:
  io::exp::Structure* io_struct;

  std::vector<io::exporter::Base*> vec_exporter;
};

}
