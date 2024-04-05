#include "Importer.h"

#include <Velodyne/Namespace.h>


namespace vld::utils{

std::vector<std::vector<int>> file_packets;
size_t lenght(0);
int loop_beg(0);
int loop_end(0);
int loop_cpt(0);


//Constructor / Destructor
Importer::Importer(vld::structure::Main* vld_struct){
  //---------------------------

  this->vld_struct = vld_struct;
  this->vld_player = new vld::processing::Player(vld_struct);

  this->lidar_model = VLP_16;
  this->packet_range_on = false;
  this->packet_beg = 0;
  this->packet_end = 0;
  this->format = "pcap";

  //---------------------------
}
Importer::~Importer(){}

//PCAP reader callback
bool parse_packets(const Tins::PDU& packet){
  //---------------------------

  if(loop_cpt >= loop_beg && loop_cpt < loop_end){
    //Retrieve data packet
    const Tins::RawPDU raw = packet.rfind_pdu<Tins::RawPDU>();
    std::vector<uint8_t> buffer = raw.payload();

    //Convert into decimal vector
    std::vector<int> packet_dec;
    for(int i =0; i < buffer.size(); i++){
      std::bitset<8> octet(buffer[i]);

      int octet_32 = octet.to_ulong();
      packet_dec.push_back(octet_32);
    }

    //Store the packet
    file_packets.push_back(packet_dec);
  }

  loop_cpt++;

  //---------------------------
  return true;
}
bool count_packets(const Tins::PDU &){
    lenght++;
    return true;
}

//Main function
utl::File* Importer::import(utl::Path path){
  file_packets.clear();
  //---------------------------

  utl::file::Dataset* dataset = new utl::file::Dataset();
  dataset->name = utl::path::get_name_from_path(path.data);
  dataset->path.data = path.data;
  dataset->type = utl::file::DATASET;

  this->importer_init(path.data);
  this->importer_sniffing(path.data);
  this->importer_parsing(dataset, path.data);

  //---------------------------
  return dataset;
}
void Importer::insert(utl::type::Set* set){
  //---------------------------

  vld_struct->data.vec_set.push_back(set);
  vld_struct->data.current_set = set;
  vld_player->determine_range();
  vld_player->start_playback();

  //---------------------------
}

//Importer function
void Importer::importer_init(std::string path){
  //---------------------------

  //Set up parameters
  loop_cpt = 0;
  loop_beg = 0;
  loop_end = get_file_length(path);

  //Check if hdl32 is present in name
  if(path.find("HDL32") != std::string::npos){
    this->lidar_model = HDL_32;
  }

  //---------------------------
}
void Importer::importer_sniffing(std::string path){
  //---------------------------

  //Sniff UDP packets
  Tins::FileSniffer sniffer(path);
  sniffer.sniff_loop(parse_packets);

  //---------------------------
}
void Importer::importer_parsing(utl::file::Dataset* dataset, std::string path){
  //---------------------------

  //Parse data
  switch(lidar_model){
    case VLP_16:{
      this->parser_vlp16(dataset, path);
      break;
    }
    case HDL_32:{
      this->parser_hdl32(dataset, path);
      break;
    }
  }

  //---------------------------
}

//Subfunction
void Importer::parser_vlp16(utl::file::Dataset* dataset, std::string path){
  vld::processing::Frame vld_frame;
  vld::parser::VLP16 parser;
  //---------------------------

  int cpt = 0;
  for(int i=0; i<file_packets.size(); i++){
    utl::file::Data* data = parser.parse_packet(file_packets[i]);
    bool frame_rev = vld_frame.build_frame(data);

    if(frame_rev){
      utl::file::Data* frame = vld_frame.get_endedFrame();
      utl::file::Data* entity = new utl::file::Data();

      entity->name = "frame_" + std::to_string(cpt); cpt++;
      entity->path.data = path;
      entity->nb_element = frame->xyz.size();

      for(int j=0; j<frame->xyz.size(); j++){
        entity->xyz.push_back(frame->xyz[j]);
        entity->Is.push_back(frame->Is[j]);
        entity->ts.push_back(frame->ts[j]);
        entity->A.push_back(frame->A[j]);
        entity->R.push_back(frame->R[j]);
      }

      dataset->vec_data.push_back(entity);
    }
  }

  //---------------------------
}
void Importer::parser_hdl32(utl::file::Dataset* dataset, std::string path){
  vld::processing::Frame vld_frame;
  vld::parser::HDL32 parser;
  //---------------------------

  for(int i=0; i<file_packets.size(); i++){
    utl::file::Data* data = parser.parse_packet(file_packets[i]);
    bool frame_rev = vld_frame.build_frame(data);

    if(frame_rev){
      utl::file::Data* frame = vld_frame.get_endedFrame();
      utl::file::Data* entity = new utl::file::Data();

      entity->path.data = path;
      entity->nb_element = frame->xyz.size();

      for(int j=0; j<frame->xyz.size(); j++){
        entity->xyz.push_back(frame->xyz[j]);
        entity->Is.push_back(frame->Is[j] / 255);
        entity->ts.push_back(frame->ts[j]);
        entity->A.push_back(frame->A[j]);
        entity->R.push_back(frame->R[j]);
      }

      dataset->vec_data.push_back(entity);
    }
  }

  //---------------------------
}
int Importer::get_file_length(std::string path){
  lenght = 0;
  //---------------------------

  Tins::FileSniffer sniffer(path);
  sniffer.sniff_loop(count_packets);

  //---------------------------
  return lenght;
}

}
