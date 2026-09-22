#pragma once
#include <string>
// Abstract Class:

class Command {
public:

	// Destructor.
	virtual ~Command() {};

	// Abstract method. The derived classes will use this method to proceed with their respective command.
	virtual void run() = 0;

	// Abstract method. It returns the new symbol for the command prompt. This will only be used for the prompt and batch commands.
	virtual std::string getNewSymbol() = 0;

	// Abstract method. It returns the output for the command.
	virtual std::string getOutput() = 0;

	// Abstract method. It returns the output redirection of the command.
	virtual std::string getRedirection() = 0;

protected:

	// Abstract method. It reads the user input until it has detected EOF (Ctrl + Z). In this case it reads the input for the argument of the command.
	virtual std::string readArg() = 0;

	// Abstract method. If there is an output redirection, it will print the output of the command to the following file.
	virtual void printToFile(std::string filename, int typeOfOutput, std::string outputText) = 0;
	
	// The name of the command.
	std::string name;

	// The output of the command.
	std::string output;

};
