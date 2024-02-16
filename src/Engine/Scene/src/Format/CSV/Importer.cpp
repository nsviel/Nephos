#include "Importer.h"
#include "Parser/CSV_state.h"

#include <fstream>


namespace format::csv{

//Constructor / Destructor
Importer::Importer(){
  //---------------------------

  this->format = "csv";

  //---------------------------
}
Importer::~Importer(){}

//Main function
utl::media::File* Importer::import(std::string pathFile){
  //---------------------------

  std::ifstream file(pathFile);
  std::vector<std::vector<std::string>> csvFile = readCSV(file);

  //At row level
  for(int i=0; i<csvFile.size(); i++){
    utl::media::File* data_sub = new utl::media::File();
    data_sub->path_data = pathFile;

    //At field level
    int cpt_field = -1;
    int cpt_point = 0;
    std::string ts_str, x_str, y_str, z_str;
    for(int j=0; j<csvFile[i].size(); j++){
      std::string field = csvFile[i][j];

      if(j == 0 && cpt_field == -1){
        ts_str = field;
        cpt_field++;
      }
      else if(cpt_field == 0){
        x_str = field;
        cpt_field++;
      }
      else if(cpt_field == 1){
        y_str = field;
        cpt_field++;
      }
      else if(cpt_field == 2){
        z_str = field;

        float ts = stof(ts_str);
        float x = stof(x_str);
        float y = stof(y_str);
        float z = stof(z_str);

        //Relative timestamp
        float delay = 1000000.0f / (25.0f * 340.0f);
        ts = ts + cpt_point * delay;

        glm::vec3 point = glm::vec3(x, y, z);

        data_sub->name = "frame_" + std::to_string(i);
        data_sub->ts.push_back(ts);
        data_sub->xyz.push_back(point);

        cpt_field = 0;
        cpt_point++;
      }
    }

    //End of row line
    data->vec_data.push_back(data_sub);
  }

  //---------------------------
  return data;
}

}
