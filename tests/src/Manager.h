#pragma once

#include <Utility/Specific/Common.h>

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
  vector<test::Base*> vec_test;
};

}
