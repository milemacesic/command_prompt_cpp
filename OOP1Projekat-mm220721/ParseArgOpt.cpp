#include "ParseArgOpt.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

void ParseArgOpt::parseString(std::vector<std::string> list, std::string commandLine) {
	name = list[0], flag = 0, redirection = "", redirectionType = 0;
	arg = "", opt = "", repl = "";
	
	// In this case the only command is tr, so it can be parsed in this method without creating a new object of the derived class.
	if (name == "tr") {
		std::string tmp;
		size_t position = 0, first = 0, second = 0;

		// There is no input after 'tr'.
		if (list[1].size() == 0) {
			printError(commandLine, "Error. Invalid input:", name.size() + 1, flag);
			return;
		}

		std::istringstream iss(list[1]);
		iss >> tmp;

		// Argument starts with quotation marks.
		if (tmp.front() == '"') {
			first = commandLine.find('"');
			second = commandLine.find('"', first + 1);
			// Argument does not end with quotation marks, therefore an error.
			if (second == std::string::npos) {
				printError(commandLine, "Error. Invalid input for argument:", commandLine.size(), flag);
				return;
			}
			arg = commandLine.substr(first, second - first + 1);

			while (tmp.back() != '"') iss >> tmp;
			// Potential -what.
			if (iss >> tmp) {
				// Potential -what.
				if (tmp.front() == '-' && tmp != "-") {
					first = commandLine.find('"', second + 1);
					second = commandLine.find('"', first + 1);
					// Argument does not end with quotation marks, therefore an error.
					if (second == std::string::npos) {
						printError(commandLine, "Error. Invalid input for argument:", commandLine.size(), flag);
						return;
					}
					opt = commandLine.substr(first, second - first + 1);
					opt = opt.substr(1);
					opt.pop_back();

					if (opt == " ") iss >> tmp;
					else while (tmp.back() != '"') iss >> tmp;
					if (iss >> tmp) {
						// Potential with.
						if (tmp.front() == '"') {
							first = commandLine.find('"', second + 1);
							second = commandLine.find('"', first + 1);
							// Argument does not end with quotation marks, therefore an error.
							if (second == std::string::npos) {
								printError(commandLine, "Error. Invalid input for argument:", commandLine.size(), flag);
								return;
							}
							repl = commandLine.substr(first, second - first + 1);
							repl = repl.substr(1);
							repl.pop_back();

							while (tmp.back() != '"') iss >> tmp;
							// Check for additional input.
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
						// Potential output redirection.
						else if (tmp.front() == '>') {
							checkForOutputRedirection(commandLine, iss, tmp, redirection, redirectionType, flag);
							if (flag) return;
						}
						// Error.
						else {
							printError(commandLine, "Error. Invalid input:", commandLine.find(tmp), flag);
							return;
						}
					}
					else return;
				}
				// Error.
				else {
					if (tmp != "-") position = commandLine.find(tmp);
					else position = commandLine.find(tmp) + 1;
					printError(commandLine, "Error. Invalid input:", position, flag);
					return;
				}
			}
			// Error.
			else {
				printError(commandLine, "Error. Invalid input:", commandLine.size(), flag);
				return;
			}
		}
		// Potential '-what'.
		else if (tmp.front() == '-' && tmp != "-") {
			first = commandLine.find('"');
			second = commandLine.find('"', first + 1);
			// Argument does not end with quotation marks, therefore an error.
			if (second == std::string::npos) {
				printError(commandLine, "Error. Invalid input for argument:", commandLine.size(), flag);
				return;
			}
			opt = commandLine.substr(first, second - first + 1);
			opt = opt.substr(1);
			opt.pop_back();

			if (opt == " ") iss >> tmp;
			else while (tmp.back() != '"') iss >> tmp;
			if (iss >> tmp) {
				// Potential with.
				if (tmp.front() == '"') {
					first = commandLine.find('"', second + 1);
					second = commandLine.find('"', first + 1);
					// Argument does not end with quotation marks, therefore an error.
					if (second == std::string::npos) {
						printError(commandLine, "Error. Invalid input for argument:", commandLine.size(), flag);
						return;
					}
					repl = commandLine.substr(first, second - first + 1);
					repl = repl.substr(1);
					repl.pop_back();

					while (tmp.back() != '"') iss >> tmp;
					// Check for additional input.
					if (iss >> tmp) {
						// Potential output redirection.
						if (tmp.front() == '>') {
							checkForOutputRedirection(commandLine, iss, tmp, redirection, redirectionType, flag);
							if (flag) return;

							// Check for potential input redirection or error.
							if (iss >> tmp) {
								// Input redirection.
								if (tmp.front() == '<') {
									checkForInputRedirection(commandLine, iss, tmp, arg, flag);
									if (flag) return;
								}
								// Error.
								else {
									printError(commandLine, "Error. Invalid input:", commandLine.find(tmp), flag);
									return;
								}
							}
							else return;
						}
						// Potential input redirection.
						else if (tmp.front() == '<') {
							checkForInputRedirection(commandLine, iss, tmp, arg, flag);
							if (flag) return;

							// Check for potential output redirection or error.
							if (iss >> tmp) { 
								// Output redirection.
								if (tmp.front() == '<') {
									checkForOutputRedirection(commandLine, iss, tmp, redirection, redirectionType, flag);
									if (flag) return;
								}
								// Error.
								else {
									printError(commandLine, "Error. Invalid input:", commandLine.find(tmp), flag);
									return;
								}
							}
							else return;
						}
						// Error.
						else {
							printError(commandLine, "Error. Invalid input:", commandLine.find(tmp), flag);
							return;
						}
					}
					else return;
				}
				// Potential output redirection.
				else if (tmp.front() == '>') {
					checkForOutputRedirection(commandLine, iss, tmp, redirection, redirectionType, flag);
					if (flag) return;

					// Check for potential input redirection or error.
					if (iss >> tmp) {
						// Input redirection.
						if (tmp.front() == '<') {
							checkForInputRedirection(commandLine, iss, tmp, arg, flag);
							if (flag) return;
						}
						// Error.
						else {
							printError(commandLine, "Error. Invalid input:", commandLine.find(tmp), flag);
							return;
						}
					}
					else return;
				}
				// Potential input redirection.
				else if (tmp.front() == '<') {
					checkForInputRedirection(commandLine, iss, tmp, arg, flag);
					if (flag) return;

					// Check for potential output redirection or error.
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
					else return;
				}
				// Error.
				else {
					printError(commandLine, "Error. Invalid input:", commandLine.find(tmp), flag);
					return;
				}
			}
			else return;
		}
		// File name.
		else {
			arg = tmp;
			if (iss >> tmp) {
				// Potential -what.
				if (tmp.front() == '-' && tmp != "-") {
					first = commandLine.find('"');
					second = commandLine.find('"', first + 1);
					// Argument does not end with quotation marks, therefore an error.
					if (second == std::string::npos) {
						printError(commandLine, "Error. Invalid input for argument:", commandLine.size(), flag);
						return;
					}
					opt = commandLine.substr(first, second - first + 1);
					opt = opt.substr(1);
					opt.pop_back();

					if (opt == " ") iss >> tmp;
					else while (tmp.back() != '"') iss >> tmp;
					// Check for additional input.
					if (iss >> tmp) {
						// Potential with.
						if (tmp.front() == '"') {
							first = commandLine.find('"', second + 1);
							second = commandLine.find('"', first + 1);
							// Argument does not end with quotation marks, therefore an error.
							if (second == std::string::npos) {
								printError(commandLine, "Error. Invalid input for argument:", commandLine.size(), flag);
								return;
							}
							repl = commandLine.substr(first, second - first + 1);
							repl = repl.substr(1);
							repl.pop_back();

							while (tmp.back() != '"') iss >> tmp;
							// Check for additional input.
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
							else return;
						}
						// Potential output redireciton.
						else if (tmp.front() == '>') {
							checkForOutputRedirection(commandLine, iss, tmp, redirection, redirectionType, flag);
							if (flag) return;
						}
						// Error.
						else {
							printError(commandLine, "Error. Invalid input:", commandLine.find(tmp), flag);
							return;
						}
					}
					else return;
				}
				// Error.
				else {
					printError(commandLine, "Error. Invalid input:", commandLine.find(tmp), flag);
					return;
				}
			}
			// Error. There is no -what after the file name.
			else {
				printError(commandLine, "Error. There is no indication of which part of the text will be replaced:", commandLine.find(tmp) + tmp.size(), flag);
				return;
			}
		}

		// Check for additional inputs that are not required. It is an error if they exist.
		if (iss >> tmp) printError(commandLine, "Error. Invalid input:", commandLine.find(tmp), flag);
	}
}

std::string ParseArgOpt::getName() {
	return name;
}

std::string ParseArgOpt::getOpt() {
	return opt;
}

std::string ParseArgOpt::getRepl() {
	return repl;
}

std::string ParseArgOpt::getArg() {
	return arg;
}

int ParseArgOpt::getFlag() {
	return flag;
}

std::string ParseArgOpt::getRedirection() {
	return redirection;
}

int ParseArgOpt::getRedirectionType() {
	return redirectionType;
}

void ParseArgOpt::checkForInputRedirection(std::string commandLine, std::istringstream& iss, std::string tmp, std::string& arg, int& flag) {
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

void ParseArgOpt::checkForOutputRedirection(std::string commandLine, std::istringstream& iss, std::string tmp, std::string& redirection, int& redirectionType, int& flag) {
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

void ParseArgOpt::printError(std::string commandLine, std::string error, size_t position, int& flag) {
	std::cout << error << std::endl << commandLine << std::endl;
	for (int i = 0; i < position; i++) std::cout << " ";
	std::cout << "^" << std::endl;
	flag = 1;
}
