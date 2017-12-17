#include "Task.h"

#include "CommandException.h"

using namespace std;


Task::Task(const Task& task)
{
	m_moveCount = task.m_moveCount;
	m_goal = task.m_goal;
	m_baseValue = task.m_baseValue;

	for (auto operation : task.m_operations) {
		m_operations.push_back(operation->clone());
	}
}

void Task::addOperation(const type_info& info, const OperationParameters& params)
{
	if (findOperation(info, params) != m_operations.end()) {
		throw CommandButtonDuplicateException("");	//TODO: maybe another type of exception should be thrown here
	}

	auto operation = BaseOperation::createOperation(info, params);
	if (operation != nullptr) {
		m_operations.push_back(operation);
	}
}

bool Task::operator==(const Task& task) const
{
	if (m_moveCount != task.m_moveCount
		|| m_goal != task.m_goal
		|| m_baseValue != task.m_baseValue
		|| m_operations.size() != task.m_operations.size())
	{
		return false;
	}

	for (auto operation : task.m_operations) {
		if (findOperation(operation) == m_operations.end()) {
			return false;
		}
	}

	return true;
}

vector<shared_ptr<BaseOperation>>::const_iterator
	Task::findOperation(const type_info& info, const OperationParameters & params) const
{

	for (auto it = m_operations.begin(); it != m_operations.end(); it++) {
		if (typeid(**it) == info
			&& (**it).getParams() == params)
		{
			return it;
		}
	}

	return m_operations.end();
}

vector<shared_ptr<BaseOperation>>::const_iterator Task::findOperation(shared_ptr<BaseOperation> operation) const
{
	return findOperation(typeid(*operation), operation->getParams());
}
