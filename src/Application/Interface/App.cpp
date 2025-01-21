#include "App.h"

#include <iostream>
#include <stdexcept>
#include <fstream>


//Constructor / Destructor
App::App(){
  //---------------------------


  //---------------------------
}
App::~App(){}

//Main function
void App::run(){
  //---------------------------

  node_app.init();

  // Start the node_app loop in a separate thread
  this->thread = std::thread([this]() {
    node_app.loop();  // Run the app loop
  });

  //---------------------------
}
void App::close(){
  //---------------------------

  node_app.close();   // Clean up after the loop
  this->thread.join();

  //---------------------------
}
void App::add_cloud(){
  //---------------------------

  std::cout<<"coucou"<<std::endl;



  // Specify the file name
  std::string fileName = "output.txt";

  // Create an output file stream object
  std::ofstream outFile(fileName);

  // Check if the file stream is open
  if (outFile.is_open()) {
      // Write "Hello" to the file
      outFile << "Hello" << std::endl;

      // Close the file
      outFile.close();
      std::cout << "Successfully wrote to the file: " << fileName << std::endl;
  } else {
      // Handle error if the file cannot be opened
      std::cerr << "Error: Could not open the file for writing." << std::endl;
  }

  //---------------------------
}
