#ifndef NOISEREMOVERAPPLICATION_H
#define NOISEREMOVERAPPLICATION_H

#include <QApplication>
#include "mainwindow.h"
#include "noiseremover.h"


class NoiseRemoverApplication : public QApplication
{
	Q_OBJECT
public:
	explicit NoiseRemoverApplication(int & argc, char ** argv);

signals:

public slots:
	void onLoadImageClicked();
	void onMaskChanged();
	void onSaveImageClicked();
private:
	void updateGUIImages();
	void updateNoiseRemoverMask();
	MainWindow* gui;
	NoiseRemover* noiseRemover;
};

#endif // NOISEREMOVERAPPLICATION_H
