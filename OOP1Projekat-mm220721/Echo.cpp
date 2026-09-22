#include "Echo.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>

Echo::Echo(std::string arg, std::string rdt, int rdtType, int batch, std::string prevOut, int first, int last)
	:	text(arg)
	,	redirection(rdt)
	,	redirectionType(rdtType)
	,	batchFlag(batch)
	,	previousOutput(prevOut)
	,	firstPipe(first)
	,	lastPipe(last)
{}

void Echo::run() {
	int flag = 0;
	// If the flag is activated, then the input was not done on the first line where the name of the command was. Therefore it will treat the argument as a normal string.
	if (text.size() == 0) {
		if (firstPipe) text = previousOutput;
		else text = readArg();
		flag = 1;
	}

	if (flag == 0) {
		// Argument is a user inputed text with quotations marks.
		if (text.size() >= 2 && text.front() == '"' && text.back() == '"') {
			if (redirection == "") {
				if (!batchFlag && lastPipe) {
					for (int i = 1; i < text.size() - 1; i++) std::cout << text[i];
					std::cout << std::endl;
				}
				output = text.substr(1, text.size() - 2);
			}
			else {
				std::string tmp = text.substr(1);
				tmp.pop_back();
				printToFile(redirection, redirectionType, tmp);
				output = tmp;
			}
		}
		// Argument is the name of a file.
		else {
			std::ifstream file(text);
			if (!file) {
				std::cout << "An error has occurred with opening the file." << std::endl;
				return;
			}
			std::string line;
			output = "";
			while (std::getline(file, line)) {
				if (redirection == "") {
					if (!batchFlag && lastPipe) std::cout << line << std::endl;
				}
				else printToFile(redirection, redirectionType, line);
				output += line;
			}
			file.close();
		}
	}
	// Argument is a normal string.
	else {
		if (redirection == "") {
			if (!batchFlag && lastPipe) std::cout << text << std::endl;
		}
		else printToFile(redirection, redirectionType, text);
		output = text;
	}
}

std::string Echo::getNewSymbol() {
	return "";
}

std::string Echo::getOutput() {
	return output;
}

std::string Echo::getRedirection() {
	return redirection;
}

std::string Echo::readArg() {
	std::string input(std::istreambuf_iterator<char>(std::cin), {});
	if (!input.empty() && input.back() == '\n') input.pop_back();
	return input;
}

void Echo::printToFile(std::string filename, int typeOfOutput, std::string outputText) {
	if (typeOfOutput) {
		std::ofstream rdtFile(filename, std::ios::app);
		if (!rdtFile) {
			std::cout << "An error has occured with opening the file." << std::endl;
			return;
		}
		rdtFile << outputText;
		rdtFile.close();
	}
	else {
		std::ofstream rdtFile(filename);
		if (!rdtFile) {
			std::cout << "An error has occured with opening the file." << std::endl;
			return;
		}
		rdtFile << outputText;
		rdtFile.close();
	}
}
