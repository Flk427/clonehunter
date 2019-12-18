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
	//if (QString(e1.md5array.toHex()) < QString(e2.md5array.toHex()))
	if (e1.md5 < e2.md5)
	{
		return true;
	}
	else
	{
		return false;
	}
}

static qint64 getFileSizes(const FilesInfo& filesInfo, const PROGRAMPARAMS& params)
{
	qint64 total(0);

	for (FilesInfo::const_iterator it = filesInfo.begin(); it != filesInfo.end(); ++it)
	{
		if (it->size >= params.min && (it->size <= params.max))
		{
			total += it->size;
		}
	}

	return total;
}

void calcFilesMd5(FilesInfo& filesInfo, const PROGRAMPARAMS& params)
{
	qint64 totalSize = getFileSizes(filesInfo, params);
	qint64 scannedSize(0);
	unsigned oldCto = 99;
	unsigned i(0);

	CloneHunter::consoleOut(QString(QObject::tr("Total size: %1 Count: %2")).arg(totalSize).arg(filesInfo.size()));

	for (FilesInfo::iterator it = filesInfo.begin(); it != filesInfo.end(); ++it)
	{
		i++;

		if (it->size != 0 && it->size >= params.min && (it->size <= params.max))
		{
			QFile file;
			file.setFileName(it->path + "/" + it->name);

			if (file.open(QIODevice::ReadOnly))
			{
				QByteArray content;
				QCryptographicHash hash(QCryptographicHash::Md5);
				hash.reset();

				do
				{
					content = file.read(8*1024*1024);

					if (content.size() != 0)
					{
						hash.addData(content);

						{ // TODO: вынести отдельно
							scannedSize += content.size();
							unsigned cto = (100.0 * scannedSize / totalSize);

							if (oldCto / 10 != cto / 10)
							{
								oldCto = cto;
								CloneHunter::consoleOut(QString("%1%").arg(cto - cto % 10));
							}
						}
					}
				}
				while (content.size() != 0);

				file.close();
//				QByteArray md5hash = hash.result();
//				it->md5 = QString(md5hash.toHex());
				it->md5 = hash.result();
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

//		QString previousMd5("");
		QByteArray previousMd5;
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
	std::sort(filesInfo.begin(), filesInfo.end(), [&](const FILEINFO& e1, const FILEINFO& e2){return e1.md5 < e2.md5;});
}

}
