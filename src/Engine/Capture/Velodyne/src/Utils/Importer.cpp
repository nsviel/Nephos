#include "Importer.h"

#include <Velodyne/Namespace.h>


namespace velodyne{

using namespace Tins;
std::vector<std::vector<int>> file_packets;
size_t lenght(0);
int loop_beg(0);
int loop_end(0);
int loop_cpt(0);


//Constructor / Destructor
Importer::Importer(){
  //---------------------------

  this->LiDAR_model = "vlp16";
  this->packet_range_on = false;
  this->packet_beg = 0;
  this->packet_end = 0;
  this->format = "pcap";

  //---------------------------
}
Importer::~Importer(){}

//PCAP reader callback
bool parse_packets(const PDU& packet){
  //---------------------------

  if(loop_cpt >= loop_beg && loop_cpt < loop_end){
    //Retrieve data packet
    const RawPDU raw = packet.rfind_pdu<RawPDU>();
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
bool count_packets(const PDU &){
    lenght++;
    return true;
}

//Main function
utl::media::File* Importer::import_data(std::string path){
  file_packets.clear();
  //---------------------------

  data = new utl::media::File();
  data->name = utl::fct::info::get_name_from_path(path);
  data->path_data = path;

  //Set up parameters
  loop_cpt = 0;
  if(packet_range_on){
    loop_beg = packet_beg;
    loop_end = packet_end;
  }else{
    loop_beg = 0;
    loop_end = get_file_length(path);
  }

  //Check if vlp16 or hdl32
  if (path.find("HDL32") != std::string::npos){
    this->LiDAR_model = "hdl32";
  }else{
    this->LiDAR_model = "vlp16";
  }

  //Sniff UDP packets
  FileSniffer sniffer(path);
  sniffer.sniff_loop(parse_packets);

  //Parse data
  if(LiDAR_model == "vlp16"){
    this->Loader_vlp16(data, path);
  }
  else if(LiDAR_model == "hdl32"){
    this->Loader_hdl32(data, path);
  }

  //---------------------------
  return data;
}

//Subfunction
void Importer::Loader_vlp16(utl::media::File* data, std::string path){
  velodyne::Frame velo_frame;
  velodyne::parser::VLP16 parser;
  //---------------------------

  int cpt = 0;
  for(int i=0; i<file_packets.size(); i++){

    utl::media::File* cloud = parser.parse_packet(file_packets[i]);
    bool frame_rev = velo_frame.build_frame(cloud);

    if(frame_rev){
      utl::media::File* frame = velo_frame.get_endedFrame();
      utl::media::File* frame_data = new utl::media::File();

      frame_data->name = "frame_" + std::to_string(cpt); cpt++;
      frame_data->path_data = path;
      frame_data->nb_element = frame->xyz.size();

      for(int j=0; j<frame->xyz.size(); j++){
        frame_data->xyz.push_back(frame->xyz[j]);
        frame_data->Is.push_back(frame->Is[j]);
        frame_data->ts.push_back(frame->ts[j]);
        frame_data->A.push_back(frame->A[j]);
        frame_data->R.push_back(frame->R[j]);
      }

      data->vec_data.push_back(frame_data);
    }
  }

  //---------------------------
}
void Importer::Loader_hdl32(utl::media::File* data, std::string path){
  velodyne::Frame velo_frame;
  velodyne::parser::HDL32 parser;
  //---------------------------

  for(int i=0; i<file_packets.size(); i++){
    utl::media::File* cloud = parser.parse_packet(file_packets[i]);
    bool frame_rev = velo_frame.build_frame(cloud);

    if(frame_rev){
      utl::media::File* frame = velo_frame.get_endedFrame();
      utl::media::File* frame_data = new utl::media::File();

      frame_data->path_data = path;
      frame_data->nb_element = frame->xyz.size();

      for(int j=0; j<frame->xyz.size(); j++){
        frame_data->xyz.push_back(frame->xyz[j]);
        frame_data->Is.push_back(frame->Is[j] / 255);
        frame_data->ts.push_back(frame->ts[j]);
        frame_data->A.push_back(frame->A[j]);
        frame_data->R.push_back(frame->R[j]);
      }

      data->vec_data.push_back(frame_data);
    }
  }

  //---------------------------
}
int Importer::get_file_length(std::string path){
  lenght = 0;
  //---------------------------

  FileSniffer sniffer(path);
  sniffer.sniff_loop(count_packets);

  //---------------------------
  return lenght;
}

}
