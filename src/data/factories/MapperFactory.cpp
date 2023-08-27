#include "data/factories/MapperFactory.hpp"

using namespace id::data::factories;
using namespace id::data;

MapperFactory::MapperFactory(
	std::shared_ptr<contracts::IFileReaderFactory> fileReaderFactory,
	std::shared_ptr<contracts::IBuilderFactory> builderFactory
):
	fileReaderFactory(fileReaderFactory),
	builderFactory(builderFactory)
{

}

std::shared_ptr<contracts::IMapper> MapperFactory::getMapper(domain::SbomType type)
{
	const auto& fileReader = fileReaderFactory->getFileReader();
	const auto& builder = builderFactory->build(type);

	return builder->build(fileReader);
}