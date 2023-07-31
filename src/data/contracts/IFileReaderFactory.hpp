#pragma once

#include <memory>

#include "data/contracts/IFileReader.hpp"

namespace id::data::contracts
{
	struct IFileReaderFactory
	{
		public:
			virtual ~IFileReaderFactory() = default;

			virtual std::shared_ptr<IFileReader> getFileReader() = 0;
	};
}