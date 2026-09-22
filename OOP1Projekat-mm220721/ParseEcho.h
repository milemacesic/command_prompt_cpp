#pragma once
#include "Parse.h"
#include "ParseArg.h"
#include <string>
#include <vector>
// Derived class from ParseArg:

class ParseEcho : public ParseArg {
public:

	void parseString(std::vector<std::string> list, std::string commandLine) override;

	std::string getName() override;

	// Not needed.
	std::string getOpt() override;

	std::string getArg() override;

	int getFlag() override;

	std::string getRedirection() override;

	int getRedirectionType() override;

};
