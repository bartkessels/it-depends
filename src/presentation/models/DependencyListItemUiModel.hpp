#pragma once

#include <QString>

namespace id::presentation::models
{
	struct DependencyListItemUiModel
	{
		public:
			QString iconName;
			QString name;
			QString author;
			QString version;
	};
}