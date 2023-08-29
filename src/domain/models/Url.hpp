#pragma once

#include <string>

#include "domain/models/UrlType.hpp"

namespace id::domain::models
{
	/**
	 * An url that can be included by a dependency.
	 *
	 * An url has a type which can be mapped to a specific UI-name.
	 */
	struct Url
	{
		public:
			UrlType type;
			std::string url;
	};
}