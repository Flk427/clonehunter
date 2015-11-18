/*
Copyright © 2015 Alexey Kudrin. All rights reserved.
Licensed under the Apache License, Version 2.0
*/

#if defined(__WIN32) || defined(_WIN32)
#include <Windows.h>
#endif

#include <QString>
#include <QTextCodec>
#include <QTextStream>
#include <time.h>
#include "src/getFiles.h"
#include "src/crc16.h"
#include "src/calcMd5.h"
#include "src/quickSearch.h"
#include "consoleMode.h"

namespace CloneHunter
{

static void searchQuick(CloneHunter::FilesInfo& filesInfo);
static void searchDeep(CloneHunter::FilesInfo& filesInfo, const CloneHunter::PROGRAMPARAMS& params);

int startConsoleMode(const CloneHunter::PROGRAMPARAMS& params)
{
	time_t tStart = time(0);

	consoleOut(QObject::tr("Read files"));

	CloneHunter::FilesInfo filesInfo;
	CloneHunter::getFilesInfo(params, filesInfo);

	int totalFilesCount = filesInfo.size();

	consoleOut(QString(QObject::tr("Total files: %1")).arg(totalFilesCount));

	if (filesInfo.size() != 0)
	{
		if (filesInfo.size() != 0)
		{
			if (params.quick)
			{
				searchQuick(filesInfo);
			}
			else
			{
				searchDeep(filesInfo, params);
			}

			consoleOut(QObject::tr("Files (without empty):"));
		}
	}

	int notEmptyCount(0);

	for (int i = 0; i < filesInfo.count(); i++)
	{
		if (!filesInfo[i].md5.isEmpty())
		{
			notEmptyCount++;
			consoleOut(QString("%1 %2 %3").arg(filesInfo[i].md5).arg(filesInfo[i].path + "/" + filesInfo[i].name).arg(filesInfo[i].size));
		}
		else if (params.quick)
		{
			notEmptyCount++;
			consoleOut(QString("%2 %3").arg(filesInfo[i].path + "/" + filesInfo[i].name).arg(filesInfo[i].size));
		}
	}

	consoleOut(QString(QObject::tr("Total not empty dup files: %1 Total dup files: %2 Total files: %3"))
			   .arg(notEmptyCount)
			   .arg(filesInfo.size())
			   .arg(totalFilesCount));

	if (params.other)
	{
		consoleOut(QObject::tr("Other files with equal sizes:"));

		CloneHunter::sortFilesInfoBySize(filesInfo);

		for (int i = 0; i < filesInfo.count(); i++)
		{
			if (filesInfo[i].md5.isEmpty())
			{
				notEmptyCount++;
				consoleOut(QString("%1 %2").arg(filesInfo[i].path + "/" + filesInfo[i].name).arg(filesInfo[i].size));
			}
		}
	}

	consoleOut(QString(QObject::tr("Time: %1")).arg(time(0) - tStart));
	return 0;
}

void consoleOut(const QString& text)
{
	// http://stackoverflow.com/questions/4766301/windows-console-and-qt-unicode-text

	QTextStream out(stdout);

#if defined(__WIN32) || defined(_WIN32)
	// out.setCodec("IBM866"); // for windows console out (hardcoded codec example).
	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), text.utf16(), text.size(), NULL, NULL);
#else
	out << text;
#endif

	out << endl;
}

void searchQuick(CloneHunter::FilesInfo& filesInfo)
{
	consoleOut(QObject::tr("Sort by name and size"));
	CloneHunter::sortFilesInfoByNameSize(filesInfo);

	consoleOut(QObject::tr("Filter by name and size"));
	CloneHunter::removeUniqueNamesSizes(filesInfo);

	consoleOut(QString(QObject::tr("Files count: %1")).arg(filesInfo.size()));
}

void searchDeep(CloneHunter::FilesInfo& filesInfo, const CloneHunter::PROGRAMPARAMS& params)
{
	consoleOut(QObject::tr("Sort by size"));
	CloneHunter::sortFilesInfoBySize(filesInfo);

	consoleOut(QObject::tr("Filter by size"));
	CloneHunter::removeUniqueSizes(filesInfo);

	consoleOut(QString(QObject::tr("Files count: %1")).arg(filesInfo.size()));

	/*
	qWarning() << "CALC CRC16";
	CloneHunter::calcFilesCrc16(filesInfo);
	qWarning() << "SORT BY CRC16";
	CloneHunter::sortFilesInfoByCrc16(filesInfo);
	qWarning() << "FILTER BY CRC16";
	CloneHunter::removeUniqueCrc16(filesInfo);
	qWarning() << "FILES COUNT: " << filesInfo.size();
	*/

	// For sequental file access.
	CloneHunter::sortFilesInfoByPath(filesInfo);

	consoleOut(QObject::tr("Calc MD5"));
	CloneHunter::calcFilesMd5(filesInfo, params);

	consoleOut(QObject::tr("Sort by MD5"));
	CloneHunter::sortFilesInfoByMd5(filesInfo);

	consoleOut(QObject::tr("Filter by MD5"));
	CloneHunter::removeUniqueMd5(filesInfo);

	consoleOut(QString(QObject::tr("Files count: %1")).arg(filesInfo.size()));

	if (params.sort)
	{
		CloneHunter::sortFilesInfoByPath(filesInfo);
	}
}

}
