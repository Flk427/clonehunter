/*
Copyright © 2015 Alexey Kudrin. All rights reserved.
Licensed under the Apache License, Version 2.0
*/

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

static bool fileFullNameLessThan( const FILEINFO & e1, const FILEINFO & e2 )
{
	if ((e1.path + e1.name).toUpper() < (e2.path + e2.name).toUpper())
	{
		return true;
	}
	else
	{
		return false;
	}
}

static FilesInfo readDir(const QString& path)
{
	FilesInfo filesInfo;
	FILEINFO file;

	QDir dir;
	dir.setPath(path);

	QFileInfoList entries = dir.entryInfoList(QDir::AllDirs | QDir::Files | QDir::NoSymLinks | QDir::Hidden | QDir::NoDotAndDotDot); // exclude "." and ".."

	for (int i = 0; i < entries.count(); i++)
	{
		QFileInfo fileInfo = entries[i];

		if (fileInfo.isDir())
		{
			if (path.endsWith('/') || path.endsWith('\\'))
			{
				filesInfo.append(readDir(path + fileInfo.fileName()/*, min, max*/));
			}
			else
			{
				filesInfo.append(readDir(path + QDir::separator() + fileInfo.fileName()/*, min, max*/));
			}
		}
		else
		{
			file.size = fileInfo.size();
			file.path = fileInfo.absolutePath();
			file.name =  fileInfo.fileName();
			file.lastModified = fileInfo.lastModified();
			filesInfo.push_back(file);
		}
	}

	return filesInfo;
}

/*
	TODO: Заменить params.path на QList<QString>. Для поиска сразу в нескольких каталогах.
	При этом следить, чтобы каталоги не были подкаталогами друг друга.
*/
void getFilesInfo(const PROGRAMPARAMS& params, FilesInfo& filesInfo)
{
	for(auto it=params.directories.begin(); it!=params.directories.end(); ++it)
	{
		FilesInfo directoryFilesInfo = readDir(*it /*, params.min, params.max*/);
		filesInfo.append(directoryFilesInfo);
	}

//	QString rootDir = params.directories.first();
//	filesInfo = readDir(rootDir/*, params.min, params.max*/);
}

void sortFilesInfoBySize(FilesInfo& filesInfo)
{
	std::sort(filesInfo.begin(), filesInfo.end(), fileSizeGreaterThan);
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
	qSort(filesInfo.begin(), filesInfo.end(), fileFullNameLessThan);
}

}
