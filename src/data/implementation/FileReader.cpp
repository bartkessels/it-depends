#include "data/implementation/FileReader.hpp"

using namespace id::data::implementation;
using namespace id::data;

std::string FileReader::readFile(const std::string& filePath)
{
	std::ifstream inFile;
	inFile.open(filePath);

	if (!inFile.good()) {
		inFile.close();
		throw exceptions::FileNotFoundException();
	} else if (inFile.peek() == std::ifstream::traits_type::eof()) {
		inFile.close();
		throw exceptions::EmptyFileException();
	}

	std::stringstream strStream;
	strStream << inFile.rdbuf();
	std::string str = strStream.str();
	inFile.close();

	return str;
}