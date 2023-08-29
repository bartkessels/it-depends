#pragma once

#include <string>

#include "domain/SbomType.hpp"

namespace id::presentation::windows
{
	struct IMainWindowViewModel
	{
		public:
			virtual void loadSBOM(domain::SbomType type, const std::string& fileLocation) = 0;
	};
}