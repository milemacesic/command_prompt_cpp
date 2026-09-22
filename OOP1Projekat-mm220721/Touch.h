#pragma once
#include "Command.h"
#include <string>
// Derived class from Command:

class Touch : public Command {
public:

	// Constructor.
	Touch(std::string arg);

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

	// Name of the file that will be opened. Error if the file already exists.
	std::string filename;

};
