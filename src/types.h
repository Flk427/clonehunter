/*
Author 2015 Alexey Kudrin. All rights reserved.
Licensed under the Apache License, Version 2.0
*/

#ifndef TYPES
#define TYPES

#include <QList>
#include <QVector>
#include <QString>
#include <QDateTime>
#include <QHash>

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

struct DUPFILEINFO
{
	QString path;
	QString name;
	QDateTime lastModified;
};

struct DUPFILESINFO
{
	//! Индекс родителя. Необходим для построения модели.
	int parentIndex;
	qint64 size;
	QByteArray md5;
	QList<DUPFILEINFO> files;
};

//! Модель для QTreeView.
typedef QVector<DUPFILESINFO> DupFiles;

}

#endif // TYPES
