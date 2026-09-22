#include "ParseArg.h"
#include "Parse.h"
#include "ParseEcho.h"
#include "ParsePrompt.h"
#include "ParseBatch.h"
#include "ParseCommandWithFile.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

void ParseArg::parseString(std::vector<std::string> list, std::string commandLine) {
	name = list[0], flag = 0, redirection = "", redirectionType = 0, arg = list[1];

	Parse *p;
	if (name == "echo") p = new ParseEcho();
	else {
		if (arg.size() == 0) {
			std::string error = "Error. There is no argument given for the " + name + " command:";
			printError(commandLine, error, name.size() + 1, flag);
			return;
		}
		if (name == "prompt") p = new ParsePrompt();
		else if (name == "batch") p = new ParseBatch();
		// This is for the following commands: touch, truncate, rm.
		else p = new ParseCommandWithFile();
	}
	p->parseString(list, commandLine);
	arg = p->getArg(), flag = p->getFlag(), redirection = p->getRedirection(), redirectionType = p->getRedirectionType();
	delete p;
}

std::string ParseArg::getName() {
	return name;
}

std::string ParseArg::getOpt() {
	return "";
}

std::string ParseArg::getRepl() {
	return "";
}

std::string ParseArg::getArg() {
	return arg;
}

int ParseArg::getFlag() {
	return flag;
}

std::string ParseArg::getRedirection() {
	return redirection;
}

int ParseArg::getRedirectionType() {
	return redirectionType;
}

void ParseArg::checkForInputRedirection(std::string commandLine, std::istringstream& iss, std::string tmp, std::string& arg, int& flag) {
	// Input redirection with space(s).
	if (tmp == "<") {
		if (!(iss >> arg)) {
			printError(commandLine, "Error. There is no file name for the input redirection:", commandLine.find(tmp) + 1, flag);
			return;
		}
	}
	// Input redirection with no space(s).
	else arg = tmp.substr(1);
}

void ParseArg::checkForOutputRedirection(std::string commandLine, std::istringstream& iss, std::string tmp, std::string& redirection, int& redirectionType, int& flag) {
	// Output redirection with '>' and with space(s).
	if (tmp == ">") {
		if (!(iss >> redirection)) {
			printError(commandLine, "Error. There is no file name for the output redirection:", commandLine.find(tmp) + 1, flag);
			return;
		}
	}
	// Output redirection with '>>' and with space(s).
	else if (tmp == ">>") {
		if (!(iss >> redirection)) {
			printError(commandLine, "Error. There is no file name for the output redirection:", commandLine.find(tmp) + 2, flag);
			return;
		}
		redirectionType = 1;
	}
	// Output redirection with '>>' and with no space(s).
	else if (tmp != ">>" && tmp[1] == '>') {
		redirection = tmp.substr(2);
		redirectionType = 1;
		if (redirection == "") {
			printError(commandLine, "Error. There is no file name for the output redirection:", commandLine.find(tmp) + 2, flag);
			return;
		}
	}
	// Output redirection with '>' and with no space(s).
	else redirection = tmp.substr(1);
}

void ParseArg::printError(std::string commandLine, std::string error, size_t position, int& flag) {
	std::cout << error << std::endl << commandLine << std::endl;
	for (int i = 0; i < position; i++) std::cout << " ";
	std::cout << "^" << std::endl;
	flag = 1;
}
