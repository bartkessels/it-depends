#pragma once

#include <memory>
#include <QString>

#include "domain/models/Dependency.hpp"
#include "domain/models/Type.hpp"
#include "presentation/contracts/IUiMapper.hpp"
#include "presentation/models/DependencyListItemUiModel.hpp"

namespace id::presentation::mappers
{
	class DependencyListItemUiMapper: public contracts::IUiMapper<domain::models::Dependency, models::DependencyListItemUiModel>
	{
		public:
			auto map(const std::shared_ptr<domain::models::Dependency>& dependency) -> std::shared_ptr<models::DependencyListItemUiModel> override;

		private:
			static auto getIconName(const std::shared_ptr<domain::models::Dependency>& dependency) -> QString;
	};
}