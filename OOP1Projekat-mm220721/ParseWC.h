#pragma once
#include "Parse.h"
#include "ParseOptArg.h"
#include <string>
#include <vector>
// Derived class from ParseOptArg:

class ParseWC : public ParseOptArg {
public:

	void parseString(std::vector<std::string> list, std::string commandLine) override;

	std::string getName() override;

	std::string getOpt() override;

	std::string getArg() override;

	int getFlag() override;

	std::string getRedirection() override;

	int getRedirectionType() override;

};
