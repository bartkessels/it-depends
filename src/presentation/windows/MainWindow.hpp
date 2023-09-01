#pragma once

#include <memory>
#include <iterator>
#include <QDesktopServices>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QtreeWidgetItem>

#include "domain/models/Dependency.hpp"
#include "presentation/contracts/IUiMapper.hpp"
#include "presentation/models/DependencyListItemUiModel.hpp"
#include "presentation/models/UrlUiModel.hpp"
#include "presentation/states/EmptyState.hpp"
#include "presentation/states/ErrorState.hpp"
#include "presentation/states/LoadingState.hpp"
#include "presentation/states/MainWindowState.hpp"
#include "presentation/states/SuccessState.hpp"
#include "presentation/widgets/DependencyListWidget/DependencyListWidget.hpp"
#include "presentation/windows/IMainWindow.hpp"
#include "presentation/windows/IMainWindowViewModel.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace id::presentation::windows
{
	class MainWindow: public QMainWindow, public IMainWindow
	{
		Q_OBJECT

		public:
			explicit MainWindow(
				const std::shared_ptr<contracts::IUiMapper<domain::models::Dependency, models::DependencyListItemUiModel>>& dependencyListItemUiMapper,
				const std::shared_ptr<contracts::IUiMapper<domain::models::Url, models::UrlUiModel>>& urlUiMapper,
				QWidget* parent = nullptr
			);
			~MainWindow() override;

			void setViewModel(std::shared_ptr<IMainWindowViewModel> viewModel) override;
			void updateState(std::shared_ptr<states::MainWindowState> state) override;

		private:
			Ui::MainWindow* ui;
			std::shared_ptr<IMainWindowViewModel> viewModel;
			std::shared_ptr<contracts::IUiMapper<domain::models::Dependency, models::DependencyListItemUiModel>> dependencyListItemUiMapper;
			std::shared_ptr<contracts::IUiMapper<domain::models::Url, models::UrlUiModel>> urlUiMapper;

			void displayDependency(std::shared_ptr<domain::models::Dependency> dependency);
			void loadDependenciesIntoList(std::vector<std::shared_ptr<domain::models::Dependency>> dependencies, QListWidget* listWidget);
			auto openFile() -> std::string;
			void openCycloneDXFile();

		signals:
			void changeState(std::shared_ptr<states::MainWindowState> state);

		private slots:
			void handleStateChange(std::shared_ptr<states::MainWindowState> state);
			void displayDependencyDetails(QListWidgetItem* item);
			void openUrl(QListWidgetItem* item);
	};
}
