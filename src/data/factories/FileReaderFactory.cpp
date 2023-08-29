#include "data/factories/FileReaderFactory.hpp"

using namespace id::data::factories;
using namespace id::data;

auto FileReaderFactory::getFileReader() -> std::shared_ptr<contracts::IFileReader>
{
	return std::make_shared<implementation::FileReader>();
}