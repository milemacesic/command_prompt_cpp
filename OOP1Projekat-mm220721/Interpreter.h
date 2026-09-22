#pragma once
#include <string>
#include <vector>
#include "Parse.h"
#include "Command.h"

class Interpreter {
public:

	// Constructor.
	Interpreter(int flag);

	// Destructor.
	~Interpreter() {};

	// Proceeds with the user entered command line and it processes the command entered.
	void process(std::string commandLine);

	// Returns the symbol that represents the command prompt.
	std::string getSymbol();

	// Sets the symbol that represents the command prompt.
	void setSymbol(std::string newSymbol);

	// Returns the output of the command.
	std::string getOutput();

	// Returns the output redirection of the command.
	std::string getRedirection();

private:

	// Checks to see if the command line is a pipe.
	std::vector<std::string> checkForPipe(std::string commandLine);

	// Checks if the name of the command entered is a valid and existing command.
	int checkName(std::string name);

	// Converts the entered command line into a list of strings.
	std::vector<std::string> makeList(std::string commandLine);

	// Parses the list of strings.
	Parse* parseList(std::vector<std::string> list, std::string commandLine);

	// Determines which command will be used based on the name of the command.
	Command* findCommand(Parse *p, std::string name, std::string opt, std::string arg, std::string rdt, int rdtType, std::string repl, std::string prevOut, int first, int last);

	// Command prompt. Starting symbol is $ but it can be changed.
	std::string symbol;

	// Indicates if the interpreter was created within the batch command and if the batch command itself has an output redireciton.
	int batch;

	// The output of the command which can also be written in the output redirection if needed. It is also used to help with pipes.
	std::string output;

	// The output redirection of the command which will be used to help with the output redirection of the batch command.
	std::string redirection;

};

inline std::string Interpreter::getSymbol() {
	return symbol;
}

inline void Interpreter::setSymbol(std::string newSymbol) {
	symbol = newSymbol;
}

inline std::string Interpreter::getOutput() {
	return output;
}

inline std::string Interpreter::getRedirection() {
	return redirection;
}
