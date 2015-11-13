/*
Copyright © 2015 Alexey Kudrin. All rights reserved.
Licensed under the Apache License, Version 2.0
*/

#include "src/programParams.h"
#include "src/consoleMode/consoleMode.h"

int main(int argc, char *argv[])
{
	CloneHunter::PROGRAMPARAMS params;

	if (0 != CloneHunter::parseParams(params, argc, argv))
	{
		return 1;
	}

	if (params.console)
	{
		return CloneHunter::startConsoleMode(params);
	}

	return 0;
}
