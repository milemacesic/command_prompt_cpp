#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"
#include <string>
#include <iostream>
#include <ctime>
#include <fstream>

Date::Date(std::string rdt, int rdtType, int batch, int last)
	:	redirection(rdt)
	,	redirectionType(rdtType)
	,	batchFlag(batch)
	,	pipe(last)
{}

void Date::run() {
	std::time_t t = std::time(nullptr);
	std::tm tm = *std::localtime(&t);
	char date[11];
	std::strftime(date, sizeof(date), "%d.%m.%Y", &tm);
	if (redirection == "") {
		if (!batchFlag && pipe) std::cout << date << std::endl;
	}
	else printToFile(redirection, redirectionType, date);
	output = date;
}

std::string Date::getNewSymbol() {
	return "";
}

std::string Date::getOutput() {
	return output;
}

std::string Date::getRedirection() {
	return redirection;
}

std::string Date::readArg() {
	return "";
}

void Date::printToFile(std::string filename, int typeOfOutput, std::string outputText) {
	if (typeOfOutput) {
		std::ofstream file(filename, std::ios::app);
		if (!file) {
			std::cout << "An error has occured with opening the file." << std::endl;
			return;
		}
		file << outputText;
		file.close();
	}
	else {
		std::ofstream file(filename);
		if (!file) {
			std::cout << "An error has occurred with opening the file." << std::endl;
			return;
		}
		file << outputText;
		file.close();
	}
}
