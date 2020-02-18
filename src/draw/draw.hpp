#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

class Draw {

	public:

		Draw();
		~Draw();
		cv::Mat spots(const cv::Mat& src, const std::vector<cv::Point2d>& spots);
		cv::Mat labels(const cv::Mat& src, const std::vector<cv::Point2d>& spots);
		cv::Mat all(const cv::Mat& src, const std::vector<cv::Point2d>& spots);
	private:

};