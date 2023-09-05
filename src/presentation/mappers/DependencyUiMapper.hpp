#pragma once

#include <memory>
#include <vector>
#include <QString>

#include "domain/models/Dependency.hpp"
#include "domain/models/Type.hpp"
#include "presentation/contracts/IUiMapper.hpp"
#include "presentation/models/DependencyUiModel.hpp"
#include "presentation/models/UrlUiModel.hpp"

namespace id::presentation::mappers
{
	/**
	 * Map Dependency models to a corresponding UI model.
	 *
	 * This includes the mapping of the Author name if an
	 * Author is known and map a iconName for the Type of
	 * dependency.
	 *
	 */
	class DependencyUiMapper: public contracts::IUiMapper<domain::models::Dependency, models::DependencyUiModel>
	{
		public:
			explicit DependencyUiMapper(
				const std::shared_ptr<contracts::IUiMapper<domain::models::Url, models::UrlUiModel>>& urlUiMapper
			);

			auto map(const std::vector<std::shared_ptr<domain::models::Dependency>>& models) -> std::vector<std::shared_ptr<models::DependencyUiModel>> override;

		private:
			std::shared_ptr<contracts::IUiMapper<domain::models::Url, models::UrlUiModel>> urlUiMapper;

			auto map(const std::shared_ptr<domain::models::Dependency>& model) -> std::shared_ptr<models::DependencyUiModel>;
			static auto getIconName(const std::shared_ptr<domain::models::Dependency>& model) -> QString;
	};
}