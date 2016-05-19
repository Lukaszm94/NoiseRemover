#ifndef MANUALNOISEREMOVALWIDGET_H
#define MANUALNOISEREMOVALWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "masktype.h"

class ManualNoiseRemovalWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ManualNoiseRemovalWidget(QWidget *parent = 0);
	MaskType getMaskType();
	int getMaskSize();
	void setMaskMaxSize(int maxSize);
	void setMaskSize(int size);
signals:
	void maskTypeChanged();
	void maskSizeChanged();
private slots:
	void onMaskSizeSliderValueChanged(int value);
	void onMaskTypeChanged();
private:
	QRadioButton* circleMaskRadioButton;
	QRadioButton* squareMaskRadioButton;
	QRadioButton* diamondMaskRadioButton;

	QSlider* maskSizeSlider;
	QLabel* maskSizeLabel;

};

#endif // MANUALNOISEREMOVALWIDGET_H
