#pragma once

#include <exception>
#include <string>

namespace id::data::exceptions
{
	class UnsupportedSBOMTypeException: public std::exception
	{
		public:
			[[nodiscard]] const char* what() const noexcept override {
				return message.c_str();
			}

		private:
			static inline const std::string message = "Unsupported SBOM type.";
	};
}
