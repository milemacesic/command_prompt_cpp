#include "WC.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>

WC::WC(std::string opt, std::string arg, std::string rdt, int rdtType, int batch, std::string prevOut, int first, int last) 
	:	option(opt)
	,	text(arg)
	,	redirection(rdt)
	,	redirectionType(rdtType)
	,	batchFlag(batch)
	,	previousOutput(prevOut)
	,	firstPipe(first)
	,	lastPipe(last)
{}

void WC::run() {
	std::string tmp;
	int flag = 0, cnt = 0;
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

			if (option == "-w") {
				std::string word;
				while (file >> word) cnt++;
			}
			else if (option == "-c") {
				char c;
				while (file.get(c)) cnt++;
			}
		
			if (redirection == "") {
				if (!batchFlag && lastPipe) std::cout << cnt << std::endl;
			}
			else {
				if (redirectionType) {
					std::ofstream rdtFile(redirection, std::ios::app);
					if (!rdtFile) {
						std::cout << "An error has occured with opening the file." << std::endl;
						return;
					}
					rdtFile << cnt;
					rdtFile.close();
				}
				else {
					std::ofstream rdtFile(redirection);
					if (!rdtFile) {
						std::cout << "An error has occured with opening the file." << std::endl;
						return;
					}
					rdtFile << cnt;
					rdtFile.close();
				}
			}
			file.close();
			return;
		}
	}
	
	std::stringstream ss(text);
	if (option == "-w") {
		while (ss >> text) cnt++;
	}
	else if (option == "-c") {
		if (flag == 0) cnt = text.size();
		else {
			if (lastPipe && !firstPipe) cnt = text.size() + 1;
			else cnt = text.size();
		}
	}

	if (redirection == "") {
		if (!batchFlag && lastPipe) std::cout << cnt << std::endl;
	}
	else {
		if (redirectionType) {
			std::ofstream rdtFile(redirection, std::ios::app);
			if (!rdtFile) {
				std::cout << "An error has occured with opening the file." << std::endl;
				return;
			}
			rdtFile << cnt;
			rdtFile.close();
		}
		else {
			std::ofstream rdtFile(redirection);
			if (!rdtFile) {
				std::cout << "An error has occured with opening the file." << std::endl;
				return;
			}
			rdtFile << cnt;
			rdtFile.close();
		}
	}
	output = std::to_string(cnt);
}

std::string WC::getNewSymbol() {
	return "";
}

std::string WC::getOutput() {
	return output;
}

std::string WC::getRedirection() {
	return redirection;
}

std::string WC::readArg() {
	std::string input(std::istreambuf_iterator<char>(std::cin), {});
	if (!input.empty() && input.back() == '\n') input.pop_back();
	return input;
}

void WC::printToFile(std::string filename, int typeOfOutput, std::string outputText) {
	return;
}
