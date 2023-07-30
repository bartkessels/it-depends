#pragma once

#include <memory>
#include <QMainWindow>

#include "presentation/states/EmptyState.hpp"
#include "presentation/states/ErrorState.hpp"
#include "presentation/states/LoadingState.hpp"
#include "presentation/states/MainWindowState.hpp"
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

			void setViewModel(std::shared_ptr<IMainWindowViewModel> viewModel) override;
			void updateState(std::shared_ptr<states::MainWindowState> state) override;

		private:
			Ui::MainWindow* ui;
			std::shared_ptr<IMainWindowViewModel> viewModel;
	};
}