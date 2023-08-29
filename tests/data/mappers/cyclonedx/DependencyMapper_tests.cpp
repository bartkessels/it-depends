#include <catch2/catch_test_macros.hpp>
#include <trompeloeil.hpp>
#include <list>
#include <memory>
#include <nlohmann/json.hpp>

#include "data/contracts/IJsonMapper.hpp"
#include "data/mappers/cyclonedx/DependencyMapper.hpp"
#include "domain/models/Dependency.hpp"
#include "domain/models/Hash.hpp"
#include "domain/models/License.hpp"
#include "domain/models/Url.hpp"

using namespace id::data;
using namespace id::data::mappers::cyclonedx;
using namespace id::domain;

class HashMapperMock: public contracts::IJsonMapper<std::list<std::shared_ptr<models::Hash>>>
{
	public:
		MAKE_MOCK1(map, std::list<std::shared_ptr<models::Hash>>(const nlohmann::json&), override);
};

class LicenseMapperMock: public contracts::IJsonMapper<std::list<std::shared_ptr<models::License>>>
{
	public:
		MAKE_MOCK1(map, std::list<std::shared_ptr<models::License>>(const nlohmann::json&), override);
};

class UrlMapperMock: public contracts::IJsonMapper<std::list<std::shared_ptr<models::Url>>>
{
	public:
		MAKE_MOCK1(map, std::list<std::shared_ptr<models::Url>>(const nlohmann::json&), override);
};

