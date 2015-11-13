/*
Copyright © 2015 Alexey Kudrin. All rights reserved.
Licensed under the Apache License, Version 2.0
*/

#ifndef GETFILES_H
#define GETFILES_H

#include "types.h"
#include "programParams.h"

namespace CloneHunter {
	/*!
	\brief getFilesInfo Return files info for target directory
	\param [in] params
	\param [out] filesInfo
	*/
	void getFilesInfo(const PROGRAMPARAMS& params, FilesInfo& filesInfo);

	/*!
	\brief sortFilesInfoBySize
	\param filesInfo
	*/
	void sortFilesInfoBySize(FilesInfo& filesInfo);

	void sortFilesInfoByPath(FilesInfo& filesInfo);

	/*!
	\brief removeUniqueSizes
	\param filesInfo
	*/
	void removeUniqueSizes(FilesInfo& filesInfo);
}

#endif // GETFILES_H
