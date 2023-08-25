#pragma once

#include <memory>
#include <string>
#include <list>
#include <nlohmann/json.hpp>

#include "domain/models/Hash.hpp"

using namespace id::domain;

namespace id::data::mappers::cyclonedx
{
	/**
	 * Map a json object with different kind of hashes to a generic list of Hashes.
	 *
	 */
	class HashMapper
	{
		public:
			~HashMapper() = default;

			std::list<std::shared_ptr<models::Hash>> mapHashes(nlohmann::json json);

		private:
			inline static const std::string JSON_KEY_ALGORITHM = "alg";
			inline static const std::string JSON_KEY_VALUE = "content";

			std::shared_ptr<models::Hash> mapHash(nlohmann::json json);
	};
}