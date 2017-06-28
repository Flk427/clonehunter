#ifndef FILESDECISIONFILEINFO_H
#define FILESDECISIONFILEINFO_H

#include <QString>
#include <QDateTime>
#include <QByteArray>
#include <QList>
#include <QHash>
#include "../../../types.h"

struct FilesDecisionFileInfo
{
	QString path;
	QString name;
	qint64 size;
	QDateTime lastModified;
	QByteArray hash;
	bool marked;

	FilesDecisionFileInfo() :
		path(""),
		name(""),
		size(0),
		marked(false)
	{
	}

	FilesDecisionFileInfo(const CloneHunter::FILEINFO& fi)
	{
		path = fi.path;
		name = fi.name;
		size = fi.size;
		lastModified = fi.lastModified;
		hash = fi.md5;
		marked = false;
	}
};

typedef QList<FilesDecisionFileInfo> FilesDecisionFileCopiesList;

typedef QList<FilesDecisionFileCopiesList*> FilesDecisionFiles;

#endif // FILESDECISIONFILEINFO_H
