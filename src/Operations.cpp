#include "Operations.h"

using namespace std;

shared_ptr<BaseOperation> BaseOperation::createOperation(const std::type_info& info, const OperationParameters& param)
{
	if (info == typeid(AdditionOperation)) {
		return make_shared<AdditionOperation>(param);
	}
	else if (info == typeid(MultiplicationOperation)) {
		return make_shared<MultiplicationOperation>(param);
	}
	
	return nullptr;
}

std::optional<Task> AdditionOperation::apply(Task task)
{
	task.decreaseMoveCount();
	task.setBaseValue(task.getBaseValue() + m_summand);
	return task;
}

std::optional<Task> MultiplicationOperation::apply(Task task)
{
	task.decreaseMoveCount();
	task.setBaseValue(task.getBaseValue() * m_multiplier);
	return task;
}
