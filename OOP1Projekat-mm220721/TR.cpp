#include "TR.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>

#include <regex>

TR::TR(std::string opt, std::string repl, std::string arg, std::string rdt, int rdtType, int batch, std::string prevOut, int first, int last)
	:	original(opt)
	,	replacement(repl)
	,	text(arg)
	,	redirection(rdt)
	,	redirectionType(rdtType)
	,	batchFlag(batch)
	,	previousOutput(prevOut)
	,	firstPipe(first)
	,	lastPipe(last)
{}

void TR::run() {
	std::string tmp;
	int flag = 0;
	if (text.size() == 0) {
		if (firstPipe) text = previousOutput;
		else text = readArg();
		flag = 1;
	}

	if (flag == 0) {
		// Argument is a user inputed text with quotation marks.
		if (text.size() >= 2 && text.front() == '"' && text.back() == '"') {
			for (int i = 1; i < text.size() - 1; i++) tmp += text[i];
			text = tmp;
		}
		// Argument is the name of a file.
		else {
			std::ifstream file(text);
			if (!file) {
				std::cout << "An error has occurred with opening the file." << std::endl;
				return;
			}
			std::stringstream buffer;
			buffer << file.rdbuf();
			text = buffer.str();
			file.close();
		}
	}

	size_t position = 0;
	while ((position = text.find(original, position)) != std::string::npos) {
		text.replace(position, original.size(), replacement);
		if (!replacement.empty()) position += replacement.size();
	}

	output = text;
	if (redirection == "") {
		if (!batchFlag && lastPipe) std::cout << text << std::endl;
	}
	else {
		printToFile(redirection, redirectionType, output);
	}
}

std::string TR::getNewSymbol() {
	return "";
}

std::string TR::getOutput() {
	return output;
}

std::string TR::getRedirection() {
	return redirection;
}

std::string TR::readArg() {
	std::string input(std::istreambuf_iterator<char>(std::cin), {});
	if (!input.empty() && input.back() == '\n') input.pop_back();
	return input;
}

void TR::printToFile(std::string filename, int typeOfOutput, std::string outputText) {
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
