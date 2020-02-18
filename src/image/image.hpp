#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "../config/config.hpp"

class Image {

	public:

		Image(std::shared_ptr<Config> config);
		~Image();
		
		cv::Mat GetImage() {return img;};
		cv::Mat GetFilteredImage() {return filteredImg;};
		cv::Mat GetBackgroundImage() {return backgroundImg;};
		std::vector<cv::Point2d> GetSpots() {return spots;};

	private:
		void findSpots();

		const int BLURFILTERSIZE = 5;
		
		const std::shared_ptr<Config> config_;                    

		cv::Mat img;
		cv::Mat filteredImg;
		cv::Mat backgroundImg;

		std::vector<cv::Point2d> spots;
};