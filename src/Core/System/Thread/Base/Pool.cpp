#include "Pool.h"


namespace thr{

std::atomic<int> Pool::active_thread_count{0};

}
