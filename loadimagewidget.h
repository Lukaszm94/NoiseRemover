#ifndef LOADIMAGEWIDGET_H
#define LOADIMAGEWIDGET_H

#include <QWidget>
#include <QtWidgets>

class LoadImageWidget : public QWidget
{
	Q_OBJECT
public:
	explicit LoadImageWidget(QWidget *parent = 0);
	QString getImageLocation();
	bool isResizeImageChecked();
	int getResizeImageValue();
signals:
	void loadImageClicked();
private slots:
	void onBrowseButtonClicked();
	void onLoadImageButtonClicked();
private:
	QLineEdit* imageLocationLineEdit;
	QPushButton* browseButton;
	QPushButton* loadImageButton;
	QCheckBox* resizeImageCheckbox;
	QSpinBox* resizeImageSpinbox;
};

#endif // LOADIMAGEWIDGET_H
