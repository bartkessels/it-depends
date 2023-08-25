#include "data/mappers/cyclonedx/HashMapper.hpp"

using namespace id::data::mappers::cyclonedx;

std::list<std::shared_ptr<models::Hash>> HashMapper::mapHashes(nlohmann::json json)
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
std::shared_ptr<models::Hash> HashMapper::mapHash(nlohmann::json json)
{
	const auto& hash = std::make_shared<models::Hash>();

	hash->algorithm = json.value(JSON_KEY_ALGORITHM, std::string());
	hash->value = json.value(JSON_KEY_VALUE, std::string());

	return hash;
}
