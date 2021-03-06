/*
Copyright © 2015 Alexey Kudrin. All rights reserved.
Licensed under the Apache License, Version 2.0
*/

#ifndef CALCMD5_H
#define CALCMD5_H

#include "programParams.h"
#include "types.h"

namespace CloneHunter
{

qint64 getFileSizes(const FilesInfo& filesInfo, const PROGRAMPARAMS& params);
void calcFilesMd5(FilesInfo& filesInfo, const PROGRAMPARAMS& params);
void removeUniqueMd5(FilesInfo& filesInfo);
void sortFilesInfoByMd5(FilesInfo& filesInfo);

}

#endif // CALCMD5_H
