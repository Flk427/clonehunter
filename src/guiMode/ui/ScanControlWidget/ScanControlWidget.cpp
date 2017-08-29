#include "ScanControlWidget.h"
#include "ui_ScanControlWidget.h"

ScanControlWidget::ScanControlWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ScanControlWidget)
{
	ui->setupUi(this);
}

ScanControlWidget::~ScanControlWidget()
{
	delete ui;
}
