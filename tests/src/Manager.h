#pragma once

#include <vector>

namespace test{class Base;}


namespace test{

class Manager
{
public:
  Manager();
  ~Manager();

public:
  //Main function


private:
  std::vector<test::Base*> vec_test;
};

}
