#include "presentation/mappers/DependencyUiMapper.hpp"

using namespace id;
using namespace id::presentation::mappers;


DependencyUiMapper::DependencyUiMapper(
	const std::shared_ptr<contracts::IUiMapper<domain::models::Url, models::UrlUiModel>>& urlUiMapper
):
	urlUiMapper(urlUiMapper)
{

}

auto DependencyUiMapper::map(const std::shared_ptr<domain::models::Dependency>& model) -> std::shared_ptr<models::DependencyUiModel>
{
	const auto& uiModel = std::make_shared<models::DependencyUiModel>();

	uiModel->iconName = getIconName(model);
	uiModel->name = QString::fromStdString(model->name);
	uiModel->version = QString::fromStdString(model->version);
	uiModel->description = QString::fromStdString(model->description);
	uiModel->urls = urlUiMapper->map(model->urls);

	if (model->author != nullptr) {
		uiModel->author = QString::fromStdString(model->author->name);
	}

	for (const auto& transitiveDependency: model->dependencies) {
		const auto& transitiveDependencyUiModel = map(transitiveDependency);
		uiModel->dependencies.emplace_back(transitiveDependencyUiModel);
	}

	return uiModel;
}

auto DependencyUiMapper::map(const std::vector<std::shared_ptr<domain::models::Dependency>>& models) -> std::vector<std::shared_ptr<models::DependencyUiModel>>
{
	auto uiModels = std::vector<std::shared_ptr<models::DependencyUiModel>>();

	for (const auto& model: models) {
		const auto& uiModel = map(model);
		uiModels.emplace_back(uiModel);
	}

	return uiModels;
}

auto DependencyUiMapper::getIconName(const std::shared_ptr<domain::models::Dependency>& model) -> QString
{
	switch (model->type) {
		case domain::models::Type::Application:
			return ":icons/type-app";
		case domain::models::Type::Library:
			return ":icons/type-lib";
		default:
			return ":icons/type-unknown";
	}
}
