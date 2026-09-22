#include "Prompt.h"
#include "Interpreter.h"
#include <iostream>
#include <string>
#include <iterator>
#include <fstream>

Prompt::Prompt(std::string arg, std::string symbol)
	:	text(arg)
	,	newSymbol(symbol)
{}

void Prompt::run() {
	if (text.size() >= 3 && text.front() == '"' && text.back() == '"') {
		newSymbol = text.substr(1, text.size() - 2);
	}
	else {
		std::ifstream file(text);
		if (!file) {
			std::cout << "An error has occured with opening the file." << std::endl;
			return;
		}
		std::string tmp((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		newSymbol = tmp;
		file.close();
	}
}

std::string Prompt::getNewSymbol() {
	return newSymbol;
}

std::string Prompt::getOutput() {
	return "";
}

std::string Prompt::getRedirection() {
	return "";
}

std::string Prompt::readArg() {
	return "";
}

void Prompt::printToFile(std::string filename, int typeOfOutput, std::string outputText) {
	return;
}
