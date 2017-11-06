#ifndef CONSOLE_INTERFACE_H
#define CONSOLE_INTERFACE_H

#include "Task.h"
#include "Solver.h"

#include <string>
#include <vector>
#include <memory>

class ConsoleInterface {
public:
	void main();



private:
	std::string stringifySolution(const Solution& solution) const;
	std::string stringifyOperation(const BaseOperation& operation) const;

	void handleMoveCount(std::string params);
	void handleGoal(std::string params);
	void handleBaseValue(std::string params);
	void handleAddButton(std::string params);
	void handleRemoveButton(std::string params);
	void handleClearTask(std::string params);
	void handleQuit(std::string params);
	void handleSolution(std::string params);
	void handleHelp(std::string params);
	void handleInfo(std::string params);	

	using CommandHandler = void (ConsoleInterface::*) (std::string params);

	struct Command {
		std::string longName;
		std::string shortName;
		CommandHandler handler;
	};

	static const std::vector<Command> commands;

	std::shared_ptr<Task> m_task = std::make_shared<Task>();
	Solver m_solver;
	bool m_quitFlag = false;
	bool m_restartFlag = false;
};

#endif