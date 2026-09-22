#include "ParseEcho.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

void ParseEcho::parseString(std::vector<std::string> list, std::string commandLine) {
    name = list[0], opt = "", arg = "";
    flag = 0, redirection = "", redirectionType = 0;
    std::string tmp;
    size_t position = 0;

    std::istringstream iss(list[1]);
    // There is no argument.
    if (!(iss >> tmp)) return;
    else {
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
			if (iss >> tmp) {
				// Potential output redirection or error.
				if (tmp.front() == '>') {
					checkForOutputRedirection(commandLine, iss, tmp, redirection, redirectionType, flag);
					if (flag) return;
				}
				else {
					printError(commandLine, "Error. Invalid input:", commandLine.find(tmp), flag);
					return;
				}
			}
		}
		// Potential input redirection.
		else if (tmp.front() == '<') {
			checkForInputRedirection(commandLine, iss, tmp, arg, flag);
			if (flag) return;

			// Check for potential output redirection or error.
			if (iss >> tmp) {
				if (tmp.front() == '>') {
					checkForOutputRedirection(commandLine, iss, tmp, redirection, redirectionType, flag);
					if (flag) return;
				}
				else {
					printError(commandLine, "Error. Invalid input:", commandLine.find(tmp), flag);
					return;
				}
			}
		}
		// Potential output redirection.
		else if (tmp.front() == '>') {
			checkForOutputRedirection(commandLine, iss, tmp, redirection, redirectionType, flag);
			if (flag) return;

			// Check for potential input redirection or error.
			if (iss >> tmp) {
				if (tmp.front() == '<') {
					checkForInputRedirection(commandLine, iss, tmp, arg, flag);
					if (flag) return;
				}
				else {
					printError(commandLine, "Error. Invalid input:", commandLine.find(tmp), flag);
					return;
				}
			}
		}
		// File name.
		else {
			arg = tmp;
			// Check for potential output redirection or error.
			if (iss >> tmp) {
				// Potential output redirection.
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
	}

	// Check for additional inputs that are not required. It is an error if they exist.
	if (iss >> tmp) printError(commandLine, "Error. Invalid input:", commandLine.find(tmp), flag);
}

std::string ParseEcho::getName() {
    return name;
}

std::string ParseEcho::getOpt() {
    return "";
}

std::string ParseEcho::getArg() {
    return arg;
}

int ParseEcho::getFlag() {
    return flag;
}

std::string ParseEcho::getRedirection() {
    return redirection;
}

int ParseEcho::getRedirectionType() {
    return redirectionType;
}
