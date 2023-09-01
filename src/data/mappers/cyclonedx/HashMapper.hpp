#pragma once

#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include <vector>

#include "data/contracts/IJsonMapper.hpp"
#include "domain/models/Hash.hpp"

using namespace id::domain;

namespace id::data::mappers::cyclonedx
{
	/**
	 * Map a json object with different kind of hashes to a generic list of Hashes.
	 *
	 */
	class HashMapper: public contracts::IJsonMapper<std::vector<std::shared_ptr<models::Hash>>>
	{
		public:
			auto map(const nlohmann::json& json) -> std::vector<std::shared_ptr<models::Hash>> override;

		private:
			inline static const std::string JSON_KEY_ALGORITHM = "alg";
			inline static const std::string JSON_KEY_VALUE = "content";

			static auto mapHash(const nlohmann::json& json) -> std::shared_ptr<models::Hash>;
	};
}