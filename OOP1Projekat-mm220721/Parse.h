#pragma once
#include <string>
#include <vector>
#include <sstream>
// Abstract Class:

class Parse {
public:

	// Destructor.
	virtual ~Parse() {};

	// Abstract method. It helps with determining which type of command it is, based on the inputs.
	virtual void parseString(std::vector<std::string> list, std::string commandLine) = 0;

	// Abstract method. It returns the name of the command.
	virtual std::string getName() = 0;

	// Abstract method. It returns the option of the command.
	virtual std::string getOpt() = 0;

	// Abstract method. It returns the argument of the command.
	virtual std::string getArg() = 0;

	// Abstract method. It returns the replacement string for the command 'tr'.
	virtual std::string getRepl() = 0;

	// Abstract method. It returns the flag from the parser.
	virtual int getFlag() = 0;

	// Abstract method. It returns the redirection of the command.
	virtual std::string getRedirection() = 0;

	// Abstract method. It returns the type of redirection of the command.
	virtual int getRedirectionType() = 0;

 protected:

	// Name of the command.
	std::string name;

	// Option of the command.
	std::string opt;

	// Replacement string for the 'tr' command only.
	std::string repl;

	// Argument of the command.
	std::string arg;

	// Flag object. If activated, then there is a mistake with the input.
	int flag = 0;

	// Redirection of the command.
	std::string redirection;

	// Type of output redirection depending on the symbols ('<' or '<<'). 0 if '<' and 1 if '<<'.
	int redirectionType = 0;

	// Abstract method. It checks for potential input redirections for certain commands.
	virtual void checkForInputRedirection(std::string commandLine, std::istringstream& iss, std::string tmp, std::string& arg, int& flag) = 0;

	// Abstract method. It checks for potential output redirections for certain commands.
	virtual void checkForOutputRedirection(std::string commandLine, std::istringstream& iss, std::string tmp, std::string& redirection, int& redirectionType, int& flag) = 0;

	// Abstract method. This method is used when an error occurs while the command line is being parsed.
	virtual void printError(std::string commandLine, std::string error, size_t position, int& flag) = 0;

};
