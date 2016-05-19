#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "scrollablecvimagewidget.h"
#include "loadimagewidget.h"
#include "manualnoiseremovalwidget.h"
#include "saveimageswidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow();
	QString getImageLocation();
	int getMaskSize();
	MaskType getMaskType();
	void setMaskMaxSize(int maxSize);
	void setMaskSize(int size);
	void setImages(cv::Mat imagePre_, cv::Mat frequencyDomainMagnitudePre_ ,cv::Mat imagePost_, cv::Mat frequencyDomainMagnitudePost_);
	bool isResizeImageChecked();
	int getResizeImageValue();
	QString getImagePostSaveLocation();

public slots:

signals:
	void loadImageClicked();
	void maskTypeChanged();
	void maskSizeChanged();
	void saveImageClicked();
private slots:
	void onLoadImageClicked();
	void onMaskTypeChanged();
	void onMaskSizeChanged();
	void onSaveImageClicked();
private:
	ScrollableCVImageWidget* imagePre, *imagePost, *frequencyDomainMagnitudePre, *frequencyDomainMagnitudePost;
	QTabWidget* tabWidget;
	LoadImageWidget* loadImageWidget;
	ManualNoiseRemovalWidget* manualControlWidget;
	SaveImagesWidget* saveImageWidget;
	//QWidget* autoWidget;
};

#endif // MAINWINDOW_H
