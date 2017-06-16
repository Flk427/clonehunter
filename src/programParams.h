/*
Copyright © 2015 Alexey Kudrin. All rights reserved.
Licensed under the Apache License, Version 2.0
*/

#ifndef PROGRAMPARAMS_H
#define PROGRAMPARAMS_H

#include <QString>
#include <QStringList>

namespace CloneHunter
{

struct PROGRAMPARAMS
{
	QString path;
	int min;
	int max;
	int sort;
	bool console;
	bool other;
	bool quick;
	QString lang;
	bool empty;

	PROGRAMPARAMS()
	{
		path = ".";
		min = 3;
		max = 0;
		sort = false;
		console = false;
		other = false;
		quick = false;
		lang = "en";
		empty = false;
	}
};

int parseParams(PROGRAMPARAMS& params, QStringList arguments);

}

#endif // PROGRAMPARAMS_H
