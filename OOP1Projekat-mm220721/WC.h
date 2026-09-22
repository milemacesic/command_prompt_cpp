#pragma once
#include "Command.h"
#include <string>
// Derived class from Command:

class WC : public Command {
public:

	// Constructor.
	WC(std::string opt, std::string arg, std::string rdt, int rdtType, int batch, std::string prevOut, int first, int last);

	void run() override;

	// Not needed.
	std::string getNewSymbol() override;

	std::string getOutput() override;

	std::string getRedirection() override;

private:

	std::string readArg() override;

	// Not needed since output is an integer and not a string.
	void printToFile(std::string filename, int typeOfOutput, std::string outputText) override;

	// Determines whether it will be counting words or characters.
	std::string option;

	// The text where it will count either words or characters.
	std::string text;

	// Redirection for the output of the command.
	std::string redirection;

	// Type of redirection for the output of the command.
	int redirectionType;

	// Indicates whether it is read from a file during the batch command and if the batch redirection is required.
	int batchFlag;

	// The output from the previous command from the pipe.
	std::string previousOutput;

	// Indicates whether it is in the first part of the pipe.
	int firstPipe;

	// Indicates whether it is in the last part of the pipe or if there is no pipe.
	int lastPipe;

};
