#include "Task.h"

Task::Task(const Task& task)
{
	m_moveCount = task.m_moveCount;
	m_goal = task.m_goal;
	m_baseValue = task.m_baseValue;

	for (auto& operation : task.m_operations) {
		m_operations.push_back(operation->clone());
	}
}

void Task::addOperation(const type_info& info, const OperationParameters& param)
{
	auto operation = BaseOperation::createOperation(info, param);
	if (operation != nullptr) {
		m_operations.push_back(operation);
	}
}

