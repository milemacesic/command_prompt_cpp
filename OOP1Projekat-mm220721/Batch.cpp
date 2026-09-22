#include "Batch.h"
#include "Interpreter.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>

Batch::Batch(std::string arg, std::string rdt, int rdtType, int batch, int last)
	:	filename(arg)
	,	redirection(rdt)
	,	redirectionType(rdtType)
	,	batchFlag(batch)
	,	pipe(last)
{}

void Batch::run() {
	output = "";
	std::string line;
	std::ifstream file(filename);
	if (!file) {
		std::cout << "An error has occurred with opening the file." << std::endl;
		return;
	}
	Interpreter* inter;
	if (redirection == "") inter = new Interpreter(0);
	else inter = new Interpreter(1);
	while (std::getline(file, line)) {
		inter->process(line);
		output += inter->getOutput();
		// Redirection.
		if (redirection != "" && inter->getOutput().size() > 0 && batchFlag == 0 && inter->getRedirection() == "" && pipe != 0) printToFile(redirection, redirectionType, inter->getOutput());
	}
	file.close();
	newSymbol = inter->getSymbol();
	delete inter;
}

std::string Batch::getNewSymbol() {
	return newSymbol;
}

std::string Batch::getOutput() {
	return output;
}

std::string Batch::getRedirection() {
	return redirection;
}

std::string Batch::readArg() {
	return "";
}

void Batch::printToFile(std::string filename, int typeOfOutput, std::string outputText) {
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
