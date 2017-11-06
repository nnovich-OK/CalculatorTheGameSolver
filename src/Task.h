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
	bool isOutOfMoves() const    { return (m_moveCount <= 0); }

	void setGoal(int goal)       { m_goal = goal; }
	bool isSolved() const        { return (m_goal == m_baseValue); }

	void setBaseValue(int value) { m_baseValue = value; }
	int getBaseValue() const     { return m_baseValue; }

	void addOperation(const std::type_info& info, const OperationParameters& params);
	void removeOperation(std::type_info info, OperationParameters params);
	void removeOperationByIndex(int index);
	const std::vector<std::shared_ptr<BaseOperation>>& getOperations() { return m_operations; }

	bool operator==(const Task& task) const;
	bool operator!=(const Task& task) const { return !(*this == task); }

protected:
	std::vector<std::shared_ptr<BaseOperation>>::const_iterator
		findOperation(const std::type_info& info, const OperationParameters& params) const;

	std::vector<std::shared_ptr<BaseOperation>>::const_iterator
		findOperation(std::shared_ptr<BaseOperation> operation) const;

private:
	int m_moveCount = 0;
	int m_goal = 0;
	int m_baseValue = 0;
	std::vector<std::shared_ptr<BaseOperation>> m_operations;
};

#endif