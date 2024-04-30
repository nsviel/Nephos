#include "Sphere.h"

#include <Utility/Namespace.h>
#include <opencv2/opencv.hpp>


namespace ope::fitting{

//Constructor / Destructor
Sphere::Sphere(){
  //---------------------------

  //---------------------------
}
Sphere::~Sphere(){}

//Sphere fitting
void Sphere::find_sphere_in_cloud(std::vector<glm::vec3>& xyz, glm::vec3& center, float& radius){
  glm::vec3 COM = math::centroid(xyz);
  //------------------------

  // Compute the covariance matrix M of the Y[i] = X[i]-A and the
  // right-hand side R of the linear system M*(C-A) = R.
  float M00 = 0, M01 = 0, M02 = 0, M11 = 0, M12 = 0, M22 = 0;
  glm::vec3 R = {0, 0, 0};
  for(int i=0; i<xyz.size(); i++){
    glm::vec3 Y = xyz[i] - COM;
    float Y0Y0 = Y[0] * Y[0];
    float Y0Y1 = Y[0] * Y[1];
    float Y0Y2 = Y[0] * Y[2];
    float Y1Y1 = Y[1] * Y[1];
    float Y1Y2 = Y[1] * Y[2];
    float Y2Y2 = Y[2] * Y[2];
    M00 += Y0Y0;
    M01 += Y0Y1;
    M02 += Y0Y2;
    M11 += Y1Y1;
    M12 += Y1Y2;
    M22 += Y2Y2;
    R += (Y0Y0 + Y1Y1 + Y2Y2) * Y;
  }
  R *= 0.5f;

  // Solve the linear system M*(C-A) = R for the center C.
  float cof00 = M11 * M22 - M12 * M12;
  float cof01 = M02 * M12 - M01 * M22;
  float cof02 = M01 * M12 - M02 * M11;
  float det = M00 * cof00 + M01 * cof01 + M02 * cof02;
  if(det != 0.0f){
    float cof11 = M00 * M22 - M02 * M02;
    float cof12 = M01 * M02 - M00 * M12;
    float cof22 = M00 * M11 - M01 * M01;

    glm::vec3 temp_center;
    temp_center[0] = COM[0] + (cof00 * R[0] + cof01 * R[1] + cof02 * R[2]) / det;
    temp_center[1] = COM[1] + (cof01 * R[0] + cof11 * R[1] + cof12 * R[2]) / det;
    temp_center[2] = COM[2] + (cof02 * R[0] + cof12 * R[1] + cof22 * R[2]) / det;

    float rsqr = 0.0f;
    for(int i=0; i<xyz.size(); i++){
      glm::vec3 delta = xyz[i] - temp_center;
      rsqr += math::dot_product(delta, delta);
    }
    float a = math::distance_from_origin(xyz[0]);
    rsqr *= (1.0f / xyz.size());
    radius = std::sqrt(rsqr);
    center = temp_center;
  }
  else{
    center = {0, 0, 0};
    radius = 0;
  }

  //------------------------
}
void Sphere::find_circle_in_image(utl::media::Image* image){
  //------------------------

  // Create an OpenCV Mat object from the image data
  cv::Mat cv_image(image->height, image->width, CV_8UC4, image->data.data());

  // Convert the image to grayscale
  cv::Mat gray_image;
  cv::cvtColor(cv_image, gray_image, cv::COLOR_RGBA2GRAY);

  // Perform Hough Transform to detect lines
  std::vector<cv::Vec3f> vec_circle;
  int ratio = 1;
  float min_dist = gray_image.rows / 8;
  float min_radius = 5;
  float max_radius = 50;

  //modes:
  // - cv::HOUGH_GRADIENT
  // - cv::HOUGH_STANDARD
  // - cv::HOUGH_PROBABILISTIC
  int mode = cv::HOUGH_GRADIENT;

  float param_1, param_2;
  switch(mode){
    case cv::HOUGH_GRADIENT:{
      param_1 = 100; //higher threshold for the Canny edge detector
      param_2 = 40; //accumulator threshold for the circle centers at the detection stage
      break;
    }
    case cv::HOUGH_STANDARD:{
      param_1 = 0; //not used
      param_2 = 30; //minimum number of intersections to "detect" a circle
      break;
    }
    case cv::HOUGH_PROBABILISTIC:{
      param_1 = 10; //minimum distance between the centers of the detected vec_circle
      param_2 = 30; //minimum radius of the vec_circle to detect
      break;
    }
  }

  cv::HoughCircles(gray_image, vec_circle, mode, ratio, min_dist, param_1, param_2, min_radius, max_radius);

  // Draw the detected vec_circle on the original image
  cv::Mat result;
  cv::cvtColor(gray_image, result, cv::COLOR_RGBA2BGRA); // Convert edges to BGR for drawing
  for(size_t i=0; i<vec_circle.size(); i++){
    cv::Point center(cvRound(vec_circle[i][0]), cvRound(vec_circle[i][1]));
    int radius = cvRound(vec_circle[i][2]);

    // Draw the circle center
    cv::circle(result, center, 3, cv::Scalar(44, 250, 44), -1, cv::LINE_AA);

    // Draw the circle outline
    cv::circle(result, center, radius, cv::Scalar(44, 44, 250), 1, cv::LINE_AA);
  }

  // Display the result
  say(vec_circle.size());
  cv::imshow("Raw Image", cv_image);
  cv::waitKey(0);
  cv::imshow("Hough Circles", result);
  cv::waitKey(0);

  //------------------------
}
void Sphere::find_circle_in_image_with_canny(utl::media::Image* image){
  //------------------------

  // Create an OpenCV Mat object from the image data
  cv::Mat cv_image(image->height, image->width, CV_8UC4, image->data.data());

  // Perform edge detection (you may need to adjust parameters for your specific image)
  cv::Mat edges;
  cv::Canny(cv_image, edges, 50, 150);

  // Perform Hough Transform to detect lines
  std::vector<cv::Vec3f> vec_circle;
  int ratio = 1;
  float min_dist = edges.rows / 8;
  float min_radius = 5;
  float max_radius = 50;

  //modes:
  // - cv::HOUGH_GRADIENT
  // - cv::HOUGH_STANDARD
  // - cv::HOUGH_PROBABILISTIC
  int mode = cv::HOUGH_GRADIENT;

  float param_1, param_2;
  switch(mode){
    case cv::HOUGH_GRADIENT:{
      param_1 = 100; //higher threshold for the Canny edge detector
      param_2 = 40; //accumulator threshold for the circle centers at the detection stage
      break;
    }
    case cv::HOUGH_STANDARD:{
      param_1 = 0; //not used
      param_2 = 30; //minimum number of intersections to "detect" a circle
      break;
    }
    case cv::HOUGH_PROBABILISTIC:{
      param_1 = 10; //minimum distance between the centers of the detected vec_circle
      param_2 = 30; //minimum radius of the vec_circle to detect
      break;
    }
  }

  cv::HoughCircles(edges, vec_circle, mode, ratio, min_dist, param_1, param_2, min_radius, max_radius);

  // Draw the detected vec_circle on the original image
  cv::Mat result;
  cv::cvtColor(edges, result, cv::COLOR_RGBA2BGRA); // Convert edges to BGR for drawing
  for(size_t i=0; i<vec_circle.size(); i++){
    cv::Point center(cvRound(vec_circle[i][0]), cvRound(vec_circle[i][1]));
    int radius = cvRound(vec_circle[i][2]);

    // Draw the circle center
    cv::circle(result, center, 3, cv::Scalar(0, 255, 0), -1, cv::LINE_AA);

    // Draw the circle outline
    cv::circle(result, center, radius, cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
  }

  // Display the result
  say(vec_circle.size());
  cv::imshow("Raw Image", cv_image);
  cv::waitKey(0);
  cv::imshow("Hough Circles", result);
  cv::waitKey(0);

  //------------------------
}

}
