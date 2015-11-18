/*
Copyright © 2015 Alexey Kudrin. All rights reserved.
Licensed under the Apache License, Version 2.0
*/

#include <QApplication>
#include <QTranslator>
#include <QStringList>
#include "src/programParams.h"
#include "src/consoleMode/consoleMode.h"
#include "src/guiMode/MainWindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QStringList arguments = app.arguments();

	CloneHunter::PROGRAMPARAMS params;

	if (0 != CloneHunter::parseParams(params, arguments))
	{
		return 1;
	}

	QTranslator translator;

	if (params.lang == "ru")
	{
		translator.load(":/translations/clonehunter_ru.qm");
		app.installTranslator(&translator);
	}

	if (params.console)
	{
		return CloneHunter::startConsoleMode(params);
	}
	else
	{
		MainWindow w;
		w.show();
		return app.exec();
	}

	return 0;
}
