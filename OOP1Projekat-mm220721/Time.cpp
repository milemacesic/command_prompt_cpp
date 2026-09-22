#define _CRT_SECURE_NO_WARNINGS
#include "Time.h"
#include <string>
#include <iostream>
#include <ctime>
#include <fstream>

Time::Time(std::string rdt, int rdtType, int batch, int last)
	:	redirection(rdt)
	,	redirectionType(rdtType)
	,	batchFlag(batch)
	,	pipe(last)
{}

void Time::run() {
	std::time_t t = std::time(nullptr);
	std::tm *tm = std::localtime(&t);
	char currentTime[9];
	std::strftime(currentTime, sizeof(currentTime), "%H:%M:%S", tm);
	if (redirection == "") {
		if (!batchFlag && pipe) std::cout << currentTime << std::endl;
	}
	else printToFile(redirection, redirectionType, currentTime);
	output = currentTime;
}

std::string Time::getNewSymbol() {
	return "";
}

std::string Time::getOutput() {
	return output;
}

std::string Time::getRedirection() {
	return redirection;
}

std::string Time::readArg() {
	return "";
}

void Time::printToFile(std::string filename, int typeOfOutput, std::string outputText) {
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
