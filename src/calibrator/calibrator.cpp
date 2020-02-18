#include "calibrator.hpp"


Calibrator::Calibrator(std::shared_ptr<Config> config) : config_(config) {
	px_to_mm = config_->GetPixelMM();
	targetSpots = createTargetSpots2();
}

Calibrator::~Calibrator() {}

cv::Mat Calibrator::affine(const std::vector<cv::Point2d>& spots) {
	std::vector<cv::Point2d> tmp = spots;
	const cv::Point2d avg_spot = std::accumulate(spots.begin(), spots.end(), cv::Point2d(0.0,0.0), std::plus<cv::Point2d>()) / static_cast<double>(spots.size());

	std::sort(tmp.begin(), tmp.end(), 
		[avg_spot](const cv::Point2f &a, const cv::Point2f &b)
		{
			return std::pow(avg_spot.x - a.x,2) + std::pow(avg_spot.y - a.y,2) < std::pow(avg_spot.x - b.x,2) + std::pow(avg_spot.y - b.y,2)  ; //or whatever you like
	});

	std::vector<cv::Point2d> scaled;
	for (const auto& spot : spots)
    {  
		scaled.push_back((spot-tmp[0])/px_to_mm);
    }
	std::vector<uchar> inliers(targetSpots.size(), 0);

	for(int i = 0; i< targetSpots.size(); i++)
	{
		std::cout << targetSpots[i] << "\t" << scaled[i] << std::endl;
	}	
	//return cv::findHomography(scaled, targetSpots);
	return cv::estimateAffine2D(scaled, targetSpots, inliers, cv::RANSAC);
}

std::vector<cv::Point2d> Calibrator::createTargetSpots(){

	std::vector<cv::Point2d> tmp;
	tmp.push_back(cv::Point2d(-6.0, 0.0));
	tmp.push_back(cv::Point2d(-5.0, 0.0));
	tmp.push_back(cv::Point2d(-4.0, 0.0));
	tmp.push_back(cv::Point2d(-3.0, 0.0));
	tmp.push_back(cv::Point2d(-2.0, 0.0));
	tmp.push_back(cv::Point2d(-1.0, 0.0));
	tmp.push_back(cv::Point2d(0.0, 0.0));
	tmp.push_back(cv::Point2d(1.0, 0.0));
	tmp.push_back(cv::Point2d(2.0, 0.0));
	tmp.push_back(cv::Point2d(3.0, 0.0));
	tmp.push_back(cv::Point2d(4.0, 0.0));
	tmp.push_back(cv::Point2d(5.0, 0.0));
	tmp.push_back(cv::Point2d(6.0, 0.0));
	tmp.push_back(cv::Point2d(0.0, 6.0));
	tmp.push_back(cv::Point2d(0.0, 5.0));
	tmp.push_back(cv::Point2d(0.0, 4.0));
	tmp.push_back(cv::Point2d(0.0, 3.0));
	tmp.push_back(cv::Point2d(0.0, 2.0));
	tmp.push_back(cv::Point2d(0.0, 1.0));
	tmp.push_back(cv::Point2d(0.0, 0.0));
	tmp.push_back(cv::Point2d(0.0, -1.0));
	tmp.push_back(cv::Point2d(0.0, -2.0));
	tmp.push_back(cv::Point2d(0.0, -3.0));
	tmp.push_back(cv::Point2d(0.0, -4.0));
	tmp.push_back(cv::Point2d(0.0, -5.0));
	tmp.push_back(cv::Point2d(0.0, -6.0));
	return tmp;
}

std::vector<cv::Point2d> Calibrator::createTargetSpots2(){

	std::vector<cv::Point2d> tmp;
	tmp.push_back(cv::Point2d(6.0, 0.0));
	tmp.push_back(cv::Point2d(5.0, 0.0));
	tmp.push_back(cv::Point2d(4.0, 0.0));
	tmp.push_back(cv::Point2d(3.0, 0.0));
	tmp.push_back(cv::Point2d(2.0, 0.0));
	tmp.push_back(cv::Point2d(1.0, 0.0));
	tmp.push_back(cv::Point2d(0.0, 0.0));
	tmp.push_back(cv::Point2d(-1.0, 0.0));
	tmp.push_back(cv::Point2d(-2.0, 0.0));
	tmp.push_back(cv::Point2d(-3.0, 0.0));
	tmp.push_back(cv::Point2d(-4.0, 0.0));
	tmp.push_back(cv::Point2d(-5.0, 0.0));
	tmp.push_back(cv::Point2d(-6.0, 0.0));
	tmp.push_back(cv::Point2d(0.0, 6.0));
	tmp.push_back(cv::Point2d(0.0, 5.0));
	tmp.push_back(cv::Point2d(0.0, 4.0));
	tmp.push_back(cv::Point2d(0.0, 3.0));
	tmp.push_back(cv::Point2d(0.0, 2.0));
	tmp.push_back(cv::Point2d(0.0, 1.0));
	tmp.push_back(cv::Point2d(0.0, 0.0));
	tmp.push_back(cv::Point2d(0.0, -1.0));
	tmp.push_back(cv::Point2d(0.0, -2.0));
	tmp.push_back(cv::Point2d(0.0, -3.0));
	tmp.push_back(cv::Point2d(0.0, -4.0));
	tmp.push_back(cv::Point2d(0.0, -5.0));
	tmp.push_back(cv::Point2d(0.0, -6.0));
	return tmp;
}

