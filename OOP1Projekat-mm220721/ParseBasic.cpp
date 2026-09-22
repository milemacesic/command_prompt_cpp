#include "ParseBasic.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

void ParseBasic::parseString(std::vector<std::string> list, std::string commandLine) {
	name = list[0], flag = 0, redirection = "", redirectionType = 0;
	std::string tmp;
	size_t position = 0;

	std::istringstream iss(list[1]);
	// There is no output redirection.
	if (!(iss >> tmp)) return;
	else {
		// Potential output redirection.
		if (tmp.front() == '>') {
			checkForOutputRedirection(commandLine, iss, tmp, redirection, redirectionType, flag);
			if (flag) return;
		}
		// Error.
		else {
			printError(commandLine, "Error. Invalid input:", name.size() + 1, flag);
			return;
		}
	}

	// Check for additional inputs that are not required. It is an error if they exist.
	if (iss >> tmp) printError(commandLine, "Error. Invalid input:", commandLine.find(tmp), flag);
}

std::string ParseBasic::getName() {
	return name;
}

std::string ParseBasic::getOpt() {
	return "";
}

std::string ParseBasic::getRepl() {
	return "";
}

std::string ParseBasic::getArg() {
	return "";
}

int ParseBasic::getFlag() {
	return flag;
}

std::string ParseBasic::getRedirection() {
	return redirection;
}

int ParseBasic::getRedirectionType() {
	return redirectionType;
}

void ParseBasic::checkForInputRedirection(std::string commandLine, std::istringstream& iss, std::string tmp, std::string& arg, int& flag) {
	return;
}

void ParseBasic::checkForOutputRedirection(std::string commandLine, std::istringstream& iss, std::string tmp, std::string& redirection, int& redirectionType, int& flag) {
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

void ParseBasic::printError(std::string commandLine, std::string error, size_t position, int& flag) {
	std::cout << error << std::endl << commandLine << std::endl;
	for (int i = 0; i < position; i++) std::cout << " ";
	std::cout << "^" << std::endl;
	flag = 1;
}
