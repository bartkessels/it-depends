#pragma once

#include <string>

namespace id::data::contracts
{
	struct IFileReader
	{
		public:
			virtual auto readFile(const std::string& filePath) -> std::string = 0;
	};
}