#ifndef FILESDECISIONMODEL_H
#define FILESDECISIONMODEL_H

#include <QAbstractItemModel>
#include "../../../types.h"
#include "FilesDecisionFileInfo.h"

class FilesDecisionModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	FilesDecisionModel();

	void setFilesInfo(const CloneHunter::FilesInfo& filesInfo);

	// QAbstractItemModel interface
public:
	virtual QModelIndex index(int row, int column, const QModelIndex& parent) const;
//	virtual QModelIndex parent(const QModelIndex& child) const;
	virtual int rowCount(const QModelIndex& parent) const;
	virtual int columnCount(const QModelIndex& parent) const;
//	virtual QVariant data(const QModelIndex& index, int role) const;
//	virtual bool setData(const QModelIndex& index, const QVariant& value, int role);
//	virtual Qt::ItemFlags flags(const QModelIndex& index) const;

private:
	FilesDecisionFiles m_filesDecisionFiles;

};

#endif // FILESDECISIONMODEL_H
