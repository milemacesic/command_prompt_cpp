#pragma once
#include "Command.h"
#include <string>
// Derived Class from Command:

class TR : public Command {
public:

	// Constructor.
	TR(std::string opt, std::string repl, std::string arg, std::string rdt, int rdtType, int batch, std::string prevOut, int first, int last);

	void run() override;

	// Not needed.
	std::string getNewSymbol() override;

	std::string getOutput() override;

	std::string getRedirection() override;

private:

	std::string readArg() override;

	void printToFile(std::string filename, int typeOfOutput, std::string outputText) override;

	// Part of a string that will be replaced in the argument.
	std::string original;

	// The string that will replace the original string in the argument.
	std::string replacement;

	// The argument of the string that contains either a file name or the string itself.
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
