#pragma once

#include <IO/Base/Exporter.h>
#include <memory>
#include <string>
#include <vector>

namespace io::exp{class Node;}
namespace io::exp{class Structure;}
namespace io::base{class Exporter;}
namespace io::base{class Recorder;}
namespace dat::base{class Entity;}


namespace io::exp{

class Exporter
{
public:
  //Constructor / Destructor
  Exporter(io::exp::Node* node_exporter);
  ~Exporter();

public:
  //Main function
  void export_entity(std::shared_ptr<dat::base::Entity> entity, std::string path);

  //Subfunction
  void init_path();
  void export_with_config(io::base::Exporter* exporter, std::shared_ptr<dat::base::Entity> entity, std::string path);
  void insert_exporter(io::base::Exporter* exporter);
  void update_current_path(std::shared_ptr<utl::base::Element> element);
  bool is_format_supported(std::string format);
  bool is_current_config(std::shared_ptr<dat::base::Entity> entity);
  bool is_recording(std::shared_ptr<utl::base::Element> element);
  std::vector<std::string> get_supported_format();
  std::vector<io::exp::Encoding> get_supported_encoding(std::string format);

private:
  io::exp::Structure* io_struct;

  std::vector<io::base::Exporter*> vec_exporter;
};

}
