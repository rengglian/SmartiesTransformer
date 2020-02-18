#pragma once
#include <opencv2/core/types.hpp>
#include <iostream>
#include <numeric>

class Analyzer {

	public:

		Analyzer();
		~Analyzer();
        std::vector<cv::Point2d> Sort(const std::vector<cv::Point2d>& unsorted_spots);
        std::vector<cv::Point2d> GetXAxisSpots() {return xAxisSpots;};
        std::vector<cv::Point2d> GetYAxisSpots() {return yAxisSpots;};
        std::vector<cv::Point2d> GetCornerSpots() {return cornerSpots;};

	private:

        const double calculateSlope(const cv::Point2d start, const cv::Point2d end);
        const double calculateOffset(const cv::Point2d p, const double slope);  

        std::vector<cv::Point2d> xAxisSpots;
	    std::vector<cv::Point2d> yAxisSpots;
        std::vector<cv::Point2d> cornerSpots;

};