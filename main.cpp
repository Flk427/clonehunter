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
#include "src/guiMode/TestWindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QStringList arguments = app.arguments();

	CloneHunter::PROGRAMPARAMS params;

	if (0 != CloneHunter::parseParams(params, arguments) && params.console)
	{
		return 0;
	}

	QTranslator translator;

	if (params.lang == "ru")
	{
		translator.load(":/i18n/clonehunter_ru.qm");
		app.installTranslator(&translator);
	}

	if (params.console)
	{
		CloneHunter::consoleOut(QObject::tr("Path: ") + params.path);
		CloneHunter::consoleOut(QString(QObject::tr("Min file size: %1")).arg(params.min));
		CloneHunter::consoleOut(QString(QObject::tr("Max file size: %1")).arg(params.max));

		return CloneHunter::startConsoleMode(params);
	}
	else
	{
		TestWindow t;
		t.show();

		MainWindow w;
		w.show();

		return app.exec();
	}

	return 0;
}
