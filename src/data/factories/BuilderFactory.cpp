#include "data/factories/BuilderFactory.hpp"

using namespace id::data;
using namespace id::data::factories;

std::shared_ptr<contracts::IMapperBuilder> BuilderFactory::build(domain::SbomType type)
{
	switch (type)
	{
		case domain::SbomType::CycloneDX:
			return std::make_shared<builders::CycloneDXMapperBuilder>();
		default:
			throw exceptions::UnsupportedSBOMTypeException();
	}
}