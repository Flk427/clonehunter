#include "FilesDecisionModel.h"

FilesDecisionModel::FilesDecisionModel(TreeRootItem* root) :
	m_rootItem(root)
{

}

FilesDecisionModel::~FilesDecisionModel()
{
	if (m_rootItem) delete m_rootItem;
}

void FilesDecisionModel::setFilesInfo(TreeRootItem* rootItem)
{
	m_rootItem = rootItem;
}

QModelIndex FilesDecisionModel::index(int row, int column, const QModelIndex& parent) const
{
	if (!hasIndex(row, column, parent))
	{
		return QModelIndex();
	}

	if (!parent.isValid())
	{
		return createIndex(row, column, nullptr);
	}
	else
	{
		if (parent.internalPointer() == nullptr)
		{
			TreeInnerItem *childItem = m_rootItem->child(parent.row());

			if (childItem)
			{
				return createIndex(row, column, childItem);
			}
		}
	}

	return QModelIndex();
}

QModelIndex FilesDecisionModel::parent(const QModelIndex& child) const
{
	if (!child.isValid())
	{
		return QModelIndex();
	}

	if (child.internalPointer() == nullptr)
	{
		return QModelIndex();
	}

	TreeInnerItem *childItem = static_cast<TreeInnerItem*>(child.internalPointer());
	return createIndex(childItem->row(), 0, nullptr);
}

int FilesDecisionModel::rowCount(const QModelIndex& parent) const
{
	if (parent.column() > 0)
	{
		return 0;
	}

	if (!parent.isValid())
	{
		return m_rootItem->dataCount();
	}
	else
	{
		if (parent.internalPointer() == nullptr)
		{
			if (parent.row() < m_rootItem->childItems().size())
			{
				return m_rootItem->child(parent.row())->dataCount();
			}
		}
	}

	return 0;
}

int FilesDecisionModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return 1;
}

QVariant FilesDecisionModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}

	if (role != Qt::DisplayRole)
	{
		return QVariant();
	}

	if (index.internalPointer() == nullptr)
	{
		return m_rootItem->data(index.row());
	}
	else
	{
		TreeInnerItem *item = static_cast<TreeInnerItem*>(index.internalPointer());
		return item->data(index.row());
	}
}

Qt::ItemFlags FilesDecisionModel::flags(const QModelIndex& index) const
{
	Q_UNUSED(index);
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
