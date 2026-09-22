#include "Interpreter.h"
#include "Parse.h"
#include "ParseBasic.h"
#include "ParseArg.h"
#include "ParseOptArg.h"
#include "ParseArgOpt.h"
#include "Command.h"
#include "Time.h"
#include "Date.h"
#include "Echo.h"
#include "Touch.h"
#include "WC.h"
#include "Truncate.h"
#include "RM.h"
#include "Prompt.h"
#include "Batch.h"
#include "Head.h"
#include "TR.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

Interpreter::Interpreter(int flag)
	:	symbol("$")
	,	batch(flag)
{}

std::vector<std::string> Interpreter::checkForPipe(std::string commandLine) {
	std::vector<std::string> commands;
	std::string tmp;
	bool inQuotes = false;
	for (char c : commandLine) {
		if (c == '"') inQuotes = !inQuotes;
		if (c == '|' && !inQuotes) {
			commands.push_back(tmp);
			tmp.clear();
		}
		else tmp += c;
	}
	commands.push_back(tmp);
	for (int i = 0; i < commands.size(); i++) if (i > 0 && commands[i].size() > 0) commands[i] = commands[i].substr(1);
	return commands;
}

int Interpreter::checkName(std::string name) {
	std::vector<std::string> commands = {"echo", "prompt", "time", "date", "touch", "truncate", "rm", "wc", "tr", "head", "batch"};

	for (std::string cmd : commands) {
		if (name == cmd) return -1;
	}

	int firstMistake = 0;
	for (std::string cmd : commands) {
		int i = 0;
		while (i < name.size() && i < cmd.size() && name[i] == cmd[i]) i++;
		if (i > firstMistake) firstMistake = i;
	}
	return firstMistake;
}

std::vector<std::string> Interpreter::makeList(std::string commandLine) {
	std::stringstream ss(commandLine);
	std::vector<std::string> list(2);
	
	ss >> list[0];
	// Checks if there has been an input.
	if (list[0].size() == 0) return std::vector<std::string>();
	// Checks if the name of the command entered is a an existing command.
	int firstMistake = checkName(list[0]);
	if (firstMistake != -1) {
		std::cout << "Error. Unknown command: " << list[0] << std::endl << commandLine << std::endl;
		for (int i = 0; i < firstMistake; i++) std::cout << " ";
		std::cout << "^" << std::endl;
		return std::vector<std::string>();
	}

	getline(ss, list[1]);
	// If the size of the string is greater than zero, it should ignore the first character since it is a whitespace.
	if (list[1].size() > 0) {
		std::string tmp = list[1].substr(1);
		list[1] = tmp;
	}
	return list;
}

Parse* Interpreter::parseList(std::vector<std::string> list, std::string commandLine) {
	Parse* p;
	if (list[0] == "time" || list[0] == "date") p = new ParseBasic();
	else if (list[0] == "echo" || list[0] == "touch" || list[0] == "truncate" || list[0] == "rm" || list[0] == "prompt" || list[0] == "batch") p = new ParseArg();
	else if (list[0] == "wc" || list[0] == "head") p = new ParseOptArg();
	// tr command only in this case.
	else p = new ParseArgOpt();
	p->parseString(list, commandLine);
	if (p->getFlag()) p = nullptr;
	return p;
}

Command* Interpreter::findCommand(Parse* p, std::string name, std::string opt, std::string arg, std::string rdt, int rdtType, std::string repl, std::string prevOut, int first, int last) {
	Command *com = nullptr;
	if (name == "time") com = new Time(rdt, rdtType, batch, last);
	else if (name == "date") com = new Date(rdt, rdtType, batch, last);
	else if (name == "echo") com = new Echo(arg, rdt, rdtType, batch, prevOut, first, last);
	else if (name == "touch") com = new Touch(arg);
	else if (name == "wc") com = new WC(opt, arg, rdt, rdtType, batch, prevOut, first, last);
	else if (name == "truncate") com = new Truncate(arg);
	else if (name == "rm") com = new RM(arg);
	else if (name == "prompt") com = new Prompt(arg, getSymbol());
	else if (name == "batch") com = new Batch(arg, rdt, rdtType, batch, last);
	else if (name == "head") com = new Head(opt, arg, rdt, rdtType, batch, prevOut, first, last);
	else com = new TR(opt, repl, arg, rdt, rdtType, batch, prevOut, first, last);
	return com;
}

void Interpreter::process(std::string commandLine) {
	// Checks to see if the command line is a pipe and splits each command if it is.
	std::vector<std::string> commands = checkForPipe(commandLine);

	// If this flag is activated, it means that it is no longer in the first pipe.
	int firstPipe = 0;
	// If this flag is activated, it means that it is the last pipe.
	int lastPipe = 0;

	for (int i = 0; i < commands.size(); i++) {
		if (i != 0) firstPipe = 1;
		if (i == commands.size() - 1) lastPipe = 1;
		commandLine = commands[i];

		// Splits the command line input into two different strings which will be parsed.
		std::vector<std::string> list = makeList(commandLine);
		if (list.empty()) return;

		// Parsing the command line.
		Parse* p = parseList(list, commandLine);
		if (!p) return;

		// Determining which command was entered.
		Command* com = findCommand(p, p->getName(), p->getOpt(), p->getArg(), p->getRedirection(), p->getRedirectionType(), p->getRepl(), output, firstPipe, lastPipe);
		com->run();
		// Changes the command prompt if the command name is prompt or if the prompt command shows up within the batch command file.
		if (p->getName() == "prompt" || (p->getName() == "batch" && com->getNewSymbol() != "$")) setSymbol(com->getNewSymbol());

		// Output and output redirection of the command is stored in the interpreter in case of redirection for the batch command.
		output = com->getOutput();
		redirection = com->getRedirection();

		delete com;
		delete p;
	}
}
