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
#include "src/calcMd5.h"
#include "src/quickSearch.h"
#include "consoleMode.h"

namespace CloneHunter
{

/*!
\brief searchQuick
\param [out] filesInfo список одинаковых файлов (см. полное описание)

Быстрый поиск по совпадению имён и размеров файлов.
Файлы, имена и размеры которых совпадают считаются одинаковыми,
независимо от их содержимого.
*/
static void searchQuick(FilesInfo& filesInfo);
/*!
\brief searchQuick
\param [out] filesInfo список одинаковых файлов (см. полное описание)

Поиск по содержимому файлов. Долгий.
Файлы с одинаковым содержимым считаются одинаковыми даже
если их имена не совпадают.
*/
static void searchDeep(FilesInfo& filesInfo, const PROGRAMPARAMS& params);

static unsigned printQuickDupFiles(const FilesInfo& filesInfo, const bool empty);
unsigned printDupFiles(const FilesInfo& filesInfo, const bool quickMode = false);
static void printOtherFiles(const FilesInfo& filesInfo, const bool quickMode);
static void printEmptyFiles(const FilesInfo& filesInfo);

int startConsoleMode(const PROGRAMPARAMS& params)
{
	time_t tStart = time(0);

	consoleOut(QObject::tr("Read files"));

	FilesInfo filesInfo;
	getFilesInfo(params, filesInfo);

	int totalFilesCount = filesInfo.count();

	consoleOut(QString(QObject::tr("Total files: %1")).arg(totalFilesCount));

	if (!filesInfo.empty())
	{
		if (params.empty && !params.quick)
		{
			sortFilesInfoByPath(filesInfo);
			printEmptyFiles(filesInfo);
		}
		else if (params.quick)
		{
			searchQuick(filesInfo);

			sortFilesInfoByNameSize(filesInfo);

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
				sortFilesInfoBySize(filesInfo);
				printOtherFiles(filesInfo, false);
			}
		}
	}

	consoleOut(QString(QObject::tr("Time: %1")).arg(time(nullptr) - tStart));
	return 0;
}

void consoleOut(const QString& text, const QString lang)
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

void searchQuick(FilesInfo& filesInfo)
{
	consoleOut(QObject::tr("Sort by name and size"));
	sortFilesInfoByNameSize(filesInfo);

	consoleOut(QObject::tr("Filter by name and size"));
	removeUniqueNamesSizes(filesInfo);

	consoleOut(QString(QObject::tr("Files count: %1")).arg(filesInfo.size()));
}

void searchDeep(FilesInfo& filesInfo, const PROGRAMPARAMS& params)
{
	consoleOut(QObject::tr("Sort by size"));
	sortFilesInfoBySize(filesInfo);

	consoleOut(QObject::tr("Filter by size"));
	removeUniqueSizes(filesInfo);

	consoleOut(QString(QObject::tr("Files count: %1")).arg(filesInfo.size()));

	// For sequental file access.
	sortFilesInfoByPath(filesInfo);

	consoleOut(QObject::tr("Calc MD5"));
	calcFilesMd5(filesInfo, params);

	consoleOut(QObject::tr("Sort by MD5"));
	sortFilesInfoByMd5(filesInfo);

	consoleOut(QObject::tr("Filter by MD5"));
	removeUniqueMd5(filesInfo);

	consoleOut(QString(QObject::tr("Files count: %1")).arg(filesInfo.size()));

	if (params.sort)
	{
		sortFilesInfoByPath(filesInfo);
	}
}

void printEmptyFiles(const FilesInfo& filesInfo)
{
	consoleOut(QObject::tr("Empty files:"));

	int emptyCount(0);

	for (FilesInfo::const_iterator it = filesInfo.begin(); it != filesInfo.end(); ++it)
	{
		if (it->size == 0)
		{
			emptyCount++;
			consoleOut(QString("%1 %2").arg(it->path + "/" + it->name).arg(it->size));
		}
	}
}

unsigned printQuickDupFiles(const FilesInfo& filesInfo, const bool empty)
{
	unsigned notEmptyCount(0);

	for (FilesInfo::const_iterator it = filesInfo.begin(); it != filesInfo.end(); ++it)
	{
		if (it->size != 0 || empty)
		{
			notEmptyCount++;
			consoleOut(QString("%2 %3").arg(it->path + "/" + it->name).arg(it->size));
		}
	}

	return notEmptyCount;
}

unsigned printDupFiles(const FilesInfo& filesInfo, const bool quickMode)
{
	unsigned notEmptyCount(0);

	for (FilesInfo::const_iterator it = filesInfo.begin(); it != filesInfo.end(); ++it)
	{
		if (!it->md5.isEmpty())
		{
			notEmptyCount++;
			consoleOut(QString("%1 %2 %3").arg(QString(it->md5.toHex())).arg(it->path + "/" + it->name).arg(it->size));
		}
		else if (quickMode && it->size != 0)
		{
			notEmptyCount++;
			consoleOut(QString("%2 %3").arg(it->path + "/" + it->name).arg(it->size));
		}
	}

	return notEmptyCount;
}

void printOtherFiles(const FilesInfo& filesInfo, const bool quickMode)
{
	for (FilesInfo::const_iterator it = filesInfo.begin(); it != filesInfo.end(); ++it)
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
