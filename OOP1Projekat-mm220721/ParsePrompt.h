#pragma once
#include "Parse.h"
#include "ParseArg.h"
#include <string>
#include <vector>
// Dervied class from ParseArg:

class ParsePrompt : public ParseArg {
public:

	void parseString(std::vector<std::string> list, std::string commandLine) override;

	std::string getName() override;

	// Not needed.
	std::string getOpt() override;

	std::string getArg() override;

	int getFlag() override;

	// Not needed.
	std::string getRedirection() override;

	// Not needed.
	int getRedirectionType() override;

};
