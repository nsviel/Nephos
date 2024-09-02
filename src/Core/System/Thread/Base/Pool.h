#pragma once

#include <atomic>
#include <mutex>


namespace thr{

struct Pool{
  //---------------------------

  std::mutex active_thread_mutex;
  static std::atomic<int> active_thread_count;

  //---------------------------
};

}
