#include "noiseremover.h"
#include <QDebug>
#include <vector>

using namespace cv;

NoiseRemover::NoiseRemover()
{
}

bool NoiseRemover::loadImage(QString fileLocation, float scale)
{
	fileLoc = fileLocation;
	imagePre = imread(fileLocation.toStdString(), 0);
	if(imagePre.empty()) {
		return false;
	}
	Size imageSize = imagePre.size();
	imageSize.height *= scale;
	imageSize.width *= scale;
	Mat imageTmp = imagePre.clone();
	resize(imageTmp, imagePre, imageSize);
	int m = getOptimalDFTSize(imagePre.rows);
	int n = getOptimalDFTSize(imagePre.cols); // on the border add zero values
	copyMakeBorder(imagePre, imagePre, 0, m - imagePre.rows, 0, n - imagePre.cols, BORDER_CONSTANT, Scalar::all(0));
	return true;
}

void NoiseRemover::setMaskType(MaskType newMaskType)
{
	maskType = newMaskType;
}

void NoiseRemover::setMaskSize(int newMaskSize)
{
	maskSize = newMaskSize;
}

void NoiseRemover::process()
{
	if(imagePre.empty()) {
		qDebug() << "NoiseRemover::process(): imagePre is empty, returning";
		return;
	}
	Mat planes[] = {Mat_<float>(imagePre), Mat::zeros(imagePre.size(), CV_32F)};
	Mat complexI;
	merge(planes, 2, complexI);         // Add to the expanded another plane with zeros
	dft(complexI, complexI);            // this way the result may fit in the source matrix
	split(complexI, planes);

	FrequencyDomainImage freqDomainImage;
	freqDomainImage.real = planes[0].clone();
	freqDomainImage.img = planes[1].clone();
	rearrangeQuadrants(freqDomainImage.real);
	rearrangeQuadrants(freqDomainImage.img);
	frequencyDomainMagnitudePre = calculateMagnitude(freqDomainImage);
	//imshow("frequencyDomainMagnitudePre", frequencyDomainMagnitudePre);

	freqDomainImage = eraseHighFrequencies(freqDomainImage);
	frequencyDomainMagnitudePost = calculateMagnitude(freqDomainImage);
	//imshow("frequencyDomainMagnitudePost", frequencyDomainMagnitudePost);

	//merge them into complex again
	rearrangeQuadrants(freqDomainImage.real);
	rearrangeQuadrants(freqDomainImage.img);
	planes[0] = freqDomainImage.real;
	planes[1] = freqDomainImage.img;
	merge(planes, 2, complexI);
	//Mat inverse;
	dft(complexI, complexI, DFT_INVERSE);
	split(complexI, planes);// planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	freqDomainImage.real = planes[0];
	freqDomainImage.img = planes[1];
	imagePost = calculateMagnitude(freqDomainImage, false);
	//imshow("imagePost", imagePost);
}

Size NoiseRemover::getImageSize()
{
	return imagePre.size();
}

cv::Mat NoiseRemover::getImagePre()
{
	if(imagePre.data == NULL) {
		qDebug() << "NoiseRemover::getImagePre(): data is NULL";
	}
	return imagePre;
}

cv::Mat NoiseRemover::getFrequencyDomainMagnitudePre()
{
	if(frequencyDomainMagnitudePre.data == NULL) {
		qDebug() << "NoiseRemover::getFrequencyDomainMagnitudePre(): data is NULL";
	}
	return frequencyDomainMagnitudePre;
}

cv::Mat NoiseRemover::getImagePost()
{
	if(imagePost.data == NULL) {
		qDebug() << "NoiseRemover::getImagePost(): data is NULL";
	}
	return imagePost;
}

cv::Mat NoiseRemover::getFrequencyDomainMagnitudePost()
{
	if(frequencyDomainMagnitudePost.data == NULL) {
		qDebug() << "NoiseRemover::getFrequencyDomainMagnitudePost(): data is NULL";
	}
	return frequencyDomainMagnitudePost;
}

