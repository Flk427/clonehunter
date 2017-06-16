#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QTreeWidget>
//#include <QListWidget>
#include <QVBoxLayout>
#include "ui/autotooltipdelegate.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	test();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::test()
{
	QAbstractItemDelegate* itemDelegate;

	CListWidget* lv = new CListWidget(ui->centralwidget);

	ui->treeWidget->setItemDelegate(new AutoToolTipDelegate( ui->treeWidget ));

//	ui->listView->setItemDelegate(itemDelegate);

//	ui->
}

CListWidget::CListWidget(QWidget* parent) : QWidget(parent)
{
	init();
}

void CListWidget::init()
{
	QTreeWidget* _tree = new QTreeWidget(this);
	QLayout* _layout = new QVBoxLayout(this);
	_layout->addWidget(_tree);

	_tree->setColumnCount(2); // Путь, дата модификации.

	_tree->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

	setLayout(_layout);
}
