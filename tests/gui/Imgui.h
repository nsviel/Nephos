#pragma once




namespace test{

class Imgui
{
public:
  Imgui();
  ~Imgui();

public:
  //Main function
  void run();

  //Subfunction
  void init();
  void loop();
  void clean();

private:

};

}
