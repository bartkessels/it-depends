#include "data/mappers/cyclonedx/HashMapper.hpp"

using namespace id::data::mappers::cyclonedx;

auto HashMapper::map(const nlohmann::json& json) -> std::list<std::shared_ptr<models::Hash>>
{
	auto hashes = std::list<std::shared_ptr<models::Hash>>();

	for (const auto& object: json) {
		if (!object.empty()) {
			const auto& hash = mapHash(object);
			hashes.emplace_back(hash);
		}
	}

	return hashes;
}

auto HashMapper::mapHash(const nlohmann::json& json) -> std::shared_ptr<models::Hash>
{
	const auto& hash = std::make_shared<models::Hash>();

	hash->algorithm = json.value(JSON_KEY_ALGORITHM, std::string());
	hash->value = json.value(JSON_KEY_VALUE, std::string());

	return hash;
}
