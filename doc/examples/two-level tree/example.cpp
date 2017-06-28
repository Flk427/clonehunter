void test2()
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
