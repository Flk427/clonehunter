/*
Copyright © 2015 Alexey Kudrin. All rights reserved.
Licensed under the Apache License, Version 2.0
*/

#include <QFile>
#include <QByteArray>
#include <QDebug>
#include "types.h"
#include "crc16.h"

namespace CloneHunter
{

static bool fileCrc16LessThan( const FILEINFO & e1, const FILEINFO & e2 )
{
	if (e1.crc16 < e2.crc16)
	{
		return true;
	}
	else
	{
		return false;
	}
}

static unsigned int GetCRC16(const unsigned char* bufData, unsigned int sizeData)
{
	static unsigned POLYNOMIAL = 0x08408;
	unsigned int CRC, i;
	unsigned char j;

	CRC = 0;

	for(i=0; i < sizeData; i++)
	{
		CRC ^= bufData[i];

		for(j=0; j < 8; j++)
		{
			if(CRC & 0x0001)
			{
				CRC >>= 1; CRC ^= POLYNOMIAL;
			}
			else
			{
				CRC >>= 1;
			}
		}
	}

	return CRC;
}

void calcFilesCrc16(FilesInfo& filesInfo)
{
	int i(0);
	int hundreed(1);

	for (FilesInfo::iterator it = filesInfo.begin(); it != filesInfo.end(); ++it)
	{
		i++;
		hundreed++;

		if (((it->size > 100000) && (hundreed > 10)) || ((it->size > 50000) && (hundreed > 100)) || (hundreed > 1000))
		{
			hundreed = 1;
			qDebug() << i;
		}

		QFile file;
		file.setFileName(it->path + "/" + it->name);
		if (file.open(QIODevice::ReadOnly))
		{
			QByteArray content = file.readAll();
			file.close();

			it->crc16 = GetCRC16((const unsigned char*) content.data(), content.size());
		}
	}
}

void removeUniqueCrc16(FilesInfo& filesInfo)
{
//	1
//	1
//	2
//	2 <- previous
//	3 <- work
//	4 <- current
//	4

	unsigned previousCRC(std::numeric_limits<unsigned>::max());
	FilesInfo::iterator work = filesInfo.begin();

	while (work != filesInfo.end())
	{
		FilesInfo::iterator next = work;
		next++;

		if (next == filesInfo.end())
		{
			if (work->crc16 != previousCRC)
			{
				filesInfo.erase(work);
			}

			break;
		}

		if (work->crc16 != previousCRC && work->crc16 != next->crc16)
		{
			work = filesInfo.erase(work); // erase increments its iterator
		}
		else
		{
			// skip
			previousCRC = work->crc16;
			++work;
		}
	}
}

void sortFilesInfoByCrc16(FilesInfo& filesInfo)
{
	qSort(filesInfo.begin(), filesInfo.end(), fileCrc16LessThan);
}

}
