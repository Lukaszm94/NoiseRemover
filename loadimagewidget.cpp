#include "loadimagewidget.h"

LoadImageWidget::LoadImageWidget(QWidget *parent) : QWidget(parent)
{
	imageLocationLineEdit = new QLineEdit;
	browseButton = new QPushButton("Browse");
	loadImageButton = new QPushButton("Load image");
	resizeImageCheckbox = new QCheckBox("Resize image:");
	resizeImageSpinbox = new QSpinBox;

	QHBoxLayout* imageLocationLayout = new QHBoxLayout;
	imageLocationLayout->addWidget(imageLocationLineEdit);
	imageLocationLayout->addWidget(browseButton);
	imageLocationLayout->addStretch();

	QHBoxLayout* resizeImageLayout = new QHBoxLayout;
	resizeImageLayout->addWidget(resizeImageCheckbox);
	resizeImageLayout->addWidget(resizeImageSpinbox);
	resizeImageLayout->addWidget(new QLabel("%"));
	resizeImageLayout->addStretch();

	QHBoxLayout* loadLayout = new QHBoxLayout;
	loadLayout->addWidget(loadImageButton);
	loadLayout->addStretch();

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addLayout(imageLocationLayout);
	mainLayout->addLayout(resizeImageLayout);
	mainLayout->addLayout(loadLayout);
	this->setLayout(mainLayout);

	resizeImageSpinbox->setMaximum(100);
	resizeImageSpinbox->setValue(100);
	resizeImageCheckbox->setChecked(false);
	resizeImageSpinbox->setEnabled(false);
	resizeImageSpinbox->setFixedWidth(50);

	connect(browseButton, SIGNAL(clicked()), this, SLOT(onBrowseButtonClicked()));
	connect(loadImageButton, SIGNAL(clicked()), this, SLOT(onLoadImageButtonClicked()));
	connect(resizeImageCheckbox, SIGNAL(toggled(bool)), resizeImageSpinbox, SLOT(setEnabled(bool)));
}

QString LoadImageWidget::getImageLocation()
{
	return imageLocationLineEdit->text();
}

bool LoadImageWidget::isResizeImageChecked()
{
	return resizeImageCheckbox->isChecked();
}

int LoadImageWidget::getResizeImageValue()
{
	return resizeImageSpinbox->value();
}

void LoadImageWidget::onLoadImageButtonClicked()
{
	emit loadImageClicked();
}

void LoadImageWidget::onBrowseButtonClicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Select image"), "", tr("Images (*.png *.jpg)"));
	if(!fileName.isEmpty()) {
		imageLocationLineEdit->setText(fileName);
	}
}
