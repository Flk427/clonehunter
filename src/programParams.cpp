/*
Copyright © 2015 Alexey Kudrin. All rights reserved.
Licensed under the Apache License, Version 2.0
*/

#include <QObject>
#include <QString>
#include <QTextDecoder>
#include <QTextCodec>
#include <QDir>
#include <limits>
#include "programParams.h"
#include "consoleMode/consoleMode.h"

namespace CloneHunter
{

int parseParams(PROGRAMPARAMS& params, QStringList arguments)
{
	for (QStringList::const_iterator it = ++arguments.begin(); it != arguments.end(); ++it)
	{
		QString param = *it;

		if (param == "--console")
		{
			params.console = true;
		}
		else if (param == "--gui")
		{
			params.console = false;
		}
		else if (param.startsWith("--lang=", Qt::CaseInsensitive))
		{
			params.lang = param.right(param.size() - 7);
		}
		else if (param.startsWith("--dir=", Qt::CaseInsensitive))
		{
			params.path = param.right(param.size() - 6);

			if (!params.path.endsWith('\\') && !params.path.endsWith('/'))
			{
				params.path.append(QDir::separator());
			}
		}
		else if (param.startsWith("--min=", Qt::CaseInsensitive))
		{
			params.min = param.right(param.size() - 6).toUInt();
		}
		else if (param.startsWith("--max=", Qt::CaseInsensitive))
		{
			params.max = param.right(param.size() - 6).toUInt();
		}
		else if (param == "--sort")
		{
			params.sort = true;
		}
		else if (param == "--other")
		{
			params.other = true;
		}
		else if (param == "--quick")
		{
			params.quick = true;
			params.empty = false;
		}
		else if (param == "--empty")
		{
			params.empty = true;
			params.quick = false;
		}
		else if (param == "--help" || param == "/?" || param == "?")
		{
			CloneHunter::consoleOut(QObject::tr("Usage: CloneHunter.exe [--console] [--dir=<path to dir>] [--min=<size>] [--max=<size>] [--sort] [--other] [--quick|--empty] [--lang={en|ru}]"));
			CloneHunter::consoleOut(QObject::tr("  --console: Run in console mode. Default: console (windowed in future) mode"));
			CloneHunter::consoleOut(QString("  --dir: Directory to scan (recursively). Default dir: %1").arg(params.path));
			CloneHunter::consoleOut(QString("  --min: Mininal file size for content scan. Default: %1").arg(params.min));
			CloneHunter::consoleOut(QString("  --max: Maximal file size for content scan. Default: %1").arg((std::numeric_limits<int>::max)()));
			CloneHunter::consoleOut("  --quick: Quick scan. Compare file names and sizes only. Default: false");
			CloneHunter::consoleOut("  --empty: Show all empty files (include unical names). Default: false");
			CloneHunter::consoleOut("  --other: Show possibly dup files for normal or quick mode. Default: false");
			CloneHunter::consoleOut("  --sort: Sort results by path. Default: sort by hash");
			CloneHunter::consoleOut("  --lang: l18n (en, ru). Default: en");
			params.console = true;
			return 1;
		}
		else {
			CloneHunter::consoleOut(QString(QObject::tr("Error: wrong param: '%1'")).arg(param));
			CloneHunter::consoleOut("Type: 'CloneHunter.exe --help' for info.");
			params.console = true;
			return 2; // params error;
		}
	}

	if (params.max == 0)
	{
		params.max = (std::numeric_limits<int>::max)();
	}

	return 0;
}

}
