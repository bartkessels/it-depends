#include "presentation/mappers/DependencyListItemUiMapper.hpp"

using namespace id;
using namespace id::presentation::mappers;

auto DependencyListItemUiMapper::map(const std::shared_ptr<domain::models::Dependency>& dependency) -> std::shared_ptr<models::DependencyListItemUiModel>
{
	const auto& uiModel = std::make_shared<models::DependencyListItemUiModel>();

	uiModel->iconName = getIconName(dependency);
	uiModel->name = QString::fromStdString(dependency->name);
	uiModel->version = QString::fromStdString(dependency->version);

	if (dependency->author != nullptr) {
		uiModel->author = QString::fromStdString(dependency->author->name);
	}

	return uiModel;
}

auto DependencyListItemUiMapper::getIconName(const std::shared_ptr<domain::models::Dependency>& dependency) -> QString
{
	switch (dependency->type) {
		case domain::models::Type::Library:
			return ":icons/type-lib";
		case domain::models::Type::Application:
			return ":icons/type-app";
		default:
			return ":icons/type-unknown";
	}
}