TEST_CASE("DependencyMapper.map")
{
	const auto& hashMapperMock = std::make_shared<HashMapperMock>();
	const auto& licenseMapperMock = std::make_shared<LicenseMapperMock>();
	const auto& urlMapperMock = std::make_shared<UrlMapperMock>();

	const auto& sut = std::make_shared<DependencyMapper>(hashMapperMock, licenseMapperMock, urlMapperMock);

	ALLOW_CALL(*hashMapperMock, map(trompeloeil::_)).RETURN(std::list<std::shared_ptr<models::Hash>>());
	ALLOW_CALL(*licenseMapperMock, map(trompeloeil::_)).RETURN(std::list<std::shared_ptr<models::License>>());
	ALLOW_CALL(*urlMapperMock, map(trompeloeil::_)).RETURN(std::list<std::shared_ptr<models::Url>>());

	SECTION("maps the values for a single dependency")
	{
		// Arrange
		const auto& expectedId = "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar";
		const auto& expectedName = "bcprov-jdk15on";
		const auto& expectedDescription = "The Bouncy Castle Crypto package is a Java implementation of cryptographic algorithms.";
		const auto& expectedVersion = "1.62";

		const nlohmann::json& json = {
			{ "components",
				{
					{
						  {"type", "library"},
						  {"bom-ref", expectedId},
						  {"group", "org.bouncycastle"},
						  {"name", expectedName},
						  {"version", expectedVersion},
						  {"description", expectedDescription},
						  {"hashes", {
								  {
										  {"alg", "MD5"},
										  {"content", "01b1a8cff910fdb9328cef5c437ff2f9"}
								  }
						  }},
						  {"licenses", {
								  {
										  {"license", {
												  {"name", "Bouncy Castle License"},
												  {"url", "http://www.bouncycastle.org/licence.html"}
										  }}
								  }
						  }},
						  {"purl", "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar"},
						  {"externalReferences", {
								  {
										  {"type", "issue-tracker"},
										  {"url", "https://github.com/bcgit/bc-java/issues"}
								  }
						  }}
					}
				}
			}
		};

		// Act
		const auto& result = sut->map(json);

		// Assert
		REQUIRE(result.front()->id == expectedId);
		REQUIRE(result.front()->name == expectedName);
		REQUIRE(result.front()->description == expectedDescription);
		REQUIRE(result.front()->version == expectedVersion);
	}

	SECTION("maps the values for multiple dependencies")
	{
		// Arrange
		const auto& expectedIdOne = "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar";
		const auto& expectedIdTwo = "pkg:maven/org.bouncycastle/bcpkix-jdk15on@1.62?type=jar";
		const auto& expectedNameOne = "bcprov-jdk15on";
		const auto& expectedNameTwo = "bcpkix-jdk15on";
		const auto& expectedDescriptionOne = "The Bouncy Castle Crypto package is a Java implementation of cryptographic algorithms.";
		const auto& expectedDescriptionTwo = "The Bouncy Castle Java APIs for CMS, PKCS, EAC, TSP, CMP, CRMF, OCSP, and certificate generation.";
		const auto& expectedVersionOne = "1.62";
		const auto& expectedVersionTwo = "1.57";

		const nlohmann::json& json = {
				{"components",
				 {
					{
						  {"type", "library"},
						  {"bom-ref", expectedIdOne},
						  {"group", "org.bouncycastle"},
						  {"name", expectedNameOne},
						  {"version", expectedVersionOne},
						  {"description", expectedDescriptionOne},
						  {"hashes", {
								  {
										  {"alg", "MD5"},
										  {"content", "01b1a8cff910fdb9328cef5c437ff2f9"}
								  }
						  }},
						  {"licenses", {
								  {
										  {"license", {
												  {"name", "Bouncy Castle License"},
												  {"url", "http://www.bouncycastle.org/licence.html"}
										  }}
								  }
						  }},
						  {"purl", "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar"},
						  {"externalReferences", {
								  {
										  {"type", "issue-tracker"},
										  {"url", "https://github.com/bcgit/bc-java/issues"}
								  }
						  }}
				  },
				  {
						  {"type", "library"},
						  {"bom-ref", expectedIdTwo},
						  {"group", "org.bouncycastle"},
						  {"name", expectedNameTwo},
						  {"version", expectedVersionTwo},
						  {"description", expectedDescriptionTwo},
						  {"hashes", {
								  {
										  {"alg", "MD5"},
										  {"content", "c488e97d0a455ef687b1b8d46795554f"}
								  }
						  }},
						  {"licenses", {
								  {
										  {"license", {
												  {"name", "Bouncy Castle License"},
												  {"url", "http://www.bouncycastle.org/licence.html"}
										  }}
								  }
						  }},
						  {"purl", "pkg:maven/org.bouncycastle/bcpkix-jdk15on@1.62?type=jar"},
						  {"externalReferences", {
								  {
										  {"type", "issue-tracker"},
										  {"url", "https://github.com/bcgit/bc-java/issues"}
								  }
						  }}
				 		}
				 	}
				}
		};

		// Act
		const auto& result = sut->map(json);

		// Assert
		REQUIRE(result.front()->id == expectedIdOne);
		REQUIRE(result.front()->name == expectedNameOne);
		REQUIRE(result.front()->description == expectedDescriptionOne);
		REQUIRE(result.front()->version == expectedVersionOne);

		REQUIRE(result.back()->id == expectedIdTwo);
		REQUIRE(result.back()->name == expectedNameTwo);
		REQUIRE(result.back()->description == expectedDescriptionTwo);
		REQUIRE(result.back()->version == expectedVersionTwo);
	}

	SECTION("maps the id to an empty string when bom-ref not available in the json object")
	{
		// Arrange
		const auto& expected = std::string();
		const auto& json = nlohmann::json::parse(R"(
			{
				"components": [
					{
						"type": "library",
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
						"licenses": [{"license": {
        					"name": "Bouncy Castle Licence",
        					"url": "http://www.bouncycastle.org/licence.html"
      					}}],
						"purl": "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar",
						"externalReferences": [
        					{
          						"type": "issue-tracker",
          						"url": "https://github.com/bcgit/bc-java/issues"
        					}
						]
					}
				]
			}
		)");

		// Act
		const auto& result = sut->map(json);

		// Assert
		REQUIRE(result.front()->id == expected);
	}

	SECTION("maps the name to an empty string when it's not available in the json object")
	{
		// Arrange
		const auto& expected = std::string();
		const auto& json = nlohmann::json::parse(R"(
			{
				"components": [
				    {
						"type": "library",
					    "bom-ref": "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar",
					    "group": "org.bouncycastle",
						"version": "1.62",
					 	"description": "The Bouncy Castle Crypto package is a Java implementation of cryptographic algorithms. This jar contains JCE provider and lightweight API for the Bouncy Castle Cryptography APIs for JDK 1.5 to JDK 1.8.",
						"hashes": [
							{
								"alg": "MD5",
								"content": "01b1a8cff910fdb9328cef5c437ff2f9"
						  	}
					 	],
					 	"licenses": [{"license": {
							"name": "Bouncy Castle Licence",
						  	"url": "http://www.bouncycastle.org/licence.html"
					 	}}],
					 	"purl": "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar",
					 	"externalReferences": [
							{
								"type": "issue-tracker",
							  	"url": "https://github.com/bcgit/bc-java/issues"
						  	}
					 	]
					}
				]
			}
		)");

		// Act
		const auto& result = sut->map(json);

		// Assert
		REQUIRE(result.front()->name == expected);
	}

	SECTION("maps the description to an empty string when it's not available in the json object")
	{
		// Arrange
		const auto& expected = std::string();
		const auto& json = nlohmann::json::parse(R"(
			{
				"components": [
				    {
						"type": "library",
					    "bom-ref": "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar",
					    "group": "org.bouncycastle",
						"name": "bcprov-jdk15on",
						"version": "1.62",
						"hashes": [
							{
								"alg": "MD5",
								"content": "01b1a8cff910fdb9328cef5c437ff2f9"
						  	}
					 	],
					 	"licenses": [{"license": {
							"name": "Bouncy Castle Licence",
						  	"url": "http://www.bouncycastle.org/licence.html"
					 	}}],
					 	"purl": "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar",
					 	"externalReferences": [
							{
								"type": "issue-tracker",
							  	"url": "https://github.com/bcgit/bc-java/issues"
						  	}
					 	]
					}
				]
			}
		)");

		// Act
		const auto& result = sut->map(json);

		// Assert
		REQUIRE(result.front()->description == expected);
	}
	SECTION("maps the version to an empty string when it's not available in the json object")
	{
		// Arrange
		const auto& expected = std::string();
		const auto& json = nlohmann::json::parse(R"(
			{
				"components": [
				    {
						"type": "library",
					    "bom-ref": "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar",
					    "group": "org.bouncycastle",
						"name": "bcprov-jdk15on",
						"description": "The Bouncy Castle Crypto package is a Java implementation of cryptographic algorithms. This jar contains JCE provider and lightweight API for the Bouncy Castle Cryptography APIs for JDK 1.5 to JDK 1.8.",
						"hashes": [
							{
								"alg": "MD5",
								"content": "01b1a8cff910fdb9328cef5c437ff2f9"
						  	}
					 	],
					 	"licenses": [{"license": {
							"name": "Bouncy Castle Licence",
						  	"url": "http://www.bouncycastle.org/licence.html"
					 	}}],
					 	"purl": "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar",
					 	"externalReferences": [
							{
								"type": "issue-tracker",
							  	"url": "https://github.com/bcgit/bc-java/issues"
						  	}
					 	]
					}
				]
			}
		)");

		// Act
		const auto& result = sut->map(json);

		// Assert
		REQUIRE(result.front()->version == expected);
	}

	SECTION("calls map on the HashMapper when the json object contains hashes")
	{
		// Arrange
		const auto& json = nlohmann::json::parse(R"(
			{
				"components": [
				    {
						"type": "library",
					    "bom-ref": "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar",
					    "group": "org.bouncycastle",
						"name": "bcprov-jdk15on",
						"description": "The Bouncy Castle Crypto package is a Java implementation of cryptographic algorithms. This jar contains JCE provider and lightweight API for the Bouncy Castle Cryptography APIs for JDK 1.5 to JDK 1.8.",
						"version": "1.62",
						"hashes": [
							{
								"alg": "MD5",
								"content": "01b1a8cff910fdb9328cef5c437ff2f9"
						  	}
					 	],
					 	"licenses": [{"license": {
							"name": "Bouncy Castle Licence",
						  	"url": "http://www.bouncycastle.org/licence.html"
					 	}}],
					 	"purl": "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar",
					 	"externalReferences": [
							{
								"type": "issue-tracker",
							  	"url": "https://github.com/bcgit/bc-java/issues"
						  	}
					 	]
					}
				]
			}
		)");

		// Assert
		REQUIRE_CALL(*hashMapperMock, map(trompeloeil::_)).RETURN(std::list<std::shared_ptr<models::Hash>>());

		// Act
		sut->map(json);
	}

	SECTION("calls map on the HashMapper when the json object doesn't contain hashes")
	{
		// Arrange
		const auto& json = nlohmann::json::parse(R"(
			{
				"components": [
				    {
						"type": "library",
					    "bom-ref": "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar",
					    "group": "org.bouncycastle",
						"name": "bcprov-jdk15on",
						"description": "The Bouncy Castle Crypto package is a Java implementation of cryptographic algorithms. This jar contains JCE provider and lightweight API for the Bouncy Castle Cryptography APIs for JDK 1.5 to JDK 1.8.",
						"version": "1.62",
					 	"licenses": [{"license": {
							"name": "Bouncy Castle Licence",
						  	"url": "http://www.bouncycastle.org/licence.html"
					 	}}],
					 	"purl": "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar",
					 	"externalReferences": [
							{
								"type": "issue-tracker",
							  	"url": "https://github.com/bcgit/bc-java/issues"
						  	}
					 	]
					}
				]
			}
		)");

		// Assert
		REQUIRE_CALL(*hashMapperMock, map(trompeloeil::_)).RETURN(std::list<std::shared_ptr<models::Hash>>());

		// Act
		sut->map(json);
	}


	SECTION("calls map on the LicenseMapper when the json object contains licenses")
	{
		// Arrange
		const auto& json = nlohmann::json::parse(R"(
			{
				"components": [
				    {
						"type": "library",
					    "bom-ref": "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar",
					    "group": "org.bouncycastle",
						"name": "bcprov-jdk15on",
						"description": "The Bouncy Castle Crypto package is a Java implementation of cryptographic algorithms. This jar contains JCE provider and lightweight API for the Bouncy Castle Cryptography APIs for JDK 1.5 to JDK 1.8.",
						"version": "1.62",
						"hashes": [
							{
								"alg": "MD5",
								"content": "01b1a8cff910fdb9328cef5c437ff2f9"
						  	}
					 	],
					 	"licenses": [{"license": {
							"name": "Bouncy Castle Licence",
						  	"url": "http://www.bouncycastle.org/licence.html"
					 	}}],
					 	"purl": "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar",
					 	"externalReferences": [
							{
								"type": "issue-tracker",
							  	"url": "https://github.com/bcgit/bc-java/issues"
						  	}
					 	]
					}
				]
			}
		)");

		// Assert
		REQUIRE_CALL(*licenseMapperMock, map(trompeloeil::_)).RETURN(std::list<std::shared_ptr<models::License>>());

		// Act
		sut->map(json);
	}

	SECTION("calls map on the LicenseMapper when the json object doesn't contain licenses")
	{
		// Arrange
		const auto& json = nlohmann::json::parse(R"(
			{
				"components": [
				    {
						"type": "library",
					    "bom-ref": "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar",
					    "group": "org.bouncycastle",
						"name": "bcprov-jdk15on",
						"description": "The Bouncy Castle Crypto package is a Java implementation of cryptographic algorithms. This jar contains JCE provider and lightweight API for the Bouncy Castle Cryptography APIs for JDK 1.5 to JDK 1.8.",
						"version": "1.62",
						"hashes": [
							{
								"alg": "MD5",
								"content": "01b1a8cff910fdb9328cef5c437ff2f9"
						  	}
					 	],
					 	"purl": "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar",
					 	"externalReferences": [
							{
								"type": "issue-tracker",
							  	"url": "https://github.com/bcgit/bc-java/issues"
						  	}
					 	]
					}
				]
			}
		)");

		// Assert
		REQUIRE_CALL(*licenseMapperMock, map(trompeloeil::_)).RETURN(std::list<std::shared_ptr<models::License>>());

		// Act
		sut->map(json);
	}

	SECTION("calls map on the UrlMapper when the json object contains urls")
	{
		// Arrange
		const auto& json = nlohmann::json::parse(R"(
			{
				"components": [
				    {
						"type": "library",
					    "bom-ref": "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar",
					    "group": "org.bouncycastle",
						"name": "bcprov-jdk15on",
						"description": "The Bouncy Castle Crypto package is a Java implementation of cryptographic algorithms. This jar contains JCE provider and lightweight API for the Bouncy Castle Cryptography APIs for JDK 1.5 to JDK 1.8.",
						"version": "1.62",
						"hashes": [
							{
								"alg": "MD5",
								"content": "01b1a8cff910fdb9328cef5c437ff2f9"
						  	}
					 	],
					 	"licenses": [{"license": {
							"name": "Bouncy Castle Licence",
						  	"url": "http://www.bouncycastle.org/licence.html"
					 	}}],
					 	"purl": "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar",
					 	"externalReferences": [
							{
								"type": "issue-tracker",
							  	"url": "https://github.com/bcgit/bc-java/issues"
						  	}
					 	]
					}
				]
			}
		)");

		// Assert
		REQUIRE_CALL(*urlMapperMock, map(trompeloeil::_)).RETURN(std::list<std::shared_ptr<models::Url>>());

		// Act
		sut->map(json);
	}

	SECTION("calls map on the UrlMapper when the json object doesn't contain urls")
	{
		// Arrange
		const auto& json = nlohmann::json::parse(R"(
			{
				"components": [
				    {
						"type": "library",
					    "bom-ref": "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar",
					    "group": "org.bouncycastle",
						"name": "bcprov-jdk15on",
						"description": "The Bouncy Castle Crypto package is a Java implementation of cryptographic algorithms. This jar contains JCE provider and lightweight API for the Bouncy Castle Cryptography APIs for JDK 1.5 to JDK 1.8.",
						"version": "1.62",
						"hashes": [
							{
								"alg": "MD5",
								"content": "01b1a8cff910fdb9328cef5c437ff2f9"
						  	}
					 	],
					 	"licenses": [{"license": {
							"name": "Bouncy Castle Licence",
						  	"url": "http://www.bouncycastle.org/licence.html"
					 	}}],
					 	"purl": "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar"
					}
				]
			}
		)");

		// Assert
		REQUIRE_CALL(*urlMapperMock, map(trompeloeil::_)).RETURN(std::list<std::shared_ptr<models::Url>>());

		// Act
		sut->map(json);
	}

	SECTION("maps the dependencies to an empty list when none are available")
	{
		// Arrange
		const auto& json = nlohmann::json::parse(R"(
			{
				"components": [
				    {
						"type": "library",
					    "bom-ref": "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar",
					    "group": "org.bouncycastle",
						"name": "bcprov-jdk15on",
						"description": "The Bouncy Castle Crypto package is a Java implementation of cryptographic algorithms. This jar contains JCE provider and lightweight API for the Bouncy Castle Cryptography APIs for JDK 1.5 to JDK 1.8.",
						"version": "1.62",
						"hashes": [
							{
								"alg": "MD5",
								"content": "01b1a8cff910fdb9328cef5c437ff2f9"
						  	}
					 	],
					 	"licenses": [{"license": {
							"name": "Bouncy Castle Licence",
						  	"url": "http://www.bouncycastle.org/licence.html"
					 	}}],
					 	"purl": "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar"
					}
				]
			}
		)");

		// Act
		const auto& result = sut->map(json);

		// Assert
		REQUIRE(result.front()->dependencies.empty());
	}

	// TODO: Test the mapping of dependencies

	SECTION("returns an empty list when the dependency is an empty object")
	{
		// Arrange
		const auto& json = nlohmann::json::parse(R"({ "components": [{}]})");

		// Act
		const auto& result = sut->map(json);

		// Assert
		REQUIRE(result.empty());
	}

	SECTION("returns a list with one object if one of the two is an empty json object")
	{
		// Arrange
		const auto& json = nlohmann::json::parse(R"(
			{ "components": [
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
						"licenses": [{"license": {
        					"name": "Bouncy Castle Licence",
        					"url": "http://www.bouncycastle.org/licence.html"
      					}}],
						"purl": "pkg:maven/org.bouncycastle/bcprov-jdk15on@1.62?type=jar",
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
					},
					{}
				]
			}
		)");

		// Act
		const auto& result = sut->map(json);

		// Assert
		REQUIRE(result.size() == 1);
	}

	SECTION("returns an empty list when an empty json object is given")
	{
		// Arrange
		const auto& json = nlohmann::json::parse("{}");

		// Act
		const auto& result = sut->map(json);

		// Assert
		REQUIRE(result.empty());
	}
}