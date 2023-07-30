#pragma once

#include <string>

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
			~Url() = default;

			std::string type;
			std::string url;
	};
}