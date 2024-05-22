#include "Correction.h"

#include <Radiometry/Namespace.h>
#include <Data/Namespace.h>


namespace rad{

//Constructor / Destructor
Correction::Correction(rad::Node* node_radio){
  //---------------------------

  this->rad_struct = node_radio->get_rad_struct();
  this->rad_model = node_radio->get_rad_model();
  this->ope_normal = new ope::normal::KNN();

  //---------------------------
}
Correction::~Correction(){}

//Main function
void Correction::apply_correction(dat::base::Sensor* sensor, utl::media::Image* ir, utl::media::Image* depth){
  //---------------------------


  if(rad_model->is_ready() == false) return;

  rad_struct->correction.image.data = ir->data;
  rad_struct->correction.image.width = ir->width;
  rad_struct->correction.image.height = ir->height;
  rad_struct->correction.image.size = ir->size;
  rad_struct->correction.image.format = ir->format;

  vector<glm::vec3> vec_Nxyz;
  this->compute_normal(sensor, depth, vec_Nxyz);


  vec3 root = vec3(0, 0, 0);
  int cpt = 0;
  for(int y=0; y<ir->height; y++){
    for(int x=0; x<ir->width; x++){
      // Compute the index of the current pixel
      int idx = (y * ir->width + x) * 4; // Each pixel occupies 4 bytes

      // Convert the grayscale value to a floating-point value between 0 and 1
      float I_raw = ir->data[idx] / 255.0f * 1000;

      // Calculate It, R, and I_cor
      vec3 Nxyz = vec_Nxyz[cpt++];
      vec3 xyz = sensor->convert_depth_2d_to_3d(ivec2(x, y));
      float It = math::compute_It(xyz, Nxyz, root);
      float R = math::distance_from_origin(xyz);

      float I_cor;
      if (isnan(It)) {
          I_cor = 0;
      } else {
          float fit = rad_model->apply_model(R, It);
          I_cor = (I_raw / fit) / 2;

          if(I_cor > 1) I_cor = 1;
      }


      I_cor = I_cor * 255;




      // Set all color channels to I_cor (grayscale) and leave alpha channel unchanged
      rad_struct->correction.image.data[idx] = static_cast<uint8_t>(I_cor); // Red channel
      rad_struct->correction.image.data[idx + 1] = static_cast<uint8_t>(I_cor); // Green channel
      rad_struct->correction.image.data[idx + 2] = static_cast<uint8_t>(I_cor); // Blue channel

    }
  }

/*
  //Try to turn all the ir in white to be sure all conversion is ok
  vec3 root = vec3(0, 0, 0);
  int cpt = 0;
  for(int y=0; y<ir->height; y++){
    for(int x=0; x<ir->width; x++){
      // Compute the index of the current pixel
      int idx = (y * ir->width + x) * 2;


      // Set all color channels to 255 (white) and leave alpha channel unchanged
      rad_struct->correction.image.data[idx] = 255; // Red channel
      rad_struct->correction.image.data[idx + 1] = 255; // Green channel
      rad_struct->correction.image.data[idx + 2] = 255; // Blue channel
      // Assuming alpha channel is the next byte after the RGB channels
      rad_struct->correction.image.data[idx + 3] = ir->data[idx + 3]; // Alpha channel

    }
  }
*/
  rad_struct->correction.image.new_data = true;


  //---------------------------
}

//Subfunction
void Correction::compute_normal(dat::base::Sensor* sensor, utl::media::Image* depth, vector<glm::vec3>& vec_Nxyz) {
    //---------------------------
    vec_Nxyz.resize(depth->width * depth->height);

    for(int y = 0; y < depth->height; ++y){
        for(int x = 0; x < depth->width; ++x){
            // Compute the index of the current pixel
            int idx = y * depth->width + x;

            // Compute neighboring pixel indices
            ivec2 idx_center = ivec2(x, y);
            ivec2 idx_left = ivec2(std::max(x - 1, 0), y);
            ivec2 idx_right = ivec2(std::min(x + 1, depth->width - 1), y);
            ivec2 idx_up = ivec2(x, std::max(y - 1, 0));
            ivec2 idx_down = ivec2(x, std::min(y + 1, depth->height - 1));

            // Retrieve depth values of neighboring pixels
            glm::vec3 depth_center = sensor->convert_depth_2d_to_3d(idx_center);
            glm::vec3 depth_left = (x > 0) ? sensor->convert_depth_2d_to_3d(idx_left) : depth_center;
            glm::vec3 depth_right = (x < depth->width - 1) ? sensor->convert_depth_2d_to_3d(idx_right) : depth_center;
            glm::vec3 depth_up = (y > 0) ? sensor->convert_depth_2d_to_3d(idx_up) : depth_center;
            glm::vec3 depth_down = (y < depth->height - 1) ? sensor->convert_depth_2d_to_3d(idx_down) : depth_center;

            // Compute central differences for x and y gradients
            glm::vec3 gradient_x = (depth_right - depth_left) / 2.0f;
            glm::vec3 gradient_y = (depth_down - depth_up) / 2.0f;

            // Compute the normal using the gradients
            glm::vec3 normal = glm::cross(gradient_x, gradient_y);
            float length = glm::length(normal);
            if (length > 0) {
                normal /= length;
            }

            // Compute the vector from the surface to the camera
            glm::vec3 to_camera = glm::normalize(vec3(0, 0, 0) - depth_center);
            if (glm::dot(normal, to_camera) < 0) {
                // Flip the normal to point towards the camera
                normal *= -1;
            }

            // Store the normal
            vec_Nxyz[idx] = normal;
        }
    }
    //---------------------------
}
void Correction::compute_normal_pca(dat::base::Sensor* sensor, utl::media::Image* depth, std::vector<glm::vec3>& vec_Nxyz) {
    //---------------------------
    vec_Nxyz.resize(depth->width * depth->height);

    // Helper function to perform PCA
    auto compute_pca_normal = [](const std::vector<glm::vec3>& points) -> glm::vec3 {
        if (points.size() < 3) return glm::vec3(0, 0, 1);

        // Compute mean
        glm::vec3 mean(0.0f);
        for (const auto& p : points) mean += p;
        mean /= static_cast<float>(points.size());

        // Compute covariance matrix
        Eigen::Matrix3f covariance = Eigen::Matrix3f::Zero();
        for (const auto& p : points) {
            glm::vec3 centered = p - mean;
            covariance(0, 0) += centered.x * centered.x;
            covariance(0, 1) += centered.x * centered.y;
            covariance(0, 2) += centered.x * centered.z;
            covariance(1, 1) += centered.y * centered.y;
            covariance(1, 2) += centered.y * centered.z;
            covariance(2, 2) += centered.z * centered.z;
        }
        covariance(1, 0) = covariance(0, 1);
        covariance(2, 0) = covariance(0, 2);
        covariance(2, 1) = covariance(1, 2);

        // Eigen decomposition
        Eigen::SelfAdjointEigenSolver<Eigen::Matrix3f> solver(covariance);
        Eigen::Vector3f normal = solver.eigenvectors().col(0);

        return glm::vec3(normal[0], normal[1], normal[2]);
    };

    for (int y = 0; y < depth->height; ++y) {
        for (int x = 0; x < depth->width; ++x) {
            // Compute the index of the current pixel
            int idx = y * depth->width + x;

            // Collect neighboring points within a certain radius
            std::vector<glm::vec3> neighbors;
            int radius = 1;
            while (neighbors.size() < 10000) {
                for (int ky = std::max(0, y - radius); ky <= std::min(depth->height - 1, y + radius); ++ky) {
                    for (int kx = std::max(0, x - radius); kx <= std::min(depth->width - 1, x + radius); ++kx) {
                        if (kx == x && ky == y) continue;
                        glm::vec3 neighbor = sensor->convert_depth_2d_to_3d(glm::ivec2(kx, ky));
                        neighbors.push_back(neighbor);
                    }
                }
                radius++;
            }

            // Compute the normal using PCA
            glm::vec3 normal = compute_pca_normal(neighbors);
            normal = glm::normalize(normal);

            // Compute the vector from the surface to the camera
            glm::vec3 depth_center = sensor->convert_depth_2d_to_3d(glm::ivec2(x, y));
            glm::vec3 to_camera = glm::normalize(glm::vec3(0, 0, 0) - depth_center);
            if (glm::dot(normal, to_camera) < 0) {
                // Flip the normal to point towards the camera
                normal *= -1;
            }

            // Store the normal
            vec_Nxyz[idx] = normal;
        }
    }
    //---------------------------
}

}
