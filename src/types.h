/*
Author 2015 Alexey Kudrin. All rights reserved.
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
	QString path;
	QString name;
	qint64 size;
	QDateTime lastModified;
	QByteArray md5;

	FILEINFO()
	{
		path = "";
		name = "";
		size = 0;
	}
};

typedef QList<FILEINFO> FilesInfo;

}

#endif // TYPES

