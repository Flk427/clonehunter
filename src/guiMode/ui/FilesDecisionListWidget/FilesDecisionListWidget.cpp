#include "FilesDecisionListWidget.h"
#include "ui_FilesDecisionListWidget.h"

FilesDecisionListWidget::FilesDecisionListWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::FilesDecisionListWidget)
{
	ui->setupUi(this);
}

FilesDecisionListWidget::~FilesDecisionListWidget()
{
	delete ui;
}
