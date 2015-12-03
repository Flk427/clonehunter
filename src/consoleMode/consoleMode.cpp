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

static unsigned printQuickDupFiles(const CloneHunter::FilesInfo& filesInfo, const bool empty);
static unsigned printDupFiles(const CloneHunter::FilesInfo& filesInfo, const bool quickMode = false);
static void printOtherFiles(const CloneHunter::FilesInfo& filesInfo, const bool quickMode);
static void printEmptyFiles(const CloneHunter::FilesInfo& filesInfo);

int startConsoleMode(const CloneHunter::PROGRAMPARAMS& params)
{
	time_t tStart = time(0);

	consoleOut(QObject::tr("Read files"));

	CloneHunter::FilesInfo filesInfo;
	CloneHunter::getFilesInfo(params, filesInfo);

	int totalFilesCount = filesInfo.count();

	consoleOut(QString(QObject::tr("Total files: %1")).arg(totalFilesCount));

	if (!filesInfo.empty())
	{
		if (params.empty && !params.quick)
		{
			CloneHunter::sortFilesInfoByPath(filesInfo);
			printEmptyFiles(filesInfo);
		}
		else if (params.quick)
		{
			searchQuick(filesInfo);

			CloneHunter::sortFilesInfoByNameSize(filesInfo);

			consoleOut(QObject::tr("Files (without empty):"));
			unsigned notEmptyCount = printQuickDupFiles(filesInfo, params.empty);

			consoleOut(QString(QObject::tr("Total not empty dup files: %1 Total dup files: %2 Total files: %3"))
					   .arg(notEmptyCount)
					   .arg(filesInfo.size())
					   .arg(totalFilesCount));

			if (params.other)
			{
				consoleOut(QObject::tr("Other dup files:"));
				printOtherFiles(filesInfo, true);
			}
		}
		else
		{
			searchDeep(filesInfo, params);
			consoleOut(QObject::tr("Files (without empty):"));
			unsigned notEmptyCount = printDupFiles(filesInfo);

			consoleOut(QString(QObject::tr("Total not empty dup files: %1 Total dup files: %2 Total files: %3"))
					   .arg(notEmptyCount)
					   .arg(filesInfo.size())
					   .arg(totalFilesCount));

			if (params.other)
			{
				consoleOut(QObject::tr("Other files with equal sizes:"));
				CloneHunter::sortFilesInfoBySize(filesInfo);
				printOtherFiles(filesInfo, false);
			}
		}
	}

	consoleOut(QString(QObject::tr("Time: %1")).arg(time(0) - tStart));
	return 0;
}

void consoleOut(const QString& text, QString& lang)
{
	// http://stackoverflow.com/questions/4766301/windows-console-and-qt-unicode-text

	QTextStream out(stdout);

#if defined(Q_OS_WIN)
	if (lang == "ru")
	{
		out.setCodec("cp866"); // for windows console out (hardcoded codec example).
	}

	// Cannot redirect output to file by "prog.exe > filename":
	// WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), text.utf16(),  text.size(), NULL, NULL);

	// CP1251 output: std::cout << text.toLocal8Bit().data() << std::endl;
#endif

	out << text;
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

void printEmptyFiles(const CloneHunter::FilesInfo& filesInfo)
{
	consoleOut(QObject::tr("Empty files:"));

	int emptyCount(0);

	for (CloneHunter::FilesInfo::const_iterator it = filesInfo.begin(); it != filesInfo.end(); ++it)
	{
		if (it->size == 0)
		{
			emptyCount++;
			consoleOut(QString("%1 %2").arg(it->path + "/" + it->name).arg(it->size));
		}
	}
}

unsigned printQuickDupFiles(const CloneHunter::FilesInfo& filesInfo, const bool empty)
{
	unsigned notEmptyCount(0);

	for (CloneHunter::FilesInfo::const_iterator it = filesInfo.begin(); it != filesInfo.end(); ++it)
	{
		if (it->size != 0 || empty)
		{
			notEmptyCount++;
			consoleOut(QString("%2 %3").arg(it->path + "/" + it->name).arg(it->size));
		}
	}

	return notEmptyCount;
}

unsigned printDupFiles(const CloneHunter::FilesInfo& filesInfo, const bool quickMode)
{
	unsigned notEmptyCount(0);

	for (CloneHunter::FilesInfo::const_iterator it = filesInfo.begin(); it != filesInfo.end(); ++it)
	{
		if (!it->md5.isEmpty())
		{
			notEmptyCount++;
			consoleOut(QString("%1 %2 %3").arg(it->md5).arg(it->path + "/" + it->name).arg(it->size));
		}
		else if (quickMode && it->size != 0)
		{
			notEmptyCount++;
			consoleOut(QString("%2 %3").arg(it->path + "/" + it->name).arg(it->size));
		}
	}

	return notEmptyCount;
}

void printOtherFiles(const CloneHunter::FilesInfo& filesInfo, const bool quickMode)
{
	for (CloneHunter::FilesInfo::const_iterator it = filesInfo.begin(); it != filesInfo.end(); ++it)
	{
		if (quickMode)
		{
			if (it->size == 0)
			{
				consoleOut(QString("%1 %2").arg(it->path + "/" + it->name).arg(it->size));
			}
		}
		else
		{
			if (it->md5.isEmpty())
			{
				consoleOut(QString("%1 %2").arg(it->path + "/" + it->name).arg(it->size));
			}
		}
	}
}

}
