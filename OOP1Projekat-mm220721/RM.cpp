#include "RM.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <filesystem>

RM::RM(std::string arg)
	:	filename(arg)
{}

void RM::run() {
	if (!std::filesystem::remove(filename)) std::cout << "Error. File not found." << std::endl;
}

std::string RM::getNewSymbol() {
	return "";
}

std::string RM::getOutput() {
	return "";
}

std::string RM::getRedirection() {
	return "";
}

std::string RM::readArg() {
	return "";
}

void RM::printToFile(std::string filename, int typeOfOutput, std::string outputText) {
	return;
}
