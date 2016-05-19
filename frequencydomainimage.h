#ifndef FREQUENCYDOMAINIMAGE_H
#define FREQUENCYDOMAINIMAGE_H

#include <opencv2/opencv.hpp>

struct FrequencyDomainImage
{
	cv::Mat real;
	cv::Mat img;
};

#endif // FREQUENCYDOMAINIMAGE_H
