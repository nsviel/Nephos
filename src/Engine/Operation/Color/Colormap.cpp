#include "Colormap.h"


namespace ope::color{

//Constructor / destructor
Colormap::Colormap(){
  //---------------------------


  //---------------------------
  this->init();
}
Colormap::~Colormap(){}

void Colormap::init(){
  //---------------------------

  //Colormap - Viridis
  vector<vec3> viridis_short = {vec3(0.267004, 0.004874, 0.329415), vec3(0.252194, 0.269783, 0.531579),
                          vec3(0.180629, 0.429975, 0.557282), vec3(0.133743, 0.548535, 0.553541),
                          vec3(0.137339, 0.662252, 0.515571), vec3(0.304148, 0.764704, 0.419943),
                          vec3(0.575563, 0.844566, 0.256415), vec3(0.993248, 0.906157, 0.143936)};
  this->colormap_name.push_back("viridis_short");
  this->colormap_list.push_back(viridis_short);

  //Colormap - Viridis
  vector<vec3> viridis_long = {
    vec3(0.267004, 0.004874, 0.329415), vec3(0.275191, 0.194905, 0.496005),
    vec3(0.282482, 0.348894, 0.511832), vec3(0.289719, 0.480025, 0.513077),
    vec3(0.296899, 0.592109, 0.494742), vec3(0.304011, 0.687258, 0.454855),
    vec3(0.311053, 0.768116, 0.400769), vec3(0.318025, 0.836173, 0.328326),
    vec3(0.324925, 0.893509, 0.237081), vec3(0.331753, 0.942333, 0.122426),
    vec3(0.338503, 0.982512, 0.045477), vec3(0.345159, 0.998963, 0.042916),
    vec3(0.351688, 0.970423, 0.061360), vec3(0.358075, 0.912594, 0.088184),
    vec3(0.364300, 0.836673, 0.123862), vec3(0.370346, 0.749331, 0.170965),
    vec3(0.376195, 0.655230, 0.227362), vec3(0.381835, 0.557047, 0.290428),
    vec3(0.387249, 0.457048, 0.358640), vec3(0.392423, 0.356766, 0.430856),
    vec3(0.397341, 0.257246, 0.505136), vec3(0.401981, 0.160073, 0.579410),
    vec3(0.406308, 0.065559, 0.651754), vec3(0.410282, 0.014800, 0.719317),
    vec3(0.413876, 0.125344, 0.780397), vec3(0.417058, 0.239530, 0.828164),
    vec3(0.419784, 0.349815, 0.863830), vec3(0.422018, 0.454414, 0.889262),
    vec3(0.423725, 0.553333, 0.906139), vec3(0.424873, 0.645816, 0.916888),
    vec3(0.425427, 0.731885, 0.923370), vec3(0.425350, 0.811598, 0.926065),
    vec3(0.424607, 0.885078, 0.924977), vec3(0.423162, 0.952524, 0.919431),
    vec3(0.420980, 0.997328, 0.911659), vec3(0.417992, 0.999808, 0.903101),
    vec3(0.414080, 0.987279, 0.892275), vec3(0.409089, 0.960326, 0.877838),
    vec3(0.402844, 0.919612, 0.858973), vec3(0.395234, 0.866497, 0.834087),
    vec3(0.386123, 0.802318, 0.800196), vec3(0.375415, 0.728850, 0.756675),
    vec3(0.362989, 0.647422, 0.705082), vec3(0.348703, 0.559937, 0.647220),
    vec3(0.332387, 0.468227, 0.584861), vec3(0.313966, 0.375921, 0.519350),
    vec3(0.293543, 0.286791, 0.453320), vec3(0.271135, 0.205304, 0.390423),
    vec3(0.246835, 0.142115, 0.333023), vec3(0.220789, 0.097549, 0.284509),
    vec3(0.193170, 0.068909, 0.248124), vec3(0.164207, 0.053183, 0.228886),
    vec3(0.134263, 0.047293, 0.216936), vec3(0.103761, 0.047758, 0.209780),
    vec3(0.073235, 0.051540, 0.205945), vec3(0.043163, 0.056700, 0.203574),
    vec3(0.013935, 0.060034, 0.200528)
  };
  this->colormap_name.push_back("viridis_long");
  this->colormap_list.push_back(viridis_long);

  //Colormap - Magma
  vector<vec3> magma = {vec3(0.001462, 0.000466, 0.013866), vec3(0.043830, 0.033830, 0.141886),
                        vec3(0.232077, 0.059889, 0.437695), vec3(0.439062, 0.120298, 0.506555),
                        vec3(0.620005, 0.183840, 0.497524), vec3(0.804752, 0.249911, 0.442102),
                        vec3(0.953099, 0.397563, 0.361438), vec3(0.993326, 0.602275, 0.414390),
                        vec3(0.995131, 0.827052, 0.585701), vec3(0.987053, 0.991438, 0.749504)};
  this->colormap_name.push_back("magma");
  this->colormap_list.push_back(magma);

  //Colormap - Rainbow
  vector<vec3> rainbow = {vec3(0,0,1), vec3(0,1,0), vec3(1,1,0), vec3(1,0,0)};
  this->colormap_name.push_back("rainbow");
  this->colormap_list.push_back(rainbow);

  //Selected colormap
  this->colormap_selected = viridis_long;

  //---------------------------
}
void Colormap::choose(string name){
  //---------------------------

  for(int i=0; i<colormap_name.size(); i++){
    if(name == colormap_name[i]){
      colormap_selected = colormap_list[i];
    }
  }

  //---------------------------
}
glm::vec4 Colormap::random(){
  //---------------------------

  float Red = float(rand()%101)/100;
  float Green = float(rand()%101)/100;
  float Blue = float(rand()%101)/100;
  glm::vec4 color = glm::vec4(Red, Green, Blue, 1.0f);

  //---------------------------
  return color;
}

}