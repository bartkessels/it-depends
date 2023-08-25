#pragma once

#include <string>

namespace id::domain::models
{
	/**
	 * Representation of a specific hash for a dependency
	 *
	 * This includes both the algorithm used to calculate the hash
	 * as well as the hash value itself.
	 */
	struct Hash
	{
		public:
			~Hash() = default;

			std::string algorithm;
			std::string value;
	};
}