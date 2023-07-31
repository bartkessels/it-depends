#include "data/factories/MapperFactory.hpp"

using namespace id::data::factories;
using namespace id::data;

MapperFactory::MapperFactory(std::shared_ptr<contracts::IFileReaderFactory> fileReaderFactory):
	fileReaderFactory(fileReaderFactory)
{

}

std::shared_ptr<contracts::IMapper> MapperFactory::getMapper(domain::SbomType type)
{
	const auto& fileReader = fileReaderFactory->getFileReader();

	if (type == domain::SbomType::CycloneDX)
	{
		return std::make_shared<mappers::CycloneDXMapper>(fileReader);
	}

	throw "Unsupported type";
}