#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "data/contracts/IFileReader.hpp"
#include "data/exceptions/EmptyFileException.hpp"
#include "data/exceptions/FileNotFoundException.hpp"

namespace id::data::implementation
{
	class FileReader: public contracts::IFileReader
	{
		public:
			auto readFile(const std::string& filePath) -> std::string override;
	};
}