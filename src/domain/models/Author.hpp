#pragma once

#include <string>

namespace id::domain::models
{
	/**
	 * Information about an author
	 *
	 * All public information about a specific author.
	 */
	struct Author
	{
		public:
			std::string name;
			std::string emailAddress;
			std::string website;
	};
}