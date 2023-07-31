#include "data/factories/FileReaderFactory.hpp"

using namespace id::data::factories;
using namespace id::data;

std::shared_ptr<contracts::IFileReader> FileReaderFactory::getFileReader()
{
	return std::make_shared<implementation::FileReader>();
}