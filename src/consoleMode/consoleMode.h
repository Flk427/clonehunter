/*
Copyright © 2015 Alexey Kudrin. All rights reserved.
Licensed under the Apache License, Version 2.0
*/

#ifndef CONSOLE_H
#define CONSOLE_H

#include "../programParams.h"
#include "../types.h"

namespace CloneHunter
{
	int startConsoleMode(const PROGRAMPARAMS& params);
	void consoleOut(const QString& text, const QString lang = QString("ru"));
	unsigned printDupFiles(const FilesInfo& filesInfo, const bool quickMode);
}

#endif // CONSOLE_H
