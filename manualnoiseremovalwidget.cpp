#include "manualnoiseremovalwidget.h"
#include "QDebug"

ManualNoiseRemovalWidget::ManualNoiseRemovalWidget(QWidget *parent) : QWidget(parent)
{
	circleMaskRadioButton = new QRadioButton("circle");
	squareMaskRadioButton = new QRadioButton("square");
	diamondMaskRadioButton = new QRadioButton("diamond");
	maskSizeSlider = new QSlider(Qt::Horizontal);
	maskSizeLabel = new QLabel;

	QVBoxLayout* maskTypeLayout = new QVBoxLayout;
	maskTypeLayout->addWidget(circleMaskRadioButton);
	maskTypeLayout->addWidget(squareMaskRadioButton);
	maskTypeLayout->addWidget(diamondMaskRadioButton);

	QGroupBox* maskTypeGroupBox = new QGroupBox("Mask type");
	maskTypeGroupBox->setLayout(maskTypeLayout);

	QHBoxLayout* maskSizeLayout = new QHBoxLayout;
	maskSizeLayout->addWidget(maskSizeSlider);
	maskSizeLayout->addWidget(maskSizeLabel);

	QGroupBox* maskSizeGroupBox = new QGroupBox("Mask size");
	maskSizeGroupBox->setLayout(maskSizeLayout);

	QHBoxLayout* mainLayout = new QHBoxLayout;
	mainLayout->addWidget(maskSizeGroupBox);
	mainLayout->addWidget(maskTypeGroupBox);
	mainLayout->addStretch();

	this->setLayout(mainLayout);
	maskSizeSlider->setFixedWidth(100);
	squareMaskRadioButton->setChecked(true);
	maskSizeGroupBox->setFixedWidth(180);

	QFont largeFont;
	largeFont.setPixelSize(16);
	maskSizeLabel->setFont(largeFont);
	maskSizeSlider->setTickInterval(10);

	connect(maskSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(onMaskSizeSliderValueChanged(int)));
	connect(circleMaskRadioButton, SIGNAL(clicked()), this, SLOT(onMaskTypeChanged()));
	connect(squareMaskRadioButton, SIGNAL(clicked()), this, SLOT(onMaskTypeChanged()));
	connect(diamondMaskRadioButton, SIGNAL(clicked()), this, SLOT(onMaskTypeChanged()));
}

MaskType ManualNoiseRemovalWidget::getMaskType()
{
	if(squareMaskRadioButton->isChecked())
		return MaskType::SQUARE;
	else if(circleMaskRadioButton->isChecked())
		return MaskType::CIRCLE;
	else if(diamondMaskRadioButton->isChecked())
		return MaskType::DIAMOND;
	else {
		qDebug() << "ManualNoiseRemovalWidget::getMaskType(): no mask type selected, returning MaskType::SQUARE";
		return MaskType::SQUARE;
	}
}

int ManualNoiseRemovalWidget::getMaskSize()
{
	return maskSizeSlider->value();
}

void ManualNoiseRemovalWidget::onMaskSizeSliderValueChanged(int value)
{
	maskSizeLabel->setText(QString::number(value) + "px");
	emit maskSizeChanged();
}

void ManualNoiseRemovalWidget::onMaskTypeChanged()
{
	emit maskTypeChanged();
}

void ManualNoiseRemovalWidget::setMaskMaxSize(int maxSize)
{
	maskSizeSlider->setMaximum(maxSize);
}

void ManualNoiseRemovalWidget::setMaskSize(int size)
{
	maskSizeSlider->setValue(size);
}
