#include "ParsePrompt.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

void ParsePrompt::parseString(std::vector<std::string> list, std::string commandLine) {
	name = list[0], opt = "", arg = "";
	flag = 0, redirection = "", redirectionType = 0;
	size_t position = 0;
	std::string tmp;

	std::istringstream iss(list[1]);
	iss >> tmp;

	// Argument starts with a quotation mark.
	if (tmp.front() == '"') {
		size_t first = commandLine.find('"');
		size_t second = commandLine.find('"', first + 1);
		// Argument does not end with quotation marks, therefore an error.
		if (second == std::string::npos) {
			printError(commandLine, "Error. Invalid input for argument:", commandLine.size(), flag);
			return;
		}
		arg = commandLine.substr(first, second - first + 1);
		while (tmp.back() != '"') iss >> tmp;
	}
	// Potential input redirection.
	else if (tmp.front() == '<') {
		checkForInputRedirection(commandLine, iss, tmp, arg, flag);
		if (flag) return;
	}
	// File name.
	else arg = tmp;

	// Check for additional inputs that are not required. It is an error if they exist.
	if (iss >> tmp) printError(commandLine, "Error. Invalid input:", commandLine.find(tmp), flag);
}

std::string ParsePrompt::getName() {
	return name;
}

std::string ParsePrompt::getOpt() {
	return "";
}

std::string ParsePrompt::getArg() {
	return arg;
}

int ParsePrompt::getFlag() {
	return flag;
}

std::string ParsePrompt::getRedirection() {
	return "";
}

int ParsePrompt::getRedirectionType() {
	return 0;
}
