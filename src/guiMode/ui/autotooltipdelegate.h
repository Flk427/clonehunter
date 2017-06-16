#ifndef AUTOTOOLTIPDELEGATE_H
#define AUTOTOOLTIPDELEGATE_H

#include <QAbstractItemView>
#include <QToolTip>
#include <QStyledItemDelegate>
#include <QHelpEvent>

/*!
\brief Tooltips for truncated items in a QTreeView
\link http://www.mimec.org/node/337
\author Michał Męciński

Then tooltips are shown for all items, whether they are truncated or not. It doesn't look very well.
If the item is truncated, the display text is retrieved and displayed as a tooltip.
Otherwise the default handler is called, so a custom tooltip may be displayed.
If you want, you may reverse this behavior and only display the automatic tooltip if there is no custom one,
or remove the call to the default handler if there are no custom tooltips.
Note that it will also work for other kinds of views, not only QTreeView.
*/

class AutoToolTipDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	AutoToolTipDelegate(QObject* parent);
	~AutoToolTipDelegate();

public slots:
	bool helpEvent(QHelpEvent* e, QAbstractItemView* view, const QStyleOptionViewItem& option, const QModelIndex& index);
};

#endif // AUTOTOOLTIPDELEGATE_H
