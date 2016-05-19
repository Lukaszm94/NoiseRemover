#include "scrollablecvimagewidget.h"
#include "QtWidgets"

ScrollableCVImageWidget::ScrollableCVImageWidget(QWidget* parent) : QScrollArea(parent)
{
	imageWidget = new CVImageWidget;
	this->setWidget(imageWidget);
}

void ScrollableCVImageWidget::showImage(const cv::Mat image)
{
	imageWidget->showImage(image);
}
