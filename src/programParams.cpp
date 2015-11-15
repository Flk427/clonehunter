/*
Copyright © 2015 Alexey Kudrin. All rights reserved.
Licensed under the Apache License, Version 2.0
*/

#include <limits>
#include "programParams.h"
#include "consoleMode/consoleMode.h"

namespace CloneHunter
{

int parseParams(PROGRAMPARAMS& params, int argc, char *argv[])
{
	if (argc < 2)
	{
		CloneHunter::consoleOut("Type: 'CloneHunter.exe --help' for info.");
		params.console = false;
		return 1;
	}

	for (int i=1; i < argc; ++i)
	{
		QString param = QString(argv[i]);

		if (param == "--console")
		{
			params.console = true;
		}
		else if (param.startsWith("--dir=", Qt::CaseInsensitive))
		{
			params.path = param.right(param.size() - 6);
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
		else if (param == "--help")
		{
			CloneHunter::consoleOut("Usage: CloneHunter.exe [--console] [--dir=<path to dir>] [--min=<size>] [--max=<size>] [--sort] [--other]");
			CloneHunter::consoleOut("  --console: Run in console mode. Default: windowed mode");
			CloneHunter::consoleOut(QString("  --dir: Directory to scan (recursively). Default dir: %1").arg(params.path));
			CloneHunter::consoleOut(QString("  --min: Mininal file size to scan. Default: %1").arg(params.min));
			CloneHunter::consoleOut(QString("  --max: Maximal file size to scan. Default: %1").arg(std::numeric_limits<int>::max()));
			CloneHunter::consoleOut("  --sort: Sort results by path. Default: sort by hash");
			CloneHunter::consoleOut("  --other: Show possibly dup files. Default: false");
			return 1;
		}
		else {
			CloneHunter::consoleOut(QString("Error: wrong param: '%1'").arg(argv[i]));
			CloneHunter::consoleOut("Type: 'CloneHunter.exe --help' for info.");
			return 2; // params error;
		}
	}

	if (params.max == 0)
	{
		params.max = std::numeric_limits<int>::max();
	}

	if (params.console == true)
	{
		CloneHunter::consoleOut("Path: " + params.path);
		CloneHunter::consoleOut(QString("Min file size: %1").arg(params.min));
		CloneHunter::consoleOut(QString("Max file size: %1").arg(params.max));
	}
	else
	{
		CloneHunter::consoleOut("Error: no windowed mode yet.");
		return 1;
	}

	return 0;
}

}
