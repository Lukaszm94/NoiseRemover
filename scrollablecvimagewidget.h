#ifndef SCROLLABLECVIMAGEWIDGET_H
#define SCROLLABLECVIMAGEWIDGET_H

#include "cvimagewidget.h"
#include <QScrollArea>

class ScrollableCVImageWidget : public QScrollArea
{
	Q_OBJECT
public:
	ScrollableCVImageWidget(QWidget* parent = 0);
	//QSize sizeHint() const;
	//QSize minimumSizeHint() const;
public slots:
	void showImage(const cv::Mat image);
private:
	CVImageWidget* imageWidget;
};

#endif // SCROLLABLECVIMAGEWIDGET_H
