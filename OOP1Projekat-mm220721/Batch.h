#pragma once
#include "Command.h"
#include <string>
// Derived Class from Command:

class Batch : public Command {
public:

	// Constructor.
	Batch(std::string arg, std::string rdt, int rdtType, int batch, int last);

	void run() override;

	// Not needed.
	std::string getNewSymbol() override;

	std::string getOutput() override;

	std::string getRedirection() override;

private:

	// Not needed.
	std::string readArg() override;

	void printToFile(std::string filename, int typeOfOutput, std::string outputText) override;

	// Name of the file that will be opened. Error if the file already exists.
	std::string filename;

	// Redirection for the output of the command.
	std::string redirection;

	// Type of redirection for the output of the command.
	int redirectionType;

	// Potential new symbol for the command prompt if the command prompt appears within the file.
	std::string newSymbol;

	// Indicates whether it is read from a file during the batch command and if the batch redirection is required.
	int batchFlag;

	// Indicates whether it is in the last part of the pipe or if there is no pipe.
	int pipe;

};
