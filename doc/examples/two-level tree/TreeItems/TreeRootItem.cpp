#include "TreeRootItem.h"
#include "TreeInnerItem.h"

TreeRootItem::TreeRootItem(const QList<QVariant>& data) : TreeInnerItem(data)
{

}

TreeRootItem::~TreeRootItem()
{
	qDeleteAll(m_childItems);
}

void TreeRootItem::appendChild(TreeInnerItem* child)
{
	m_childItems.append(child);
}

TreeInnerItem* TreeRootItem::child(int row)
{
	return m_childItems.value(row);
}

int TreeRootItem::childCount() const
{
	return m_childItems.count();
}

QList<TreeInnerItem*> TreeRootItem::childItems() const
{
	return m_childItems;
}
