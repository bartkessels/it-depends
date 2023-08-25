#include <catch2/catch.hpp>
#include <trompeloeil.hpp>
#include <memory>
#include <nlohmann/json.hpp>

#include "data/mappers/cyclonedx/DependencyMapper.hpp"
#include "domain/models/Dependency.hpp"

using namespace id::data::mappers::cyclonedx;

TEST_CASE("DependencyMapper.mapDependencies")
{


//	const auto& sut = std::make_shared<DependencyMapper>();

	SECTION("maps direct values to null pointers when the json keys aren't defined")
	{
		// Arrange
		const auto& json = nlohmann::json::parse(R"(
			{
				"component": {
					"type": "application",
					"bom-ref": "pkg:maven/org.keycloak/keycloak-parent@10.0.1",
					"group": "org.keycloak",
					"name": "keycloak-parent",
					"version": "10.0.2",
					"licenses": [
						{
							"license": {
								"id": "Apache-2.0"
							}
						}
					],
					"purl": "pkg:maven/org.keycloak/keycloak-parent@10.0.1"
				},
				"components": [
					{
						"type": "library",
						"bom-ref": "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar",
						"group": "org.bouncycastle",
						"name": "bcprov-jdk15on",
						"version": "1.62",
						"description": "The Bouncy Castle Crypto package is a Java implementation of cryptographic algorithms. This jar contains JCE provider and lightweight API for the Bouncy Castle Cryptography APIs for JDK 1.5 to JDK 1.8.",
						"hashes": [
							{
								"alg": "MD5",
								"content": "01b1a8cff910fdb9328cef5c437ff2f9"
							}
						],
						"licenses": [
							{
								"license": {
									"name": "Bouncy Castle License",
									"url": "http://www.bouncycastle.org/license.html
								}
							}
						],
						"externalReferences": [
							{
								"type": "issue-tracker",
								"url": "https://github.com/bcgit/bc-java/issues"
							},
							{
								"type": "vcs",
								"url": "https://github.com/bcgit/bc-java"
							}
						]
					}
				]
			}
		)");

		// Act

		// Assert
	}

	SECTION("maps direct values to empty strings when the json values are empty")
	{
		// Arrange

		// Act

		// Assert
	}

	SECTION("maps direct values to the json values")
	{
		// Arrange

		// Act

		// Assert
	}
}