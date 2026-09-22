#include "ParseCommandWithFile.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

void ParseCommandWithFile::parseString(std::vector<std::string> list, std::string commandLine) {
	name = list[0], opt = "", arg = "";
	flag = 0, redirection = "", redirectionType = 0;
	size_t position = 0;
	std::string tmp;

	std::istringstream iss(list[1]);
	iss >> tmp;

	// Potential input redirection.
	if (tmp.front() == '<') {
		checkForInputRedirection(commandLine, iss, tmp, arg, flag);
		if (flag) return;
	}
	// File name.
	else arg = tmp;

	// Check for additional inputs that are not required. It is an error if they exist.
	if (iss >> tmp) printError(commandLine, "Error. Invalid input:", commandLine.find(tmp), flag);
}

std::string ParseCommandWithFile::getName() {
	return name;
}

std::string ParseCommandWithFile::getOpt() {
	return "";
}

std::string ParseCommandWithFile::getArg() {
	return arg;
}

int ParseCommandWithFile::getFlag() {
	return flag;
}

std::string ParseCommandWithFile::getRedirection() {
	return "";
}

int ParseCommandWithFile::getRedirectionType() {
	return 0;
}
