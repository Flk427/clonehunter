#ifndef QUICKSEARCH_H
#define QUICKSEARCH_H

#include "types.h"

namespace CloneHunter
{
	void sortFilesInfoByNameSize(FilesInfo& filesInfo);
	void removeUniqueNamesSizes(FilesInfo& filesInfo);
}

#endif // QUICKSEARCH_H
