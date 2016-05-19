#include <iostream>
#include "noiseremoverapplication.h"
#include "mainwindow.h"
#include "cvimagewidget.h"


int main(int argc, char* argv[])
{
	NoiseRemoverApplication app(argc, argv);
	return app.exec();
}
