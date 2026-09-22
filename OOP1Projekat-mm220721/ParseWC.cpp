#include "ParseWC.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

void ParseWC::parseString(std::vector<std::string> list, std::string commandLine) {
	name = list[0], opt = "", arg = "";
	flag = 0, redirection = "", redirectionType = 0;
	std::string tmp;
	size_t position = 0;
	std::vector<std::string> options = {"-c", "-w"};

	std::istringstream iss(list[1]);
	// There is no option for the command.
	if (!(iss >> opt)) {
		std::string error = "Error. There is no option given for the " + name + " command:";
		printError(commandLine, error, name.size() + 1, flag);
		return;
	}
	// Potential option or error.
	else {
		if (opt != "-w" && opt != "-c") {
			for (std::string str : options) {
				int i = 0;
				while (i < opt.size() && i < str.size() && opt[i] == str[i]) i++;
				if (i > position) position = i;
			}
			printError(commandLine, "Error. Invalid option:", name.size() + position + 1, flag);
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

std::string ParseWC::getName() {
	return name;
}

std::string ParseWC::getOpt() {
	return opt;
}

std::string ParseWC::getArg() {
	return arg;
}

int ParseWC::getFlag() {
	return flag;
}

std::string ParseWC::getRedirection() {
	return redirection;
}

int ParseWC::getRedirectionType() {
	return redirectionType;
}
