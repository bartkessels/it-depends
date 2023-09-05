#pragma once

#include <memory>
#include <QWidget>
#include <QString>
#include <QListWidget>
#include <QListWidgetItem>
#include <QIcon>
#include <QPixmap>

#include "presentation/models/DependencyUiModel.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class DependencyListWidget; }
QT_END_NAMESPACE

namespace id::presentation::widgets
{
	class DependencyListWidget: public QWidget
	{
		public:
			explicit DependencyListWidget(const std::shared_ptr<models::DependencyUiModel>& dependency, QWidget* parent = nullptr);
			~DependencyListWidget() override;

		private:
			inline static const int ICON_SIZE = 30;
			Ui::DependencyListWidget* ui;
	};
}