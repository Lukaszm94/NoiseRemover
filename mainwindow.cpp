#include "mainwindow.h"

MainWindow::MainWindow()
{
	imagePre = new ScrollableCVImageWidget;
	imagePost = new ScrollableCVImageWidget;
	frequencyDomainMagnitudePre = new ScrollableCVImageWidget;
	frequencyDomainMagnitudePost = new ScrollableCVImageWidget;
	tabWidget = new QTabWidget;
	loadImageWidget = new LoadImageWidget;
	manualControlWidget = new ManualNoiseRemovalWidget;
	saveImageWidget = new SaveImagesWidget;

	QFont bigFont;
	bigFont.setPixelSize(20);
	bigFont.setBold(true);

	QFont mediumFont;
	mediumFont.setPixelSize(15);

	QVBoxLayout* preLayout = new QVBoxLayout;
	QLabel* labelHeaderPre = new QLabel("Before processing");
	QLabel* labelImagePre = new QLabel("Image");
	QLabel* labelFrequencyDomainMagnitudePre = new QLabel("Frequency domain magnitude");
	preLayout->addWidget(labelHeaderPre, 0, Qt::AlignHCenter);
	preLayout->addWidget(labelImagePre, 0, Qt::AlignHCenter);
	preLayout->addWidget(imagePre);
	preLayout->addWidget(labelFrequencyDomainMagnitudePre, 0, Qt::AlignHCenter);
	preLayout->addWidget(frequencyDomainMagnitudePre);

	QVBoxLayout* postLayout = new QVBoxLayout;
	QLabel* labelHeaderPost = new QLabel("After processing");
	QLabel* labelImagePost = new QLabel("Image");
	QLabel* labelFrequencyDomainMagnitudePost = new QLabel("Frequency domain magnitude");
	postLayout->addWidget(labelHeaderPost, 0, Qt::AlignHCenter);
	postLayout->addWidget(labelImagePost, 0, Qt::AlignHCenter);
	postLayout->addWidget(imagePost);
	postLayout->addWidget(labelFrequencyDomainMagnitudePost, 0, Qt::AlignHCenter);
	postLayout->addWidget(frequencyDomainMagnitudePost);

	labelHeaderPre->setFont(bigFont);
	labelHeaderPost->setFont(bigFont);
	labelImagePre->setFont(mediumFont);
	labelFrequencyDomainMagnitudePre->setFont(mediumFont);
	labelImagePost->setFont(mediumFont);
	labelFrequencyDomainMagnitudePost->setFont(mediumFont);

	QHBoxLayout* imagesLayout = new QHBoxLayout;
	imagesLayout->addLayout(preLayout);
	imagesLayout->addLayout(postLayout);

	tabWidget->addTab(loadImageWidget, "Load");
	tabWidget->addTab(manualControlWidget, "Manual");
	tabWidget->addTab(saveImageWidget, "Save");

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addLayout(imagesLayout);
	mainLayout->addWidget(tabWidget);
	QWidget* mainWidget = new QWidget;
	mainWidget->setLayout(mainLayout);
	this->setCentralWidget(mainWidget);
	tabWidget->setFixedHeight(150);

	connect(loadImageWidget, SIGNAL(loadImageClicked()), this, SLOT(onLoadImageClicked()));
	connect(manualControlWidget, SIGNAL(maskSizeChanged()), this, SLOT(onMaskSizeChanged()));
	connect(manualControlWidget, SIGNAL(maskTypeChanged()), this, SLOT(onMaskTypeChanged()));
	connect(saveImageWidget, SIGNAL(saveImagePostClicked()), this, SLOT(onSaveImageClicked()));
}

QString MainWindow::getImageLocation()
{
	return loadImageWidget->getImageLocation();
}

int MainWindow::getMaskSize()
{
	return manualControlWidget->getMaskSize();
}

MaskType MainWindow::getMaskType()
{
	return manualControlWidget->getMaskType();
}

void MainWindow::setImages(cv::Mat imagePre_, cv::Mat frequencyDomainMagnitudePre_, cv::Mat imagePost_, cv::Mat frequencyDomainMagnitudePost_)
{
	imagePre->showImage(imagePre_);
	frequencyDomainMagnitudePre->showImage(frequencyDomainMagnitudePre_);
	imagePost->showImage(imagePost_);
	frequencyDomainMagnitudePost->showImage(frequencyDomainMagnitudePost_);
}

bool MainWindow::isResizeImageChecked()
{
	return loadImageWidget->isResizeImageChecked();
}

int MainWindow::getResizeImageValue()
{
	return loadImageWidget->getResizeImageValue();
}

QString MainWindow::getImagePostSaveLocation()
{
	return saveImageWidget->getImagePostSavePath();
}

void MainWindow::onLoadImageClicked()
{
	emit loadImageClicked();
}

void MainWindow::onMaskTypeChanged()
{
	emit maskTypeChanged();
}

void MainWindow::onMaskSizeChanged()
{
	emit maskSizeChanged();
}

void MainWindow::onSaveImageClicked()
{
	emit saveImageClicked();
}

void MainWindow::setMaskMaxSize(int maxSize)
{
	manualControlWidget->setMaskMaxSize(maxSize);
}

void MainWindow::setMaskSize(int size)
{
	manualControlWidget->setMaskSize(size);
}
