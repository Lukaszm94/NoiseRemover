#include "noiseremoverapplication.h"
#include "QMessageBox"

NoiseRemoverApplication::NoiseRemoverApplication(int &argc, char **argv) : QApplication(argc, argv)
{
	gui = new MainWindow;
	noiseRemover = new NoiseRemover;

	connect(gui, SIGNAL(loadImageClicked()), this, SLOT(onLoadImageClicked()));
	connect(gui, SIGNAL(maskSizeChanged()), this, SLOT(onMaskChanged()));
	connect(gui, SIGNAL(maskTypeChanged()), this, SLOT(onMaskChanged()));
	connect(gui, SIGNAL(saveImageClicked()), this, SLOT(onSaveImageClicked()));

	updateNoiseRemoverMask();
	updateGUIImages();
	gui->show();
}

void NoiseRemoverApplication::onLoadImageClicked()
{
	QString imageLocation = gui->getImageLocation();
	if(imageLocation.isEmpty()) {
		qDebug() << "NoiseRemoverApplication::onLoadImageClicked(): image location is empty";
		return;
	}
	float scaleFactor = 1.0;
	if(gui->isResizeImageChecked()) {
		scaleFactor = gui->getResizeImageValue() / 100.0;
	}
	if(!noiseRemover->loadImage(imageLocation, scaleFactor)) {
		//TODO pop error message
		QMessageBox::critical(gui, "Error", "Unable to open image from path: " + imageLocation);
		return;
	} else {
		int width = noiseRemover->getImageSize().width;
		int height = noiseRemover->getImageSize().height;
		int smallerValue = width;
		if(smallerValue > height)
			smallerValue = height;
		gui->setMaskMaxSize(smallerValue / 2);
		gui->setMaskSize(smallerValue / 8);
	}

	updateNoiseRemoverMask();
	noiseRemover->process();
	updateGUIImages();

}

void NoiseRemoverApplication::onMaskChanged()
{
	updateNoiseRemoverMask();
	noiseRemover->process();
	updateGUIImages();
}

void NoiseRemoverApplication::onSaveImageClicked()
{
	cv::Mat imagePost = noiseRemover->getImagePost();
	QString savePath = gui->getImagePostSaveLocation();
	qDebug() << "NoiseRemoverApplication::onSaveImageClicked(): saving image to: " << savePath;
	if(imagePost.empty()) {
		qDebug() << "Mat is empty, return";
		return;
	}
	imagePost.convertTo(imagePost, CV_8UC1, 255);
	cvtColor(imagePost, imagePost, CV_GRAY2RGB);
	cv::imwrite(savePath.toStdString(), imagePost);
}


void NoiseRemoverApplication::updateGUIImages()
{
	gui->setImages(noiseRemover->getImagePre(), noiseRemover->getFrequencyDomainMagnitudePre(), noiseRemover->getImagePost(), noiseRemover->getFrequencyDomainMagnitudePost());
	gui->update();
}

void NoiseRemoverApplication::updateNoiseRemoverMask()
{
	noiseRemover->setMaskType(gui->getMaskType());
	noiseRemover->setMaskSize(gui->getMaskSize());
}
