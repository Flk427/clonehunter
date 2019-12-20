#include "AutoToolTipDelegate.h"

AutoToolTipDelegate::AutoToolTipDelegate(QObject* parent) : QStyledItemDelegate(parent)
{
}

AutoToolTipDelegate::~AutoToolTipDelegate()
{
}

bool AutoToolTipDelegate::helpEvent(QHelpEvent* e, QAbstractItemView* view,
									const QStyleOptionViewItem& option, const QModelIndex& index)
{
	if (!e || !view)
	{
		return false;
	}

	if (e->type() == QEvent::ToolTip)
	{
		QRect rect = view->visualRect(index);
		QSize size = sizeHint(option, index);

		// Если элемент не может быть целиком отображён в представлении, показывается подсказка.
		if (index.parent()==QModelIndex() || rect.width() < size.width())
		{
			QVariant tooltipText = index.data(Qt::UserRole+3);

			if (tooltipText.canConvert<QString>())
			{
				QToolTip::showText(e->globalPos(), tooltipText.toString(), view);
				return true;
			}
		}

		if (!QStyledItemDelegate::helpEvent(e, view, option, index))
		{
			QToolTip::hideText();
		}

		return true;
	}

	return QStyledItemDelegate::helpEvent(e, view, option, index);
}
