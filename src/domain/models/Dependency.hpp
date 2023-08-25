#pragma once

#include <string>
#include <list>
#include <memory>

#include "domain/models/Hash.hpp"
#include "domain/models/License.hpp"
#include "domain/models/Url.hpp"

namespace id::domain::models
{
	/**
	 * Representation of a single dependency
	 *
	 * This includes information about the current dependencies,
	 * all transitive dependencies and the different hashes to validate
	 * the correct binary is downloaded.
	 */
	struct Dependency
	{
		public:
			~Dependency() = default;

			std::string id;
			std::string name;
			std::string version;
			std::list<std::shared_ptr<Url>> urls;
			std::list<std::shared_ptr<Hash>> hashes;
			std::list<std::shared_ptr<License>> licenses;
			std::list<std::shared_ptr<Dependency>> dependencies;
	};
}