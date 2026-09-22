#pragma once
#include "Command.h"
#include <string>
// Derived Class from Command:

class Echo : public Command {
public:

	// Constructor.
	Echo(std::string arg, std::string rdt, int rdtType, int batch, std::string prevOut, int first, int last);

	void run() override;

	// Not needed.
	std::string getNewSymbol() override;

	std::string getOutput() override;

	std::string getRedirection() override;

private:

	std::string readArg() override;

	void printToFile(std::string filename, int typeOfOutput, std::string outputText) override;

	// User inputed text for the command.
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
