#include "ConsoleInterface.h"

#include "Operations.h"
#include "Task.h"
#include "CommandException.h"
#include "Utils.h"

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

const vector<ConsoleInterface::Command> ConsoleInterface::commands = {
	{ "moves",    "m", &handleMoveCount },
	{ "goal",     "g", &handleGoal },
	{ "base",     "b", &handleBaseValue },
	{ "add",      "a", &handleAddButton },
	{ "remove",   "r", &handleRemoveButton },
	{ "clear",    "c", &handleClearTask },
	{ "quit",     "q", &handleQuit },
	{ "solution", "s", &handleSolution },
	{ "help",     "h", &handleHelp },
	{ "info",     "i", &handleInfo}
};

void ConsoleInterface::main()
{
	m_task = make_shared<Task>();

	cout << "Welcome to \"Calculator: The Game\" solver." << endl
	     << "Type help to get list of supported commands." << endl;

	while (!m_quitFlag) {
		cout << "\n> ";

		string commandLine;
		getline(cin, commandLine);

		// Normalize input
		transform(commandLine.begin(), commandLine.end(), commandLine.begin(), ::tolower);
		commandLine = Utils::reduce(commandLine);

		// Divide into command itself and its parameters
		size_t spacePos = commandLine.find(' ');
		string commandName = commandLine.substr(0, spacePos);
		if (commandName.empty()) {
			continue;
		}

		string commandParams;
		if (spacePos != string::npos) {
			// after reducing string we are sure, that space is followed by normal char
			commandParams = commandLine.substr(spacePos+1);
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

string ConsoleInterface::stringifySolution(const Solution & solution) const
{
	string rez;
	for (SolutionStep step : solution) {
		rez += stringifyOperation(*step) + " ";
	}
	return rez;
}

string ConsoleInterface::stringifyOperation(const BaseOperation & operation) const
{
	const type_info& info = typeid(operation);

	if (info == typeid(AdditionOperation)) {
		int summand = get<int>(operation.getParams());
		if (summand > 0) {
			return "+" + to_string(summand);
		}
		else {
			return to_string(summand);
		}
	}
	else if (info == typeid(MultiplicationOperation)) {
		int multiplier = get<int>(operation.getParams());
		if (multiplier < 0) {
			return "x(" + to_string(multiplier) + ")";
		}
		else {
			return 'x' + to_string(multiplier);
		}
	}
	else if (info == typeid(DivisionOperation)) {
		int divisor = get<int>(operation.getParams());
		if (divisor < 0) {
			return "/(" + to_string(divisor) + ")";
		}
		else {
			return '/' + to_string(divisor);
		}
	}
	else if (info == typeid(CutOperation)) {
		return "<<";
	}
	else if (info == typeid(AppendOperation)) {
		int appendix = get<int>(operation.getParams());
		return to_string(appendix);
	}

	return string();
}

void ConsoleInterface::handleMoveCount(string params)
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

void ConsoleInterface::handleGoal(string params)
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

void ConsoleInterface::handleBaseValue(string params)
{
	try {
		m_task->setBaseValue(stoi(params));
	}
	catch (const logic_error& e) {
		// stoi obviously failed
		(void)e;
		throw CommandParameterParseException(params);
	}
}

void ConsoleInterface::handleAddButton(string params)
{
	if (params.empty()) {
		throw CommandMissingParameterException();
	}

	string coeff;
	try {
		bool inputHandled = true;

		switch (params[0]) {
		case '+':
		case '-':
			m_task->addOperation(typeid(AdditionOperation), stoi(params));
			break;
		case 'x':
			coeff = Utils::removeCharsFromString(params, "x()");
			m_task->addOperation(typeid(MultiplicationOperation), stoi(coeff));
			break;
		case '/':
			coeff = Utils::removeCharsFromString(params, "/()");
			m_task->addOperation(typeid(DivisionOperation), stoi(coeff));
			break;
		case '<':
			assert(params.length() == 2);
			assert(params[1] == '<');
			m_task->addOperation(typeid(CutOperation), OperationParameters());
			break;
		default:
			inputHandled = false;
		}

		if (!inputHandled) {
			if (Utils::isDigits(params)) {
				m_task->addOperation(typeid(AppendOperation), stoi(params));
			}
		}
	}
	catch (const logic_error& e) {
		// stoi obviously failed
		(void)e;
		throw CommandParameterParseException(params);
	}
}


void ConsoleInterface::handleRemoveButton(string params)
{
	
}

void ConsoleInterface::handleClearTask(string params)
{
	m_task = make_shared<Task>();
}

void ConsoleInterface::handleQuit(string params)
{
	m_quitFlag = true;
}

void ConsoleInterface::handleSolution(string params)
{
	vector<Solution> solutions = m_solver.getSolutions(*m_task);
	if (solutions.empty()) {
		cout << "Task doesn't have solutions" << endl;
	} else if (params == "best") {
		cout << stringifySolution(solutions[0]) << endl;
	}
	else {
		for (const auto& solution : solutions) {
			cout << stringifySolution(solution) << endl;
		}
	}
}

void ConsoleInterface::handleHelp(string params)
{

}

void ConsoleInterface::handleInfo(string params)
{

}
