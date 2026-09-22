#include "ParseHead.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cctype>

void ParseHead::parseString(std::vector<std::string> list, std::string commandLine) {
	name = list[0], opt = "", arg = "";
	flag = 0, redirection = "", redirectionType = 0;
	std::string tmp;
	size_t position = 0;

	std::istringstream iss(list[1]);
	// There is no option for the command.
	if (!(iss >> opt)) {
		std::string error = "Error. There is no option given for the " + name + " command:";
		printError(commandLine, error, name.size() + 1, flag);
		return;
	}
	// Potential option or error.
	else {
		// Checks to see if the option starts with '-'.
		if (opt.front() == '-') {
			opt = opt.substr(1);
			if (opt.front() == 'n') {
				opt = opt.substr(1);
				for (int i = 0; i < opt.size(); i++) {
					tmp += opt[i];
					if (!(isdigit(tmp[i]))) {
						printError(commandLine, "Error. Not a number:", name.size() + 2 + i, flag);
						return;
					}
				}
				try {
					int check = std::stoi(tmp);
					if (check > 99999) {
						printError(commandLine, "Error. Number is too high:", name.size() + opt.size(), flag);
						return;
					}
				}
				catch (std::invalid_argument&) {
					printError(commandLine, "Error. Not a number:", name.size() + 2, flag);
					return;
				}
			}
			else {
				printError(commandLine, "Error. Invalid option:", name.size() + 1, flag);
				return;
			}
		}
		else {
			printError(commandLine, "Error. Invalid option:", name.size(), flag);
			return;
		}
	}

	// Checks to see if there is no input after option.
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
	}

	// Check for additional inputs that are not required. It is an error if they exist.
	if (iss >> tmp) printError(commandLine, "Error. Invalid input:", commandLine.find(tmp), flag);
}

std::string ParseHead::getName() {
	return name;
}

std::string ParseHead::getOpt() {
	return opt;
}

std::string ParseHead::getArg() {
	return arg;
}

int ParseHead::getFlag() {
	return flag;
}

std::string ParseHead::getRedirection() {
	return redirection;
}

int ParseHead::getRedirectionType() {
	return redirectionType;
}
