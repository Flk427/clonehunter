/*
Copyright © 2015 Alexey Kudrin. All rights reserved.
Licensed under the Apache License, Version 2.0
*/

#include <QApplication>
#include <QStringList>
#include "src/programParams.h"
#include "src/consoleMode/consoleMode.h"
#include "src/guiMode/MainWindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QStringList arguments = a.arguments();

	CloneHunter::PROGRAMPARAMS params;

	if (0 != CloneHunter::parseParams(params, arguments))
	{
		return 1;
	}

	if (params.console)
	{
		return CloneHunter::startConsoleMode(params);
	}
	else
	{
		MainWindow w;
		w.show();
		return a.exec();
	}

	return 0;
}
