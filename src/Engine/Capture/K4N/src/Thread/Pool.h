#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

namespace k4n::thread{

class Pool
{
public:
  Pool(size_t numThreads);
  ~Pool();

public:
  //Main function
  void add_task(std::function<void()> task, bool* taskDone = nullptr);

private:
  //Subfunction
  void worker_thread();

private:
  std::vector<std::thread> vec_thread;
  std::queue<std::function<void()>> queue_task;
  std::mutex mutex;
  std::condition_variable condition;
  bool running;
};

}
