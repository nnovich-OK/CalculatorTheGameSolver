#ifndef TASK_H
#define TASK_H

#include "Operations.h"

#include <vector>
#include <memory>

class Task {
public:
	void setMoveCount(int count) { m_moveCount = count; }
	void setGoal(int goal) { m_goal = goal; }
	void addOperation(std::unique_ptr<BaseOperation> operation);
	void removeOperation(const BaseOperation* operation);

private:
	int m_moveCount = 0;
	int m_goal = 0;
	std::vector<std::unique_ptr<BaseOperation>> m_operations;
};

#endif