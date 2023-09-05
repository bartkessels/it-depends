#pragma once

#include <string>
#include <memory>
#include <vector>

#include "domain/models/Author.hpp"
#include "domain/models/Hash.hpp"
#include "domain/models/License.hpp"
#include "domain/models/Type.hpp"
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
			std::string id;
			Type type;
			std::string name;
			std::string description;
			std::string version;
			std::shared_ptr<Author> author;
			std::vector<std::shared_ptr<Url>> urls;
			std::vector<std::shared_ptr<Hash>> hashes;
			std::vector<std::shared_ptr<License>> licenses;
			std::vector<std::shared_ptr<Dependency>> dependencies;
	};
}