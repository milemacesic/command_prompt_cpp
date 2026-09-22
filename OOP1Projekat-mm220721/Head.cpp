#include "Head.h"
#include <iostream>
#include <string>
#include <iterator>
#include <fstream>
#include <sstream>

Head::Head(std::string opt, std::string arg, std::string rdt, int rdtType, int batch, std::string prevOut, int first, int last)
	:	option(opt)
	,	text(arg)
	,	redirection(rdt)
	,	redirectionType(rdtType)
	,	batchFlag(batch)
	,	previousOutput(prevOut)
	,	firstPipe(first)
	,	lastPipe(last)
{}

void Head::run() {
	std::string tmp;
	int flag = 0;
	// If the flag is activated, then the input was not done on the first line where the name of the command was. Therefore it will treat the argument as a normal string.
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

	output = "";
	int number = std::stoi(option), cnt = 0;
	size_t position = 0, start = 0;
	while (cnt < number) {
		position = text.find('\n', start);
		if (position == std::string::npos) {
			if (redirection == "") {
				if (!batchFlag && lastPipe) std::cout << text.substr(start) << std::endl;
			}
			output += text.substr(start);
			break;
		}
		if (redirection == "") {
			if (!batchFlag && lastPipe) std::cout << text.substr(start, position - start) << std::endl;
		}
		output += text.substr(start, position - start);
		if (cnt + 1 != number) output += '\n';
		start = position + 1;
		cnt++;
	}
	if (redirection != "") printToFile(redirection, redirectionType, output);
}

std::string Head::getNewSymbol() {
	return "";
}

std::string Head::getOutput() {
	return output;
}

std::string Head::getRedirection() {
	return redirection;
}

std::string Head::readArg() {
	std::string input(std::istreambuf_iterator<char>(std::cin), {});
	if (!input.empty() && input.back() == '\n') input.pop_back();
	return input;
}

void Head::printToFile(std::string filename, int typeOfOutput, std::string outputText) {
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
