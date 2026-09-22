#include "Touch.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>

Touch::Touch(std::string arg)
	:	filename(arg)
{}

void Touch::run() {
	// First it checks if this file exists before it creates a new file.
	std::ifstream check(filename);
	if (check) {
		std::cout << "Error. File already exists." << std::endl;
		check.close();
	}
	else {
		std::ofstream file(filename);
		if (!file) {
			std::cout << "An error has occurred with opening the file." << std::endl;
			return;
		}
		file.close();
	}
}

std::string Touch::getNewSymbol() {
	return "";
}

std::string Touch::getOutput() {
	return "";
}

std::string Touch::getRedirection() {
	return "";
}

std::string Touch::readArg() {
	return "";
}

void Touch::printToFile(std::string filename, int typeOfOutput, std::string outputText) {
	return;
}
