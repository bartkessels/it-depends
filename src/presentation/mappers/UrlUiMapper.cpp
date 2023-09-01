#include "presentation/mappers/UrlUiMapper.hpp"

using namespace id::presentation;
using namespace id::presentation::mappers;

auto UrlUiMapper::map(const std::shared_ptr<domain::models::Url>& model) -> std::shared_ptr<models::UrlUiModel>
{
	const auto& uiModel = std::make_shared<models::UrlUiModel>();

	uiModel->name = getUrlName(model);
	uiModel->uri = QString::fromStdString(model->url);

	return uiModel;
}

auto UrlUiMapper::getUrlName(const std::shared_ptr<domain::models::Url>& url) -> QString
{
	switch (url->type) {
		case domain::models::UrlType::IssueTracker:
			return "Issue tracker";
		case domain::models::UrlType::Website:
			return "Website";
		case domain::models::UrlType::VCS:
			return "Version control system";
		default:
			throw;
	}
}