#pragma once

#include <memory>
#include <vector>
#include <QString>

#include "presentation/models/UrlUiModel.hpp"

namespace id::presentation::models
{
	struct DependencyUiModel
	{
		public:
			QString iconName;
			QString name;
			QString author;
			QString version;
			QString description;
			std::vector<std::shared_ptr<UrlUiModel>> urls;
			std::vector<std::shared_ptr<DependencyUiModel>> dependencies;
	};
}