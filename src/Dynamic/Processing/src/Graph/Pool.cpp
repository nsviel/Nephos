#include "Pool.h"

#include <Processing/Namespace.h>
#include <vector>
#include <queue>


namespace dyn::prc{

// Constructor / Destructor
Pool::Pool(size_t num_threads){
  //---------------------------

  for (size_t i = 0; i < num_threads; ++i) {
    workers.emplace_back([this] {
      while (true) {
        std::function<void()> task;
        {
          std::unique_lock<std::mutex> lock(queue_mutex);
          condition.wait(lock, [this] { return stop || !tasks.empty(); });
          if (stop && tasks.empty())
            return;
          task = std::move(tasks.front());
          tasks.pop();
        }
        task();
      }
    });
  }

  //---------------------------
}
Pool::~Pool(){
  //---------------------------

  {
    std::unique_lock<std::mutex> lock(queue_mutex);
    stop = true;
  }
  condition.notify_all();
  for (std::thread &worker : workers)
    worker.join();

  //---------------------------
}

//Main function
template<class F>
void Pool::submit(F&& f) {
  //---------------------------

  {
    std::unique_lock<std::mutex> lock(queue_mutex);
    if (stop)
      throw std::runtime_error("submit on stopped ThreadPool");
    tasks.emplace(std::forward<F>(f));
  }
  condition.notify_one();

  //---------------------------
}

}
