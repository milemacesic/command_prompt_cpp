#include "ParseOptArg.h"
#include "Parse.h"
#include "ParseWC.h"
#include "ParseHead.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>

void ParseOptArg::parseString(std::vector<std::string> list, std::string commandLine) {
	name = list[0], flag = 0, redirection = "", redirectionType = 0;

	Parse* p;
	if (name == "wc") p = new ParseWC();
	else p = new ParseHead();
	p->parseString(list, commandLine);
	opt = p->getOpt(), arg = p->getArg(), flag = p->getFlag(), redirection = p->getRedirection(), redirectionType = p->getRedirectionType();
	delete p;
}

std::string ParseOptArg::getName() {
	return name;
}

std::string ParseOptArg::getOpt() {
	return opt;
}

std::string ParseOptArg::getRepl() {
	return "";
}

std::string ParseOptArg::getArg() {
	return arg;
}

int ParseOptArg::getFlag() {
	return flag;
}

std::string ParseOptArg::getRedirection() {
	return redirection;
}

int ParseOptArg::getRedirectionType() {
	return redirectionType;
}

void ParseOptArg::checkForInputRedirection(std::string commandLine, std::istringstream& iss, std::string tmp, std::string& arg, int& flag) {
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

void ParseOptArg::checkForOutputRedirection(std::string commandLine, std::istringstream& iss, std::string tmp, std::string& redirection, int& redirectionType, int& flag) {
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

void ParseOptArg::printError(std::string commandLine, std::string error, size_t position, int& flag) {
	std::cout << error << std::endl << commandLine << std::endl;
	for (int i = 0; i < position; i++) std::cout << " ";
	std::cout << "^" << std::endl;
	flag = 1;
}
