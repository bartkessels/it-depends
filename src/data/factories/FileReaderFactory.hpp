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
			~FileReaderFactory() override = default;

			std::shared_ptr<contracts::IFileReader> getFileReader() override;
	};
}