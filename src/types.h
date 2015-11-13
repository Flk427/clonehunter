/*
Copyright © 2015 Alexey Kudrin. All rights reserved.
Licensed under the Apache License, Version 2.0
*/

#ifndef TYPES
#define TYPES

#include <QList>
#include <QString>
#include <QDateTime>

namespace CloneHunter
{

struct FILEINFO
{
	QString name;
	qint64 size;
	QDateTime lastModified;
	unsigned crc16;
	QString md5;

	FILEINFO()
	{
		name = "";
		size = 0;
		crc16 = 0;
		md5 = "";
	}
};

typedef QList<FILEINFO> FilesInfo;

}

#endif // TYPES

