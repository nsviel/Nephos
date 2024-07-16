#pragma once

#include <glm/glm.hpp>
#include <vector>


namespace attribut{

void compute_heatmap(std::vector<float>& v_in, std::vector<glm::vec4>& rgba);

}
