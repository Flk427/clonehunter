/*
Copyright © 2015 Alexey Kudrin. All rights reserved.
Licensed under the Apache License, Version 2.0
*/

#include <iostream>
#include "programParams.h"

namespace CloneHunter
{

int parseParams(PROGRAMPARAMS& params, int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "Type: 'CloneHunter.exe --help' for info." << std::endl;
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
			std::cout << "Usage: CloneHunter.exe [--console] [--dir=<path to dir>] [--min=<size>] [--max=<size>] [--sort] [--other]" << std::endl << std::endl;
			std::cout << "  --console: Run in console mode. Default: windowed mode" << std::endl;
			std::cout << "  --dir: Directory to scan (recursively). Default dir: " << params.path.toLocal8Bit().data() << std::endl;
			std::cout << "  --min: Mininal file size to scan. Default: " << params.min << std::endl;
			std::cout << "  --max: Maximal file size to scan. Default: " << std::numeric_limits<int>::max() << std::endl;
			std::cout << "  --sort: Sort results by path. Default: sort by hash" << std::endl;
			std::cout << "  --other: Show possibly dup files. Default: false" << std::endl;
			return 1;
		}
		else {
			std::cout << "Error: wrong param: '" << argv[i] << "'" << std::endl;
			std::cout << "Type: 'CloneHunter.exe --help' for info." << std::endl;
			return 2; // params error;
		}
	}

	if (params.max == 0)
	{
		params.max = std::numeric_limits<int>::max();
	}

	if (params.console == true)
	{
		std::cout << "Path: " << params.path.toLocal8Bit().data() << std::endl;
		std::cout << "Min file size: " << params.min << std::endl;
		std::cout << "Max file size: " << params.max << std::endl;
	}
	else
	{
		std::cout << "Error: no windowed mode yet." << std::endl;
		return 1;
	}

	return 0;
}

}
