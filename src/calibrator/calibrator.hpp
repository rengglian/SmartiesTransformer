#pragma once

#include <opencv2/calib3d.hpp>

#include "../config/config.hpp"

class Calibrator {

	public:

		Calibrator(std::shared_ptr<Config> config);
		~Calibrator();
		cv::Mat affine(const std::vector<cv::Point2d>& spots);
		std::vector<cv::Point2d> GetTargetSpots() {return targetSpots;};

	private:
		std::vector<cv::Point2d> createTargetSpots();
		const std::shared_ptr<Config> config_;
		double px_to_mm{50};
		std::vector<cv::Point2d> targetSpots;
};