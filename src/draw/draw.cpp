#include "draw.hpp"


Draw::Draw() {}

Draw::~Draw() {}

cv::Mat Draw::spots(const cv::Mat& src, const std::vector<cv::Point2d>& spots){
    
    cv::Mat tmp;
    cv::cvtColor(src, tmp, cv::COLOR_BGR2GRAY);
    
    for (const auto& spot : spots)
    {
		if (spot.x > 0 && spot.y > 0 && spot.x < tmp.cols && spot.y < tmp.rows)
        {
            cv::circle( tmp, spot, 1, cv::Scalar(255), 1, cv::LINE_4);
        }
    }
    return tmp;
}

cv::Mat Draw::labels(const cv::Mat& src, const std::vector<cv::Point2d>& spots){
    
    cv::Mat tmp;
    cv::cvtColor(src, tmp, cv::COLOR_BGR2GRAY);
    int label = 1;
    for (const auto& spot : spots)
    {
        if (spot.x > 0 && spot.y > 0 && spot.x < tmp.cols && spot.y < tmp.rows)
        {
            cv::putText(tmp, std::to_string(label), spot, cv::FONT_HERSHEY_SIMPLEX, 0.33, cv::Scalar(255));
        }
        label++;
    }
    return tmp;
}
cv::Mat Draw::all(const cv::Mat& src, const std::vector<cv::Point2d>& spots){
    
    cv::Mat tmp;
    cv::cvtColor(src, tmp, cv::COLOR_BGR2GRAY);
    int label = 1;
    for (const auto& spot : spots)
    {
        if (spot.x > 0 && spot.y > 0 && spot.x < tmp.cols && spot.y < tmp.rows)
        {
            cv::circle( tmp, spot, 1, cv::Scalar(255), 1, cv::LINE_4);
            cv::putText(tmp, std::to_string(label), spot, cv::FONT_HERSHEY_SIMPLEX, 0.33, cv::Scalar(255));
        }
        label++;
    }
    return tmp;
}