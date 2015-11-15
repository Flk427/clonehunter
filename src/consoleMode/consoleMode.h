/*
Copyright © 2015 Alexey Kudrin. All rights reserved.
Licensed under the Apache License, Version 2.0
*/

#ifndef CONSOLE_H
#define CONSOLE_H

#include "../programParams.h"

namespace CloneHunter
{
	int startConsoleMode(const CloneHunter::PROGRAMPARAMS& params);
	void consoleOut(const QString& text);
}

#endif // CONSOLE_H
