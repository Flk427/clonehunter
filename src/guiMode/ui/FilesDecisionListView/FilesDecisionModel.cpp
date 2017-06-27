#include "FilesDecisionModel.h"

FilesDecisionModel::FilesDecisionModel(TreeRootItem* root) :
	m_rootItem(root)
{

}

FilesDecisionModel::~FilesDecisionModel()
{
	if (m_rootItem) delete m_rootItem;
}

//void FilesDecisionModel::setFilesInfo(const FilesDecisionFiles& filesDecisionFiles)
//{
//	m_filesDecisionFiles = filesDecisionFiles;
//}

void FilesDecisionModel::setFilesInfo(TreeRootItem* rootItem)
{
	m_rootItem = rootItem;
}


QModelIndex FilesDecisionModel::index(int row, int column, const QModelIndex& parent) const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	if (!parent.isValid())
	{
		if (row < m_rootItem->dataCount())
			return createIndex(row, column, m_rootItem);
		else
			return QModelIndex();

//		TreeInnerItem *childItem = parentItem->child(row);
//		if (childItem)
//			return createIndex(row, column, childItem);
//		else
//			return QModelIndex();
	}
	else
	{
		TreeInnerItem *childItem = m_rootItem->child(row);
		if (childItem)
			return createIndex(row, column, childItem);
		else
			return QModelIndex();

//		TreeInnerItem* parentItem = static_cast<TreeItem*>(parent.internalPointer());

//		TreeItem *childItem = parentItem->child(row);
//		if (childItem)
//			return createIndex(row, column, childItem);
//		else
//			return QModelIndex();
	}


//	if (!hasIndex(row, column, parent))
//		return QModelIndex();

//	if (!parent.isValid())
//	{
//		return createIndex(row, column, (void*) &m_filesDecisionFiles);
//	}
//	else
//	{
////		FilesDecisionFileCopiesList* p = (FilesDecisionFileCopiesList*) parent.internalPointer();
//		return createIndex(row, column, (void*) &m_filesDecisionFiles.at(row));
//	}

//	if (!parent.parent().isValid())
//	{
//		int pRow = parent.row();

//		if (pRow != -1 && row < m_filesDecisionFiles.at(pRow).size())
//		{
//			return createIndex(row, column, nullptr);
//		}
//	}

	return QModelIndex();
}

QModelIndex FilesDecisionModel::parent(const QModelIndex& child) const
{
	if (!child.isValid())
			return QModelIndex();

	if (child.internalPointer() == m_rootItem)
		return QModelIndex();

	TreeInnerItem *childItem = static_cast<TreeInnerItem*>(child.internalPointer());
	TreeRootItem *parentItem = dynamic_cast<TreeRootItem*>(childItem->parentItem());

//	if (parentItem == m_rootItem)
//		return QModelIndex();

	return createIndex(parentItem->row(), 0, parentItem);

//	if (!child.isValid())
//		return QModelIndex();

//	if (child.internalPointer() != (void*) &m_filesDecisionFiles)
//	{
//		return QModelIndex();
//	}
//	else
//	{
//		return createIndex(child.row(), 0, (void*) &m_filesDecisionFiles);
//	}

//	FilesDecisionFileInfo* fi = qobject_cast<FilesDecisionFileInfo*>(child.internalPointer());

//	if (parentItem == rootItem)
//		   return QModelIndex();

	return QModelIndex();
}

int FilesDecisionModel::rowCount(const QModelIndex& parent) const
{
	TreeInnerItem *parentItem;
		if (parent.column() > 0)
			return 0;

		if (!parent.isValid())
		{
			return m_rootItem->dataCount();
		}
		else
		{
			TreeInnerItem* parentItem = static_cast<TreeInnerItem*>(parent.internalPointer());
			return parentItem->dataCount();
		}


//	int count = 0;

//	if (!parent.isValid())
//	{
//		count = m_filesDecisionFiles.size();
//	}
//	else
//	{
//		count = 2;

////		if (!parent.parent().isValid() && m_filesDecisionFiles.count() < parent.row())
////		{
////			count = m_filesDecisionFiles.at(parent.row()).count();
////		}
//	}

//	return count;
}

int FilesDecisionModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return 1;
}

QVariant FilesDecisionModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole)
		return QVariant();

	TreeInnerItem *item = static_cast<TreeInnerItem*>(index.internalPointer());

	return item->data(index.column());

//	if (!index.isValid())
//	{
//		return QVariant();
//	}

//	if (index.internalPointer() == (void*) &m_filesDecisionFiles)
//	{
//		if (index.row() >= m_filesDecisionFiles.size())
//		{
//			return QVariant();
//		}
//		else
//		{
//			if (role == Qt::DisplayRole)
//			{
//				return m_filesDecisionFiles.at(index.row()).at(0).name;
//			}
//		}
//	}
//	else
//	{
//		FilesDecisionFileCopiesList* p = (FilesDecisionFileCopiesList*) index.internalPointer();

//		if (role == Qt::DisplayRole)
//		{
////			return p->at(index.row()).name;
//		}
//	}

//	if (!index.parent().parent().isValid())
//	{
//		if (index.row() >= m_filesDecisionFiles.at(index.row()).size())
//		{
//			return QVariant();
//		}
//		else
//		{
//			if (role == Qt::DisplayRole)
//			{
//				return m_filesDecisionFiles.at(index.parent().row()).at(index.row()).name;
//			}
//		}
//	}

//	return QVariant();
}

//bool FilesDecisionModel::setData(const QModelIndex& index, const QVariant& value, int role)
//{
//}

Qt::ItemFlags FilesDecisionModel::flags(const QModelIndex& index) const
{
	Q_UNUSED(index);
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}


//QHash<int, QByteArray> FilesDecisionModel::roleNames() const
//{
//}
