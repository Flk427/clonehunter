#include "PreviewWidget.h"
#include "ui_PreviewWidget.h"

PreviewWidget::PreviewWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PreviewWidget)
{
	ui->setupUi(this);
}

PreviewWidget::~PreviewWidget()
{
	delete ui;
}
