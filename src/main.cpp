#include <QApplication>

#include "data/factories/BuilderFactory.hpp"
#include "data/factories/FileReaderFactory.hpp"
#include "data/factories/MapperFactory.hpp"
#include "presentation/windows/IMainWindowViewModel.hpp"
#include "presentation/windows/MainWindowViewModel.hpp"
#include "presentation/windows/IMainWindow.hpp"
#include "presentation/windows/MainWindow.hpp"

using namespace id;
using namespace id::presentation::windows;

int main(int argc, char** args)
{
    const auto& appName = "It Depends";
    QIcon icon(":icons/main");

    QApplication app(argc, args);
    QApplication::setWindowIcon(icon);
    QApplication::setApplicationDisplayName(appName);
    QApplication::setApplicationName(appName);

	// Setup dependency tree
	const auto& fileReaderFactory = std::make_shared<data::factories::FileReaderFactory>();
	const auto& builderFactory = std::make_shared<data::factories::BuilderFactory>();
	const auto& mapperFactory = std::make_shared<data::factories::MapperFactory>(fileReaderFactory, builderFactory);

	const auto& window = std::make_shared<MainWindow>();
	const auto& viewModel = std::make_shared<MainWindowViewModel>(window, mapperFactory);

	window->setViewModel(viewModel);
	window->show();

    return QApplication::exec();
}