std::vector<cv::Point2d> Calibrator::createTargetSpots3(){

	std::vector<cv::Point2d> tmp;
	tmp.push_back(cv::Point2d(6.0, 0.0));
	tmp.push_back(cv::Point2d(5.0, 0.0));
	tmp.push_back(cv::Point2d(4.0, 0.0));
	tmp.push_back(cv::Point2d(3.0, 0.0));
	tmp.push_back(cv::Point2d(2.0, 0.0));
	tmp.push_back(cv::Point2d(1.0, 0.0));
	tmp.push_back(cv::Point2d(0.0, 0.0));
	tmp.push_back(cv::Point2d(-1.0, 0.0));
	tmp.push_back(cv::Point2d(-2.0, 0.0));
	tmp.push_back(cv::Point2d(-3.0, 0.0));
	tmp.push_back(cv::Point2d(-4.0, 0.0));
	tmp.push_back(cv::Point2d(-5.0, 0.0));
	tmp.push_back(cv::Point2d(-6.0, 0.0));
	tmp.push_back(cv::Point2d(0.0, -6.0));
	tmp.push_back(cv::Point2d(0.0, -5.0));
	tmp.push_back(cv::Point2d(0.0, -4.0));
	tmp.push_back(cv::Point2d(0.0, -3.0));
	tmp.push_back(cv::Point2d(0.0, -2.0));
	tmp.push_back(cv::Point2d(0.0, -1.0));
	tmp.push_back(cv::Point2d(0.0, 0.0));
	tmp.push_back(cv::Point2d(0.0, 1.0));
	tmp.push_back(cv::Point2d(0.0, 2.0));
	tmp.push_back(cv::Point2d(0.0, 3.0));
	tmp.push_back(cv::Point2d(0.0, 4.0));
	tmp.push_back(cv::Point2d(0.0, 5.0));
	tmp.push_back(cv::Point2d(0.0, 6.0));
	return tmp;
}

std::vector<cv::Point2d> Calibrator::createTargetSpots4(){

	std::vector<cv::Point2d> tmp;
	tmp.push_back(cv::Point2d(-6.0, 0.0));
	tmp.push_back(cv::Point2d(-5.0, 0.0));
	tmp.push_back(cv::Point2d(-4.0, 0.0));
	tmp.push_back(cv::Point2d(-3.0, 0.0));
	tmp.push_back(cv::Point2d(-2.0, 0.0));
	tmp.push_back(cv::Point2d(-1.0, 0.0));
	tmp.push_back(cv::Point2d(0.0, 0.0));
	tmp.push_back(cv::Point2d(1.0, 0.0));
	tmp.push_back(cv::Point2d(2.0, 0.0));
	tmp.push_back(cv::Point2d(3.0, 0.0));
	tmp.push_back(cv::Point2d(4.0, 0.0));
	tmp.push_back(cv::Point2d(5.0, 0.0));
	tmp.push_back(cv::Point2d(6.0, 0.0));
	tmp.push_back(cv::Point2d(0.0, -6.0));
	tmp.push_back(cv::Point2d(0.0, -5.0));
	tmp.push_back(cv::Point2d(0.0, -4.0));
	tmp.push_back(cv::Point2d(0.0, -3.0));
	tmp.push_back(cv::Point2d(0.0, -2.0));
	tmp.push_back(cv::Point2d(0.0, -1.0));
	tmp.push_back(cv::Point2d(0.0, 0.0));
	tmp.push_back(cv::Point2d(0.0, 1.0));
	tmp.push_back(cv::Point2d(0.0, 2.0));
	tmp.push_back(cv::Point2d(0.0, 3.0));
	tmp.push_back(cv::Point2d(0.0, 4.0));
	tmp.push_back(cv::Point2d(0.0, 5.0));
	tmp.push_back(cv::Point2d(0.0, 6.0));
	return tmp;
}