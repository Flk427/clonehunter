#include "MainWindow.h"
#include "ui_MainWindow.h"
//#include <QTreeWidget>
//#include <QListWidget>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QVBoxLayout>
#include "ui/AutoToolTipDelegate.h"
#include "ui/FilesDecisionListView/FilesDecisionListView.h"

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
//	QAbstractItemDelegate* itemDelegate;
	//new CListWidget(ui->centralwidget);
	new FilesDecisionListView(ui->centralwidget);

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
	QTreeView* _tree = new QTreeView(this);

//	QTreeWidget* _tree = new QTreeWidget(this);
	QLayout* _layout = new QVBoxLayout(this);
	_layout->addWidget(_tree);

//	_tree->setColumnCount(2); // Путь, дата модификации.

	_tree->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	_tree->setModel(new QStandardItemModel());
//	_tree->setItemDelegate(new QStyledItemDelegate());
	_tree->setItemDelegate(new AutoToolTipDelegate(_tree));
	_tree->setAnimated(true);

	QStandardItemModel* m = qobject_cast<QStandardItemModel*>(_tree->model());

	m->appendRow(new QStandardItem("asd"));
	m->appendRow(new QStandardItem("zxcvbnmzxcvbnmzxcvbnmzxcvbnmzxcvbnm"));
	m->appendRow(new QStandardItem("qwe"));

	m->item(1)->appendRow(new QStandardItem("1"));
	m->item(1)->appendRow(new QStandardItem("2"));
	m->item(1)->appendRows(QList<QStandardItem*>() << new QStandardItem("3") << new QStandardItem("4"));

	_tree->setHeaderHidden(true);

	setLayout(_layout);
}
