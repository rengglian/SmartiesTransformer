#include "image.hpp"

Image::Image(std::shared_ptr<Config> config) : config_(config) {
	
    backgroundImg = cv::imread(config_->GetPathBackground(), cv::IMREAD_COLOR );
	img = cv::imread(config_->GetPathImage(), cv::IMREAD_COLOR );
    // Check if image is loaded fine
    if(backgroundImg.empty() || img.empty()){
        throw " Error opening image";
    }
	//substract background image from source image and blur it sligthly
    filteredImg = img-backgroundImg;
    cv::cvtColor(filteredImg, filteredImg, cv::COLOR_BGR2GRAY);
    cv::medianBlur(filteredImg, filteredImg, Image::BLURFILTERSIZE);
    findSpots();    
}

Image::~Image() {}

void Image::findSpots() {
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(filteredImg, circles, cv::HOUGH_GRADIENT, 1,
                 filteredImg.rows/32,  // change this value to detect circles with different distances to each other
                 70, 10, 3, 10 // change the last two parameters
            // (min_radius & max_radius) to detect larger circles
    );  

    for (const auto& circle : circles)
    {
        cv::Point2d center = cv::Point2d(circle[0], circle[1]);
		spots.push_back(center);									
   }    
}