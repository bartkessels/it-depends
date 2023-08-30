#pragma once

#include <memory>

#include "data/contracts/IFileReader.hpp"

namespace id::data::contracts
{
	struct IFileReaderFactory
	{
		public:
			virtual auto getFileReader() -> std::shared_ptr<contracts::IFileReader> = 0;
	};
}