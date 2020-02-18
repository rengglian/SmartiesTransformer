#include "analyzer.hpp"

template<typename T>
std::vector<double> linspace(T start_in, T end_in, int num_in);

Analyzer::Analyzer() {}

Analyzer::~Analyzer() {}

std::vector<cv::Point2d> Analyzer::Sort(const std::vector<cv::Point2d>& unsorted_spots){

    std::vector<cv::Point2d> unsorted = unsorted_spots;

    const cv::Point2d avg_spot = std::accumulate(unsorted.begin(), unsorted.end(), cv::Point2d(0.0,0.0), std::plus<cv::Point2d>()) / static_cast<double>(unsorted.size());
    
    cv::Point2d x1 = avg_spot;
    cv::Point2d x2 = avg_spot;
    cv::Point2d y1 = avg_spot;
    cv::Point2d y2 = avg_spot;    

    for (const auto& spot : unsorted)
    {
		if (spot.x > x1.x && spot.y > x1.y) x1 = spot;
		if (spot.x < x2.x && spot.y < x2.y)	x2 = spot;
		if (spot.x > y2.x && spot.y < y2.y)	y2 = spot;
		if (spot.x < y1.x && spot.y > y1.y)	y1 = spot;									
    }

    cornerSpots.clear();
    cornerSpots.push_back(x1);
    cornerSpots.push_back(x2);
    cornerSpots.push_back(y1);
    cornerSpots.push_back(y2);

	const double slopeX = calculateSlope(x1, x2);
	const double slopeY = calculateSlope(y1, y2);

	const double offsetX = calculateOffset(x1, slopeX);
	const double offsetY = calculateOffset(y1, slopeY);

	const auto Xx_spaced = linspace(x1.x, x2.x, 13);
	const auto Yx_spaced = linspace(y1.x, y2.x, 13);
	
	std::vector<double>Xy_spaced(Xx_spaced.size(), 0.0);
	std::transform(Xx_spaced.begin(), Xx_spaced.end(), Xy_spaced.begin(), [&slopeX, &offsetX](auto& c){return c*slopeX+offsetX;});

	std::vector<double>Yy_spaced(Yx_spaced.size(), 0.0);
	std::transform(Yx_spaced.begin(), Yx_spaced.end(), Yy_spaced.begin(), [&slopeY, &offsetY](auto& c){return c*slopeY+offsetY;});

    std::vector<cv::Point2d> sorted_spots;
    xAxisSpots.clear();
    yAxisSpots.clear();
    
    for (int i = 0; i < 13; i++)
	{
		cv::Point2d refPointX{Xx_spaced[i], Xy_spaced[i]};
		cv::Point2d refPointY{Yx_spaced[i], Yy_spaced[i]};
		
		std::sort(unsorted.begin(), unsorted.end(), 
			[refPointX](const cv::Point2f &a, const cv::Point2f &b)
			{
				return std::pow(refPointX.x - a.x,2) + std::pow(refPointX.y - a.y,2) < std::pow(refPointX.x - b.x,2) + std::pow(refPointX.y - b.y,2)  ; //or whatever you like
		});
		xAxisSpots.push_back(unsorted[0]);
        sorted_spots.push_back(unsorted[0]);

		std::sort(unsorted.begin(), unsorted.end(), 
			[refPointY](const cv::Point2f &a, const cv::Point2f &b)
			{
				return std::pow(refPointY.x - a.x,2) + std::pow(refPointY.y - a.y,2) < std::pow(refPointY.x - b.x,2) + std::pow(refPointY.y - b.y,2)  ; //or whatever you like
		});
		yAxisSpots.push_back(unsorted[0]);		
	}

	sorted_spots.insert(sorted_spots.end(), yAxisSpots.begin(), yAxisSpots.end());

    return sorted_spots;
}

const double Analyzer::calculateSlope(const cv::Point2d start, const cv::Point2d end)
{
	return (end.y - start.y)/(end.x - start.x);
}
const double Analyzer::calculateOffset(const cv::Point2d p, const double slope)
{
    return p.y - slope * p.x;
}

template<typename T>
std::vector<double> linspace(T start_in, T end_in, int num_in)
{

  std::vector<double> linspaced;

  double start = static_cast<double>(start_in);
  double end = static_cast<double>(end_in);
  double num = static_cast<double>(num_in);

  if (num == 0) { return linspaced; }
  if (num == 1) 
    {
      linspaced.push_back(start);
      return linspaced;
    }

  double delta = (end - start) / (num - 1);

  for(int i=0; i < num-1; ++i)
    {
      linspaced.push_back(start + delta * i);
    }
  linspaced.push_back(end);
  return linspaced;
}