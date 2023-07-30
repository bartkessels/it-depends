#pragma once

namespace id::domain::models
{
	/**
	 * Types which represent different kind of url's.
	 *
	 * This is used as a mechanism to abstract away any specific information from
	 * a specific SBOM generator tool.
	 */
	enum UrlType
	{
		Website,
		VCS,
		IssueTracker
	};
}