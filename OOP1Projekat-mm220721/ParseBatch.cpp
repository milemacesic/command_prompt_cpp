#include "ParseBatch.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

void ParseBatch::parseString(std::vector<std::string> list, std::string commandLine) {
	name = list[0], opt = "", arg = "";
	flag = 0, redirection = "", redirectionType = 0;
	size_t position = 0;
	std::string tmp;

	std::istringstream iss(list[1]);
	iss >> tmp;

	// Input redirection.
	if (tmp.front() == '<') {
		checkForInputRedirection(commandLine, iss, tmp, arg, flag);
		if (flag) return;

		// Check for potential output redirection.
		if (iss >> tmp) {
			// Output redirection.
			if (tmp.front() == '>') {
				checkForOutputRedirection(commandLine, iss, tmp, redirection, redirectionType, flag);
				if (flag) return;
			}
			// Error.
			else {
				printError(commandLine, "Error. Invalid input:", commandLine.find(tmp), flag);
				return;
			}
		}
	}
	// Output redirection.
	else if (tmp.front() == '>') {
		checkForOutputRedirection(commandLine, iss, tmp, redirection, redirectionType, flag);
		if (flag) return;

		// Input redirection is needed or else it is an error.
		if (iss >> tmp) {
			// Input redirection.
			if (tmp.front() == '<') {
				checkForInputRedirection(commandLine, iss, tmp, arg, flag);
				if (flag) return;
			}
			// Error.
			else {
				printError(commandLine, "Error. Invalid input", commandLine.find(tmp), flag);
				return;
			}
		}
		// Error.
		else {
			printError(commandLine, "Error. There is no input redirection:", commandLine.find(tmp), flag);
			return;
		}
	}
	// File name.
	else {
		arg = tmp;
		// Check for potential output redirection.
		if (iss >> tmp) {
			// Output redirection.
			if (tmp.front() == '>') {
				checkForOutputRedirection(commandLine, iss, tmp, redirection, redirectionType, flag);
				if (flag) return;
			}
			// Error.
			else {
				printError(commandLine, "Error. Invalid input:", commandLine.find(tmp), flag);
				return;
			}
		}
	}

	// Check for additional inputs that are not required. It is an error if they exist.
	if (iss >> tmp) printError(commandLine, "Error. Invalid input:", commandLine.find(tmp), flag);
}

std::string ParseBatch::getName() {
	return name;
}

std::string ParseBatch::getOpt() {
	return "";
}

std::string ParseBatch::getArg() {
	return arg;
}

int ParseBatch::getFlag() {
	return flag;
}

std::string ParseBatch::getRedirection() {
	return redirection;
}

int ParseBatch::getRedirectionType() {
	return redirectionType;
}
