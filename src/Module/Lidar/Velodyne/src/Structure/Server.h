#pragma once


namespace vld::structure{

struct Server{
  //---------------------------

  std::string ip_lidar = "192.168.1.201";
  bool is_listening = false;
  int port = 55555;
  int mtu = 1248;

  //---------------------------
};

}
