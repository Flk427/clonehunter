#include <QString>
#include "quickSearch.h"

namespace CloneHunter
{

static QString getNameSize(const FILEINFO& fileInfo)
{
	return QString("%1/%2").arg(fileInfo.name).arg(fileInfo.size);
}

static bool fileNameSizeLessThan(const FILEINFO & e1, const FILEINFO & e2 )
{
	// "/" - deprecated symbol for file name. Using it as separator.
	if (getNameSize(e1) < getNameSize(e2))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void sortFilesInfoByNameSize(FilesInfo& filesInfo)
{
	qSort(filesInfo.begin(), filesInfo.end(), fileNameSizeLessThan);
}

void removeUniqueNamesSizes(FilesInfo& filesInfo)
{
//	1
//	1
//	2
//	2 <- previous
//	3 <- work
//	4 <- current
//	4

	QString previousNameSize;
	FilesInfo::iterator work = filesInfo.begin();

	while (work != filesInfo.end())
	{
		FilesInfo::iterator next = work;
		next++;

		if (next == filesInfo.end())
		{
			if (getNameSize(*work) != previousNameSize)
			{
				filesInfo.erase(work);
			}

			break;
		}

		if (getNameSize(*work) != previousNameSize && getNameSize(*work) != getNameSize(*next))
		{
			work = filesInfo.erase(work); // erase increments its iterator
		}
		else
		{
			// skip
			previousNameSize = getNameSize(*work);
			++work;
		}
	}
}

}
