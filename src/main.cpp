#include <QApplication>

#include "presentation/windows/IMainWindowViewModel.hpp"
#include "presentation/windows/MainWindowViewModel.hpp"
#include "presentation/windows/IMainWindow.hpp"
#include "presentation/windows/MainWindow.hpp"

using namespace id::presentation::windows;

int main(int argc, char** args)
{
    const auto& appName = "It Depends";
    QIcon icon(":icons/main");

    QApplication app(argc, args);
    QApplication::setWindowIcon(icon);
    QApplication::setApplicationDisplayName(appName);
    QApplication::setApplicationName(appName);

	const auto& window = std::make_shared<MainWindow>();
	const auto& viewModel = std::make_shared<MainWindowViewModel>(window);

	window->setViewModel(viewModel);
	window->show();

    return QApplication::exec();
}