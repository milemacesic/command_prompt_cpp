#include <iostream>
#include <string>
#include "Interpreter.h"
using namespace std;

int main() {
	string commandLine;
	Interpreter* inter = new Interpreter(0);

	while (1) {
		cout << inter->getSymbol() << " ";
		getline(cin, commandLine);
		if (commandLine.size() > 512) commandLine = commandLine.substr(0, 512);
		inter->process(commandLine);
	}

	delete inter;
	return 0;
}
