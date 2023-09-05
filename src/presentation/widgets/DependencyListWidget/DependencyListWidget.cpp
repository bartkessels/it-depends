#include "presentation/widgets/DependencyListWidget/DependencyListWidget.hpp"
#include "./ui_DependencyListWidget.h"

using namespace id::presentation::widgets;

DependencyListWidget::DependencyListWidget(const std::shared_ptr<models::DependencyUiModel>& dependency, QWidget* parent):
	QWidget(parent),
	ui(new Ui::DependencyListWidget())
{
	ui->setupUi(this);

	ui->icon->setPixmap(QIcon(dependency->iconName).pixmap(ICON_SIZE, ICON_SIZE));
	ui->name->setText(dependency->name);
	ui->author->setText(dependency->author);
	ui->version->setText(dependency->version);
}

DependencyListWidget::~DependencyListWidget()
{
	delete ui;
}