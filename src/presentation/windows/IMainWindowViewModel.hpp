#pragma once

#include <memory>
#include <string>

#include "domain/SbomType.hpp"

namespace id::presentation::windows
{
	struct IMainWindowViewModel
	{
		public:
			virtual ~IMainWindowViewModel() = default;

			virtual void loadSBOM(std::shared_ptr<domain::SbomType> type, std::string fileLocation) = 0;
	};
}