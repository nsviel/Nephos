#ifndef K4APOLLINGTHREAD_H
#define K4APOLLINGTHREAD_H

#include <k4a/k4a.hpp>
#include <functional>
#include <thread>

class Struct_kinect;


class K4A_thread
{
public:
  //Constructor / Destructor
  K4A_thread(Struct_kinect* struct_kinect);
  ~K4A_thread();

  //Main function
  void run();

  //Subfunction
  void run_thread(k4a::device* device, k4a::capture* capture);
  void stop_thread();

  inline bool is_thread_running(){return thread_running;}

private:
  Struct_kinect* struct_kinect;

  std::function<bool(bool)> m_pollFn;
  std::thread thread;
  bool thread_running = false;
};


#endif
