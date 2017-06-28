#include "TreeInnerItem.h"
#include "TreeRootItem.h"

TreeInnerItem::TreeInnerItem(const QList<QVariant> &data, TreeInnerItem *parent)
{
	m_parentItem = parent;
	m_itemData = data;
}

TreeInnerItem::~TreeInnerItem()
{
}

int TreeInnerItem::dataCount() const
{
	return m_itemData.count();
}

QVariant TreeInnerItem::data(int column) const
{
	return m_itemData.value(column);
}

TreeInnerItem *TreeInnerItem::parentItem()
{
	return m_parentItem;
}

int TreeInnerItem::row() const
{
	if (m_parentItem)
		return dynamic_cast<TreeRootItem*>(m_parentItem)->childItems().indexOf(const_cast<TreeInnerItem*>(this));

	return 0;
}
