#pragma once

#include <string>

namespace id::domain::models
{
	/**
	 * License that a dependency is licensed as.
	 *
	 * This only includes the name of the license, such as
	 * MIT or Apache-2.0 for example. With an optional url where
	 * the license is located.
	 */
	struct License
	{
		public:
			std::string name;
			std::string url;
	};
}