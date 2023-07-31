#pragma once

#include <exception>
#include <string>

namespace id::data::exceptions
{
	class FileNotFoundException: public std::exception
	{
		public:
			const char* what() const noexcept override {
				return message.c_str();
			}

		private:
			const std::string message = "The file could not be found.";
	};
}