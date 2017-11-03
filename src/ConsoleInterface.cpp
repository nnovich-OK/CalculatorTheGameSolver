#include "ConsoleInterface.h"

#include "Operations.h"
#include "Task.h"
#include "CommandException.h"

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

const std::vector<ConsoleInterface::Command> ConsoleInterface::commands = {
	{ "moves",  "m", &handleMoveCount },
	{ "goal",   "g", &handleGoal },
	{ "add",    "a", &handleAddButton },
	{ "remove", "r", &handleRemoveButton },
	{ "clear",  "c", &handleClearTask },
	{ "quit",   "q", &handleQuit },
	{ "solve",  "s", &handleSolve },
	{ "help",   "h", &handleHelp },
	{ "info",   "i", &handleInfo}
};

std::string ConsoleInterface::removeLeadingSpaces(const std::string & str)
{
	size_t leadingSpacesCount = 0;
	while (leadingSpacesCount < str.length() && str[leadingSpacesCount] == ' ') {
		leadingSpacesCount++;
	}
	return str.substr(leadingSpacesCount);
}

void ConsoleInterface::main()
{
	m_task = make_unique<Task>();

	cout << "Welcome to \"Calculator: The Game\" solver." << endl
	     << "Type help to get list of supported commands." << endl;

	while (!m_quitFlag) {
		cout << "\n> ";

		string commandLine;
		getline(cin, commandLine);

		// Normalize input
		std::transform(commandLine.begin(), commandLine.end(), commandLine.begin(), ::tolower);
		commandLine = removeLeadingSpaces(commandLine);

		// Divide into command itself and its parameters
		size_t spacePos = commandLine.find(' ');
		string commandName = commandLine.substr(0, spacePos);
		if (commandName.empty()) {
			continue;
		}

		string commandParams;
		if (spacePos != string::npos) {
			commandParams = removeLeadingSpaces(commandLine.substr(spacePos));
		}

		bool commandFound = false;
		for (const Command& cmd : commands) {
			if (commandName == cmd.longName || commandName == cmd.shortName) {
				try {
					commandFound = true;
					(this->*cmd.handler)(commandParams);
				}
				catch (const CommandException& e) {
					cout << commandName << " error: " << e.what() << endl;
				}
				break;
			}
		}

		if (!commandFound) {
			cout << "Invalid input. Type \"help\" for list of supported commands." << endl;
		}
	}
}

void ConsoleInterface::handleMoveCount(std::string params)
{
	try {
		m_task->setMoveCount(stoi(params));
	}
	catch (const logic_error& e) {
		// stoi obviously failed
		(void)e;
		throw CommandParameterParseException(params);
	}
}

void ConsoleInterface::handleGoal(std::string params)
{
	try {
		m_task->setGoal(stoi(params));
	}
	catch (const logic_error& e) {
		// stoi obviously failed
		(void)e;
		throw CommandParameterParseException(params);
	}
}

void ConsoleInterface::handleAddButton(std::string params)
{

}

void ConsoleInterface::handleRemoveButton(std::string params)
{
	
}

void ConsoleInterface::handleClearTask(std::string params)
{
	m_task = make_unique<Task>();
}

void ConsoleInterface::handleQuit(std::string params)
{
	m_quitFlag = true;
}

void ConsoleInterface::handleSolve(std::string params)
{

}

void ConsoleInterface::handleHelp(std::string params)
{

}

void ConsoleInterface::handleInfo(std::string params)
{

}
