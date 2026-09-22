#include "Truncate.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>

Truncate::Truncate(std::string arg)
	:	filename(arg)
{}

void Truncate::run() {
	std::ofstream file(filename);
	if (!file) {
		std::cout << "An error has occurred with opening the file." << std::endl;
		return;
	}
	file.close();
}

std::string Truncate::getNewSymbol() {
	return "";
}

std::string Truncate::getOutput() {
	return "";
}

std::string Truncate::getRedirection() {
	return "";
}

std::string Truncate::readArg() {
	return "";
}

void Truncate::printToFile(std::string filename, int typeOfOutput, std::string outputText) {
	return;
}