void NoiseRemover::rearrangeQuadrants(Mat &mat)
{
	// crop the spectrum, if it has an odd number of rows or columns
	mat = mat(Rect(0, 0, mat.cols & -2, mat.rows & -2));
	// rearrange the quadrants of Fourier image  so that the origin is at the image center
	int cx = mat.cols/2;
	int cy = mat.rows/2;

	Mat q0(mat, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	Mat q1(mat, Rect(cx, 0, cx, cy));  // Top-Right
	Mat q2(mat, Rect(0, cy, cx, cy));  // Bottom-Left
	Mat q3(mat, Rect(cx, cy, cx, cy)); // Bottom-Right

	Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);
}

Mat NoiseRemover::calculateMagnitude(FrequencyDomainImage freqDomainImage, bool logEnabled)
{
	Mat image = Mat_<float>(freqDomainImage.real.size());
	magnitude(freqDomainImage.real, freqDomainImage.img, image);
	if(logEnabled) {
		image += Scalar::all(1);                    // switch to logarithmic scale
		log(image, image);
	}

	normalize(image, image, 0, 1, NORM_MINMAX);
	return image;
}

FrequencyDomainImage NoiseRemover::eraseHighFrequencies(FrequencyDomainImage freqDomainImage)
{
	Mat real = freqDomainImage.real.clone();
	Mat img = freqDomainImage.img.clone();

	applyMask(real, maskType, maskSize);
	applyMask(img, maskType, maskSize);

	FrequencyDomainImage postFreqImage;
	postFreqImage.real = real;
	postFreqImage.img = img;
	return postFreqImage;
}

void NoiseRemover::applyMask(Mat &mat, MaskType maskType_, int maskSize_)
{
	int centerX = mat.cols / 2;
	int centerY = mat.rows / 2;
	DistanceType distanceType = DistanceType::EUCLIDIAN;
	if(maskType_ == MaskType::CIRCLE) {
		distanceType = DistanceType::EUCLIDIAN;
	} else if(maskType_ == MaskType::SQUARE) {
		distanceType = DistanceType::CHEBYSHEV;
	} else if(maskType_ == MaskType::DIAMOND) {
		distanceType = DistanceType::MANHATTAN;
	} else {
		qDebug() << "NoiseRemover::applyMask(): unknown mask type";
	}
	for(int x = 0; x < mat.cols; x++) {
		for(int y = 0; y < mat.rows; y++) {
			if(getDistanceFromCenter(x, y, centerX, centerY, distanceType) >= maskSize_) {
				mat.at<float>(y,x) = 0.0;
			}
		}
	}
}

int NoiseRemover::getDistanceFromCenter(int x, int y, int centerX, int centerY, DistanceType distanceType)
{
	if(distanceType == DistanceType::EUCLIDIAN) {
		return sqrt(pow((x - centerX),2) + pow(y - centerY,2));
	} else if(distanceType == DistanceType::MANHATTAN) {
		return (fabs(centerX - x) + fabs(centerY - y));
	} else if(distanceType == DistanceType::CHEBYSHEV) {
		int dx = fabs(x - centerX);
		int dy = fabs(y - centerY);
		if(dx > dy) {
			return dx;
		} else {
			return dy;
		}
	} else {
		qDebug() << "NoiseRemover::getDistanceFromCenter(): unknown distance type";
		return 0.0;
	}

}

void NoiseRemover::eraseNoise(Mat &mat)
{
	int centerX = mat.cols / 2;
	int width = mat.cols;
	int height = mat.rows;
	double A1 = (double) height / width;
	double A2 = -A1;
	double B2 = height;
	for(int x = 0; x < width; x++) {
		for(int y = 0; y < height; y++) {
			double Y1 = A1 * x;
			double Y2 = A2 * x + B2;
			if(x < centerX) {
				if((y > Y1) && (y < Y2)) {
					mat.at<float>(y,x) = 0.0;
				}
			} else if(x > centerX) {
				if((y > Y2) && (y < Y1)) {
					mat.at<float>(y,x) = 0.0;
				}
			}
		}
	}
}
