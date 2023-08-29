#include "data/factories/BuilderFactory.hpp"

using namespace id::data;
using namespace id::data::factories;

auto BuilderFactory::build(domain::SbomType type) -> std::shared_ptr<contracts::IMapperBuilder>
{
	switch (type)
	{
		case domain::SbomType::CycloneDX:
			return std::make_shared<builders::CycloneDXMapperBuilder>();
		default:
			throw exceptions::UnsupportedSBOMTypeException();
	}
}