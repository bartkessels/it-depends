#pragma once

#include <memory>
#include <QString>

#include "domain/models/Url.hpp"
#include "domain/models/UrlType.hpp"
#include "presentation/contracts/IUiMapper.hpp"
#include "presentation/models/UrlUiModel.hpp"

namespace id::presentation::mappers
{
	/**
	 * Map Url models to a corresponding UI model.
	 *
	 * This includes the mapping of the current url name based
	 * on the UrlType.
	 *
	 */
	class UrlUiMapper: public contracts::IUiMapper<domain::models::Url, models::UrlUiModel>
	{
		public:
			auto map(const std::vector<std::shared_ptr<domain::models::Url>>& model) -> std::vector<std::shared_ptr<models::UrlUiModel>> override;

		private:
			auto map(const std::shared_ptr<domain::models::Url>& model) -> std::shared_ptr<models::UrlUiModel>;
			static auto getUrlName(const std::shared_ptr<domain::models::Url>& url) -> QString;
	};
}