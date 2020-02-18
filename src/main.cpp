
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/core/hal/interface.h>
#include <iostream>

#include "config/config.hpp"
#include "image/image.hpp"
#include "analyzer/analyzer.hpp"
#include "draw/draw.hpp"
#include "calibrator/calibrator.hpp"

int main( int argc, char** argv )
{
	//Config config;
	std::shared_ptr<Config> config_ = std::make_shared<Config>(argc >=1 ? argv[1] : "./config.json");
	
	std::shared_ptr<Image> image_ = std::make_shared<Image>(config_);
	std::shared_ptr<Calibrator> calibrator_ = std::make_shared<Calibrator>(config_);
	std::shared_ptr<Analyzer> analyzer_ = std::make_shared<Analyzer>();
	std::shared_ptr<Draw> draw_ = std::make_shared<Draw>();
	auto img = image_->GetImage();
	auto src = image_->GetFilteredImage();
	
	auto unsorted_spots = image_->GetSpots();

	auto sorted_spots = analyzer_->Sort(unsorted_spots);
	
	auto result = calibrator_->affine(sorted_spots);

	auto targetSpots = calibrator_->GetTargetSpots();

	for(int i = 0; i< targetSpots.size(); i++)
	{
		targetSpots[i] = (-targetSpots[i])*config_->GetPixelMM()+cv::Point2d(src.cols/2.0,src.rows/2.0);
	}

	std::cout << "result\n" << result << std::endl;

	cv::Point2d center_orig{static_cast<double>(img.cols)/2, static_cast<double>(img.rows)/2};
	cv::Point2d new_center;
	new_center.x = result.at<double>(0, 0)*center_orig.x + result.at<double>(0,1)*center_orig.y;
	new_center.y = result.at<double>(1, 0)*center_orig.x + result.at<double>(1,1)*center_orig.y;

	result.at<double>(0, 2) = center_orig.x-new_center.x;
	result.at<double>(1, 2) = center_orig.y-new_center.y;

	cv::Mat src_transformed;
    cv::warpAffine(src, src_transformed, result, src.size());
	cv::Mat bgImage = image_->GetBackgroundImage();
	cv::Mat resultImg = cv::Mat::zeros(bgImage.size(), bgImage.type());
	cv::cvtColor ( src_transformed, src_transformed, cv::COLOR_GRAY2BGR );
	cv::addWeighted(bgImage , 0.7, src_transformed, 0.3, 0, resultImg);

	cv::imshow("source", (image_->GetImage()));
	cv::imshow("filtered circles", (image_->GetFilteredImage()));
	cv::imshow("X Spots", draw_->all(image_->GetImage(), analyzer_->GetXAxisSpots()));
	cv::imshow("Y Spots", draw_->all(image_->GetImage(), analyzer_->GetYAxisSpots()));
	cv::imshow("Corners Spots", draw_->all(image_->GetImage(), analyzer_->GetCornerSpots()));
	cv::imshow("Sorted", draw_->all(image_->GetImage(), sorted_spots));
	cv::imshow("Target", draw_->all(image_->GetImage(), targetSpots));

	cv::imshow("Result", resultImg);

	cv::imwrite("result.jpg", (image_->GetFilteredImage()));
	//cv::imshow("Result", src_transformed+image_->GetImage());
	cv::waitKey();

    return 0;
}