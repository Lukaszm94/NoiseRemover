#ifndef NOISEREMOVER_H
#define NOISEREMOVER_H

#include <QString>
#include <opencv2/opencv.hpp>
#include "masktype.h"
#include "frequencydomainimage.h"
#include "distancetype.h"


class NoiseRemover
{
public:
	NoiseRemover();
	bool loadImage(QString fileLocation, float scale = 1.0);
	void setMaskType(MaskType newMaskType);
	void setMaskSize(int newMaskSize);
	void process();
	cv::Size getImageSize();
	cv::Mat getImagePre();
	cv::Mat getFrequencyDomainMagnitudePre();
	cv::Mat getImagePost();
	cv::Mat getFrequencyDomainMagnitudePost();
private:
	//modifies passed Mat
	void rearrangeQuadrants(cv::Mat &mat);
	//creates new Mat
	cv::Mat calculateMagnitude(FrequencyDomainImage freqDomainImage, bool logEnabled = true);
	//creates new FrequencyDomainImage (with new Mats)
	FrequencyDomainImage eraseHighFrequencies(FrequencyDomainImage freqDomainImage);
	//modifies mat
	void applyMask(cv::Mat &mat, MaskType maskType_, int maskSize_);
	int getDistanceFromCenter(int x,int y,int centerX,int centerY, DistanceType distanceType = DistanceType::EUCLIDIAN);
	//tmp
	void eraseNoise(cv::Mat &mat);

	MaskType maskType;
	int maskSize;
	cv::Mat imagePre;
	cv::Mat imagePost;
	cv::Mat frequencyDomainMagnitudePre;
	cv::Mat frequencyDomainMagnitudePost;
	//tmp
	QString fileLoc;
};

#endif // NOISEREMOVER_H
