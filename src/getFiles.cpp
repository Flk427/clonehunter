/*
Copyright © 2015 Alexey Kudrin. All rights reserved.
Licensed under the Apache License, Version 2.0
*/

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QStringList>
#include "programParams.h"
#include "getFiles.h"

namespace CloneHunter {

static bool fileSizeGreaterThan( const FILEINFO & e1, const FILEINFO & e2 )
{
	if (e1.size > e2.size)
	{
		return true;
	}
	else
	{
		return false;
	}
}

static bool fileNameLessThan( const FILEINFO & e1, const FILEINFO & e2 )
{
	if (e1.name.toUpper() < e2.name.toUpper())
	{
		return true;
	}
	else
	{
		return false;
	}
}

static FilesInfo readDir(const QString& path/*, qint64 min, qint64 max*/)
{
	FilesInfo filesInfo;
	FILEINFO fileSize;

	QDir dir;
	dir.setPath(path);

	QFileInfoList entries = dir.entryInfoList();

	for (int i = 0; i < entries.count(); i++)
	{
		QFileInfo fileInfo = entries[i];

		if (fileInfo.isDir())
		{
			if (fileInfo.fileName() != "." && fileInfo.fileName() != "..")
			{
				if (path.endsWith('/') || path.endsWith('\\'))
				{
					filesInfo.append(readDir(path + fileInfo.fileName()/*, min, max*/));
				}
				else
				{
					filesInfo.append(readDir(path + "/" + fileInfo.fileName()/*, min, max*/));
				}
			}
		}
		else
		{
			fileSize.size = fileInfo.size();

//			if (fileSize.size >= min && (max == 0 || fileSize.size <= max))
//			{
				fileSize.name = fileInfo.absolutePath() + "/" + fileInfo.fileName();
				fileSize.lastModified = fileInfo.lastModified();
				filesInfo.push_back(fileSize);
//			}
		}
	}

	return filesInfo;
}

void getFilesInfo(const PROGRAMPARAMS& params, FilesInfo& filesInfo)
{
	QString rootDir = params.path;

	if (rootDir.endsWith(':'))
	{
		rootDir.append("/");
	}

	filesInfo = readDir(rootDir/*, params.min, params.max*/);
}

void sortFilesInfoBySize(FilesInfo& filesInfo)
{
	qSort(filesInfo.begin(), filesInfo.end(), fileSizeGreaterThan);
}

void removeUniqueSizes(FilesInfo& filesInfo)
{
//	1
//	1
//	2
//	2 <- previous
//	3 <- work
//	4 <- current
//	4

	qint64 previousSize(-1);
	FilesInfo::iterator work = filesInfo.begin();

	while (work != filesInfo.end())
	{
		FilesInfo::iterator next = work;
		next++;

		if (next == filesInfo.end())
		{
			if (work->size != previousSize)
			{
				filesInfo.erase(work);
			}

			break;
		}

		if (work->size != previousSize && work->size != next->size)
		{
			work = filesInfo.erase(work); // erase increments its iterator
		}
		else
		{
			// skip
			previousSize = work->size;
			++work;
		}
	}
}

void sortFilesInfoByPath(FilesInfo& filesInfo)
{
	qSort(filesInfo.begin(), filesInfo.end(), fileNameLessThan);
}

}
