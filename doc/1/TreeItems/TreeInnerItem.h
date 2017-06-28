#ifndef TREEINNERITEM_H
#define TREEINNERITEM_H

#include <QList>
#include <QVariant>
//#include "TreeRootItem.h"

//class TreeRootItem;

class TreeInnerItem
{
public:
	explicit TreeInnerItem(const QList<QVariant> &data, TreeInnerItem *parentItem = 0);
	virtual ~TreeInnerItem();

//	void appendChild(TreeItem *child);

//	TreeItem *child(int row);
	int dataCount() const;
//	int columnCount() const;
	QVariant data(int column) const; // Свои данные
	int row() const;
	TreeInnerItem *parentItem();

private:
//	QList<TreeItem*> m_childItems;
	QList<QVariant> m_itemData;
	TreeInnerItem* m_parentItem;
};

#endif // TREEINNERITEM_H
