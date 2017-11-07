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
	else if (info == typeid(DivisionOperation)) {
		return make_shared<DivisionOperation>(param);
	}
	else if (info == typeid(CutOperation)) {
		return make_shared<CutOperation>(param);
	}
	
	return nullptr;
}

bool BaseOperation::verifyChange(int origValue, int modValue)
{
	const int maxValue = 999999;
	const int minValue = -999999;
	return (origValue != modValue
		&& modValue <= maxValue
		&& modValue >= minValue);
}

std::optional<Task> AdditionOperation::apply(Task task) const
{
	int origValue = task.getBaseValue();
	int modValue = origValue + m_summand;

	if (!BaseOperation::verifyChange(origValue, modValue)) {
		return nullopt;
	}

	task.decreaseMoveCount();
	task.setBaseValue(modValue);
	return task;
}

std::optional<Task> MultiplicationOperation::apply(Task task) const
{
	int origValue = task.getBaseValue();
	int modValue = origValue * m_multiplier;

	if (!BaseOperation::verifyChange(origValue, modValue)) {
		return nullopt;
	}

	task.decreaseMoveCount();
	task.setBaseValue(modValue);
	return task;
}

std::optional<Task> DivisionOperation::apply(Task task) const
{
	int origValue = task.getBaseValue();
	if (origValue % m_divisor != 0) {
		return nullopt;
	}

	int modValue = origValue / m_divisor;

	if (!BaseOperation::verifyChange(origValue, modValue)) {
		return nullopt;
	}

	task.decreaseMoveCount();
	task.setBaseValue(modValue);
	return task;
}

std::optional<Task> CutOperation::apply(Task task) const
{
	int origValue = task.getBaseValue();
	int modValue = origValue / 10;

	if (!BaseOperation::verifyChange(origValue, modValue)) {
		return nullopt;
	}

	task.decreaseMoveCount();
	task.setBaseValue(modValue);
	return task;
}