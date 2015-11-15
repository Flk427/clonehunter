/*
Copyright © 2015 Alexey Kudrin. All rights reserved.
Licensed under the Apache License, Version 2.0
*/

#include <QCryptographicHash>
#include <QFile>
#include <QByteArray>
#include "types.h"
#include "calcMd5.h"
#include "consoleMode/consoleMode.h"

namespace CloneHunter
{

static bool fileMd5LessThan( const FILEINFO & e1, const FILEINFO & e2 )
{
	if (e1.md5 < e2.md5)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void calcFilesMd5(FilesInfo& filesInfo, const PROGRAMPARAMS& params)
{
	int i(0);
	int hundreed(1);

	for (FilesInfo::iterator it = filesInfo.begin(); it != filesInfo.end(); ++it)
	{
		if (it->size >= params.min && (it->size <= params.max))
		{
			i++;
			hundreed++;

			if ((it->size > 10000000 && hundreed > 1) || (it->size > 300000 && hundreed > 10) || (it->size > 10000 && hundreed > 50) || (it->size > 2000 && hundreed) > 100 || hundreed > 1000)
			{
				hundreed = 1;
				CloneHunter::consoleOut(QString("%1 %2").arg(i).arg(it->size));
			}

			QFile file;
			file.setFileName(it->name);

			if (file.open(QIODevice::ReadOnly))
			{
				QByteArray content = file.readAll();
				file.close();

				QCryptographicHash hash(QCryptographicHash::Md5);
				hash.reset();
				hash.addData(content);

				QByteArray md5hash = hash.result();
				it->md5 = QString(md5hash.toHex());
			}
		}
	}
}

void removeUniqueMd5(FilesInfo& filesInfo)
{
	//	1
	//	1
	//	2
	//	2 <- previous
	//	3 <- work
	//	4 <- current
	//	4

		QString previousMd5("");
		FilesInfo::iterator work = filesInfo.begin();

		while (work != filesInfo.end())
		{
			FilesInfo::iterator next = work;
			next++;

			if (next == filesInfo.end())
			{
				if (work->md5 != previousMd5)
				{
					filesInfo.erase(work);
				}

				break;
			}

			if (work->md5 != previousMd5 && work->md5 != next->md5)
			{
				work = filesInfo.erase(work); // erase increments its iterator
			}
			else
			{
				// skip
				previousMd5 = work->md5;
				++work;
			}
		}
}


void sortFilesInfoByMd5(FilesInfo& filesInfo)
{
	qSort(filesInfo.begin(), filesInfo.end(), fileMd5LessThan);
}

}
