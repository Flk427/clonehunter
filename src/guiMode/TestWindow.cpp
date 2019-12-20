#include "TestWindow.h"
#include "ui_TestWindow.h"
//#include <QTreeWidget>
//#include <QListWidget>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QVBoxLayout>
#include "ui/AutoToolTipDelegate.h"
#include "ui/FilesDecisionListView/FilesDecisionListView.h"

TestWindow::TestWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::TestWindow)
{
	ui->setupUi(this);
	ui->treeWidget->setItemDelegate(new AutoToolTipDelegate( ui->treeWidget ));

//	test();
//	test2();
}

TestWindow::~TestWindow()
{
	delete ui;
}

/*
void TestWindow::test()
{
	FilesDecisionListView* v = new FilesDecisionListView(ui->centralwidget);
	QFont font;
	font.setFamily("Consolas");
	v->setFont(font);
	v->setItemDelegate(new AutoToolTipDelegate(v));

	FilesDecisionFileInfo info1;
	info1.name = "asdasda";
	info1.path = "c:\\asdasdasd";

	FilesDecisionFileInfo info2;
	info2.name = "zxczxc";
	info2.path = "c:\\zxczxczxc";

	FilesDecisionFileCopiesList* list1 = new FilesDecisionFileCopiesList();
	list1->append(info1);
	list1->append(info2);

	FilesDecisionFileInfo info3;
	info3.name = "fhgjlkjgh";
	info3.path = "c:\\fhgjlkjghzxc";

	FilesDecisionFileInfo info4;
	info4.name = "nbfkbsdc";
	info4.path = "c:\\nbfkbsdcxczmxvcsdkbskjcsjdksldnck";

	FilesDecisionFileCopiesList* list2 = new FilesDecisionFileCopiesList();

	list2->append(info3);
	list2->append(info4);

	FilesDecisionFiles filesTree = FilesDecisionFiles() << list1 << list2;

	v->setFilesInfo(filesTree);
}
*/

void TestWindow::test2()
{
//	QList<QVariant> data = QList<QVariant>() << "1asd" << "2zxc";
//	TreeRootItem* root = new TreeRootItem(data);
//	QList<QVariant> data1 = QList<QVariant>() << "11asd" << "12zxc" << "13qwe";
//	TreeInnerItem* in1 = new TreeInnerItem(data1, root);
//	root->appendChild(/*<fileName> , */ in1);
//	QList<QVariant> data2 = QList<QVariant>() << "21asd" << "22zxc" << "23qwe" << "24dfgh";
//	TreeInnerItem* in2 = new TreeInnerItem(data2, root);
//	root->appendChild(in2);
//	new FilesDecisionListView(root, ui->centralwidget);
}

CListWidget::CListWidget(QWidget* parent) : QWidget(parent)
{
	init();
}

void CListWidget::init()
{
	QTreeView* _tree = new QTreeView(this);

	QLayout* _layout = new QVBoxLayout(this);
	_layout->addWidget(_tree);

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
