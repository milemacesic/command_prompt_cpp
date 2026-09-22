#pragma once
#include "Parse.h"
#include <string>
#include <vector>
// Derived class from Parse:

class ParseArg : public Parse {
public:

	void parseString(std::vector<std::string> list, std::string commandLine) override;

	std::string getName() override;

	// Not needed.
	std::string getOpt() override;

	// Not needed.
	std::string getRepl() override;

	std::string getArg() override;

	int getFlag() override;

	std::string getRedirection() override;

	int getRedirectionType() override;
	
protected:

	void checkForInputRedirection(std::string commandLine, std::istringstream& iss, std::string tmp, std::string& arg, int& flag) override;

	void checkForOutputRedirection(std::string commandLine, std::istringstream& iss, std::string tmp, std::string& redirection, int& redirectionType, int& flag) override;

	void printError(std::string commandLine, std::string error, size_t position, int& flag) override;

};
