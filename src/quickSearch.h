/*
Copyright © 2015 Alexey Kudrin. All rights reserved.
Licensed under the Apache License, Version 2.0
*/

#ifndef QUICKSEARCH_H
#define QUICKSEARCH_H

#include "types.h"

namespace CloneHunter
{
	void sortFilesInfoByNameSize(FilesInfo& filesInfo);
	void removeUniqueNamesSizes(FilesInfo& filesInfo);
}

#endif // QUICKSEARCH_H
