#ifndef TASK_H
#define TASK_H

#include <vector>
#include <memory>

#include "OperationParams.h"
#include "Operations.h"

class BaseOperation;

class Task {
public:
	Task() {}
	Task(const Task& task);

	void setMoveCount(int count) { m_moveCount = count; }
	void decreaseMoveCount()     { m_moveCount--; }
	bool isOutOfMoves() const    { return (m_moveCount == 0); }

	void setGoal(int goal)       { m_goal = goal; }
	bool isSolved() const        { return (m_goal == m_baseValue); }

	void setBaseValue(int value) { m_baseValue = value; }
	int getBaseValue() const     { return m_baseValue; }

	void addOperation(const std::type_info& info, const OperationParameters& param);
	void removeOperation(std::type_info info, OperationParameters param);
	void removeOperationByIndex(int index);

private:
	int m_moveCount = 0;
	int m_goal = 0;
	int m_baseValue = 0;
	std::vector<std::shared_ptr<BaseOperation>> m_operations;
};

#endif