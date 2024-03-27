#pragma once


namespace k4n::structure{

struct Model{
  //---------------------------

  std::vector<glm::vec3> vec_data;

  utl::type::Plot IfR;
  utl::type::Plot IfIt;
  utl::type::Plot IfRIt;

  //---------------------------
};

}
