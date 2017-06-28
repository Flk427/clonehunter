#ifndef TREEROOTITEM_H
#define TREEROOTITEM_H

#include "TreeInnerItem.h"

//class TreeInnerItem;

class TreeRootItem : public TreeInnerItem
{
public:
	explicit TreeRootItem(const QList<QVariant>& data);
	virtual ~TreeRootItem();

	void appendChild(TreeInnerItem* child);

	TreeInnerItem* child(int row);
	int childCount() const;

	QList<TreeInnerItem*> childItems() const;

private:
	explicit TreeRootItem(const QList<QVariant> &data, TreeRootItem *parentItem);

	QList<TreeInnerItem*> m_childItems;
};

#endif // TREEROOTITEM_H
