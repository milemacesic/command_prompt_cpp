#pragma once
#include "Command.h"
#include <string>
// Derived Class from Command:

class Prompt : public Command {
public:

	// Constructor.
	Prompt(std::string arg, std::string symbol);

	void run() override;

	// Returns the value of the new symbol for the command prompt.
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

	// The text that was entered. The first character will be set as the new command prompt.
	std::string text;

	// The new symbol that will represent the new command prompt.
	std::string newSymbol;

};
