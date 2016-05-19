#include "saveimageswidget.h"
#include <QFileDialog>

SaveImagesWidget::SaveImagesWidget(QWidget *parent) : QWidget(parent)
{
	imagePostPathLineEdit = new QLineEdit;
	browseImagePostPathButton = new QPushButton("Browse");
	saveImagePostButton = new QPushButton("Save");

	QHBoxLayout* savePathLayout = new QHBoxLayout;
	savePathLayout->addWidget(new QLabel("Path:"));
	savePathLayout->addWidget(imagePostPathLineEdit);
	savePathLayout->addWidget(browseImagePostPathButton);
	savePathLayout->addWidget(saveImagePostButton);
	savePathLayout->addStretch();

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addWidget(new QLabel("Save image after processing"));
	mainLayout->addLayout(savePathLayout);
	mainLayout->addStretch();
	this->setLayout(mainLayout);

	connect(browseImagePostPathButton, SIGNAL(clicked(bool)), this, SLOT(onBrowseImagePostClicked()));
	connect(saveImagePostButton, SIGNAL(clicked(bool)), this, SLOT(onSaveImagePostClicked()));
}

QString SaveImagesWidget::getImagePostSavePath()
{
	return imagePostPathLineEdit->text();
}

void SaveImagesWidget::onBrowseImagePostClicked()
{
	QString newPath = QFileDialog::getSaveFileName(this, "Save image post", "", "Images (*.png)");
	if(newPath.isEmpty()) {
		return;
	}
	imagePostPathLineEdit->setText(newPath);
}

void SaveImagesWidget::onSaveImagePostClicked()
{
	emit saveImagePostClicked();
}
