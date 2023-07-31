#pragma once

#include <string>
#include <list>
#include <memory>

#include "domain/models/Url.hpp"

namespace id::domain::models
{
	/**
	 * Representation of a single dependency
	 *
	 * This includes information about the current dependencies
	 * and all transitive dependencies.
	 */
	struct Dependency
	{
		public:
			~Dependency() = default;

			std::string id;
			std::string name;
			std::string version;
			std::list<std::shared_ptr<Url>> urls;
			std::list<std::shared_ptr<Dependency>> dependencies;
	};
}