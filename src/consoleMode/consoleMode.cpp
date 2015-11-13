/*
Copyright © 2015 Alexey Kudrin. All rights reserved.
Licensed under the Apache License, Version 2.0
*/

#include <QDebug>
#include <QString>
#include <time.h>
#include "src/getFiles.h"
#include "src/crc16.h"
#include "src/calcMd5.h"
#include "consoleMode.h"

namespace CloneHunter
{

int startConsoleMode(const CloneHunter::PROGRAMPARAMS& params)
{
	time_t tStart = time(0);

	qWarning() << "READ FILES";

	CloneHunter::FilesInfo filesInfo;
	CloneHunter::getFilesInfo(params, filesInfo);

	int totalFilesCount = filesInfo.size();

	qWarning() << "TOTAL FILES: " << totalFilesCount;

	if (filesInfo.size() != 0)
	{
		qWarning() << "SORT BY SIZE";
		CloneHunter::sortFilesInfoBySize(filesInfo);

		qWarning() << "FILTER BY SIZE";
		CloneHunter::removeUniqueSizes(filesInfo);

		qWarning() << "FILES COUNT: " << filesInfo.size();

		if (filesInfo.size() != 0)
		{

			//	qWarning() << "CALC CRC16";
			//	CloneHunter::calcFilesCrc16(filesInfo);
			//	qWarning() << "SORT BY CRC16";
			//	CloneHunter::sortFilesInfoByCrc16(filesInfo);
			//	qWarning() << "FILTER BY CRC16";
			//	CloneHunter::removeUniqueCrc16(filesInfo);
			//	qWarning() << "FILES COUNT: " << filesInfo.size();

			qWarning() << "CALC MD5";
			CloneHunter::calcFilesMd5(filesInfo, params);

			qWarning() << "SORT BY MD5";
			CloneHunter::sortFilesInfoByMd5(filesInfo);

			qWarning() << "FILTER BY MD5";
			CloneHunter::removeUniqueMd5(filesInfo);

			qWarning() << "FILES COUNT: " << filesInfo.size();

			if (params.sort)
			{
				CloneHunter::sortFilesInfoByPath(filesInfo);
			}

			qWarning() << "FILES (WITHOUT EMPTY):";
		}
	}

	int notEmptyCount(0);

	for (int i = 0; i < filesInfo.count(); i++)
	{
		// if (filesInfo[i].size >= params.min && (filesInfo[i].size <= params.max))
		if (!filesInfo[i].md5.isEmpty())
		{
			notEmptyCount++;
			qWarning() << filesInfo[i].md5.toLocal8Bit().data() << filesInfo[i].name.toLocal8Bit().data() << filesInfo[i].size;
		}
	}

	qWarning() << "TOTAL NOT EMPTY DUP FILES: " << notEmptyCount << "TOTAL DUP FILES: " << filesInfo.size() << "TOTAL FILES: " << totalFilesCount;

	if (params.other)
	{
		qWarning() << "OTHER FILES WITH EQUAL SIZES:";

		CloneHunter::sortFilesInfoBySize(filesInfo);

		for (int i = 0; i < filesInfo.count(); i++)
		{
			if (filesInfo[i].md5.isEmpty())
			{
				notEmptyCount++;
				qWarning() << filesInfo[i].name.toLocal8Bit().data() << filesInfo[i].size;
			}
		}
	}

	qWarning() << "Time: " << (time(0) - tStart);
	return 0;
}

}
