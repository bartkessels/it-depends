#pragma once

#include <memory>
#include <iterator>
#include <QDesktopServices>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QIcon>

#include "domain/SbomType.hpp"
#include "presentation/models/DependencyUiModel.hpp"
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
			explicit MainWindow(QWidget* parent = nullptr);
			~MainWindow() override;

			void setViewModel(const std::shared_ptr<IMainWindowViewModel>& viewModel) override;
			void updateState(const std::shared_ptr<states::MainWindowState>& state) override;

		private:
			static inline const int ICON_SIZE = 50;

			Ui::MainWindow* ui;
			std::shared_ptr<IMainWindowViewModel> viewModel;

			void displayDependency(const std::shared_ptr<models::DependencyUiModel>& dependency);
			void loadDependenciesIntoList(const std::vector<std::shared_ptr<models::DependencyUiModel>>& dependencies, QListWidget* listWidget);
			auto openFile() -> std::string;
			void openCycloneDXFile();

		signals:
			void changeState(std::shared_ptr<states::MainWindowState> state);

		private slots:
			void handleStateChange(std::shared_ptr<states::MainWindowState> state);
			void displayDependencyDetails(QListWidgetItem* item);
			static void openUrl(QListWidgetItem* item);
			void filterList(const QString& searchQuery);
	};
}
