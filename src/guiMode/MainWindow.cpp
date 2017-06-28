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
#include "ui/FilesDecisionListView/TreeItems/TreeInnerItem.h"
#include "ui/FilesDecisionListView/TreeItems/TreeRootItem.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->treeWidget->setItemDelegate(new AutoToolTipDelegate( ui->treeWidget ));

	test2();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::test()
{
//	QAbstractItemDelegate* itemDelegate;
	//new CListWidget(ui->centralwidget);
	new FilesDecisionListView(nullptr, ui->centralwidget);

	FilesDecisionFileInfo info1;
	info1.name = "asdasda";
	info1.path = "c:\\asdasdasd";

	FilesDecisionFileInfo info2;
	info2.name = "zxczxc";
	info2.path = "c:\\zxczxczxc";

	FilesDecisionFileCopiesList list1 = FilesDecisionFileCopiesList() << info1 << info2;

	FilesDecisionFileInfo info3;
	info3.name = "fhgjlkjgh";
	info3.path = "c:\\fhgjlkjghzxc";

	FilesDecisionFileInfo info4;
	info4.name = "nbfkbsdc";
	info4.path = "c:\\nbfkbsdcxcz,mxvc";

	FilesDecisionFileCopiesList list2 = FilesDecisionFileCopiesList() << info3 << info4;

	FilesDecisionFiles filesTree = FilesDecisionFiles() << list1 << list2;

//	v->setFilesInfo(filesTree);

//	ui->listView->setItemDelegate(itemDelegate);

	//	ui->
}

void MainWindow::test2()
{
	QList<QVariant> data = QList<QVariant>() << "1asd" << "2zxc";

	TreeRootItem* root = new TreeRootItem(data);

	QList<QVariant> data1 = QList<QVariant>() << "11asd" << "12zxc" << "13qwe";

	TreeInnerItem* in1 = new TreeInnerItem(data1, root);

	root->appendChild(/*<fileName> , */ in1);

	QList<QVariant> data2 = QList<QVariant>() << "21asd" << "22zxc" << "23qwe" << "24dfgh";

	TreeInnerItem* in2 = new TreeInnerItem(data2, root);

	root->appendChild(in2);

	FilesDecisionListView* v = new FilesDecisionListView(root, ui->centralwidget);
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
