#pragma once
#include "Command.h"
#include <string>
// Derived Class from Command:

class Truncate : public Command {
public:

	// Constructor.
	Truncate(std::string arg);

	void run() override;

	// Not needed.
	std::string getNewSymbol() override;

	// Not needed.
	std::string getOutput() override;

	// Not needed.
	std::string getRedirection() override;

private:

	// Not needed.
	std::string readArg() override;

	// Not needed.
	void printToFile(std::string filename, int typeOfOutput, std::string outputText) override;

	// Name of the file that will be opened. The file must exist prior to this command.
	std::string filename;

};
