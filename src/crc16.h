/*
Copyright © 2015 Alexey Kudrin. All rights reserved.
Licensed under the Apache License, Version 2.0
*/

#ifndef CRC16_H
#define CRC16_H

namespace CloneHunter
{

void calcFilesCrc16(FilesInfo& filesInfo);
void removeUniqueCrc16(FilesInfo& filesInfo);
void sortFilesInfoByCrc16(FilesInfo& filesInfo);

}

#endif // CRC16_H
