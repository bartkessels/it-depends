#include "data/factories/MapperFactory.hpp"

using namespace id::data::factories;
using namespace id::data;

MapperFactory::MapperFactory(
	std::shared_ptr<contracts::IFileReaderFactory>  fileReaderFactory,
	std::shared_ptr<contracts::IBuilderFactory>  builderFactory
):
	fileReaderFactory(std::move(fileReaderFactory)),
	builderFactory(std::move(builderFactory))
{

}

auto MapperFactory::getMapper(domain::SbomType type) -> std::shared_ptr<contracts::IMapper>
{
	const auto& fileReader = fileReaderFactory->getFileReader();
	const auto& builder = builderFactory->build(type);

	return builder->build(fileReader);
}