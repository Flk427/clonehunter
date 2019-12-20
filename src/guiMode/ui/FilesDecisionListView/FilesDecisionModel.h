#ifndef FILESDECISIONMODEL_H
#define FILESDECISIONMODEL_H

#include <QAbstractItemModel>
#include "../../../types.h"
#include "FilesDecisionFileInfo.h"

/*!
\brief The FilesDecisionModel class

Если нам нужна модель с древовидной структурой, мы используем QAbstractItemModel. У этой модели надо будет дополнительно определить такие функции:
	parent() — возвращает индекс родителя элемента;
	index() — возвращает индекс элемента.
*/
class FilesDecisionModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	FilesDecisionModel();
	virtual ~FilesDecisionModel();

	void setFilesInfo(const CloneHunter::DupFiles& dupFiles);

	// QAbstractItemModel interface
public:
	virtual QModelIndex index(int row, int column, const QModelIndex& parent) const;
	virtual QModelIndex parent(const QModelIndex& child) const;
	virtual int rowCount(const QModelIndex& parent) const;
	virtual int columnCount(const QModelIndex& parent) const;
	virtual QVariant data(const QModelIndex& index, int role) const;
//	virtual bool setData(const QModelIndex& index, const QVariant& value, int role);
	virtual Qt::ItemFlags flags(const QModelIndex& index) const;

private:
	//FilesDecisionFiles m_filesDecisionFiles;
	CloneHunter::DupFiles m_dupFiles;


	// QAbstractItemModel interface
public:
//	virtual QHash<int, QByteArray> roleNames() const;
};

#endif // FILESDECISIONMODEL_H
