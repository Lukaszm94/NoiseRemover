#ifndef SAVEIMAGESWIDGET_H
#define SAVEIMAGESWIDGET_H

#include <QWidget>
#include <QtWidgets>

class SaveImagesWidget : public QWidget
{
	Q_OBJECT
public:
	explicit SaveImagesWidget(QWidget *parent = 0);
	QString getImagePostSavePath();
signals:
	void saveImagePostClicked();
private slots:
	void onBrowseImagePostClicked();
	void onSaveImagePostClicked();
private:
	QLineEdit* imagePostPathLineEdit;
	QPushButton* browseImagePostPathButton;
	QPushButton* saveImagePostButton;
};

#endif // SAVEIMAGESWIDGET_H
