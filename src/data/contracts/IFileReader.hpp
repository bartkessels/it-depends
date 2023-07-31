#pragma once

#include <string>

namespace id::data::contracts
{
	struct IFileReader
	{
		public:
			virtual ~IFileReader() = default;

			virtual std::string readFile(const std::string& filePath) = 0;
	};
}