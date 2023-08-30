#pragma once

#include <memory>

#include "data/contracts/IFileReader.hpp"
#include "data/contracts/IFileReaderFactory.hpp"
#include "data/implementation/FileReader.hpp"

namespace id::data::factories
{
	class FileReaderFactory: public contracts::IFileReaderFactory
	{
		public:
			auto getFileReader() -> std::shared_ptr<contracts::IFileReader> override;
	};
}