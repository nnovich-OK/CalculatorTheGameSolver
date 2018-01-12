#include "Operations.h"

using namespace std;

shared_ptr<BaseOperation> BaseOperation::createOperation(const type_info& info, const OperationParameters& param)
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
	else if (info == typeid(AppendOperation)) {
		return make_shared<AppendOperation>(param);
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

optional<Task> AdditionOperation::apply(Task task) const
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

optional<Task> MultiplicationOperation::apply(Task task) const
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

optional<Task> DivisionOperation::apply(Task task) const
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

optional<Task> CutOperation::apply(Task task) const
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

optional<Task> AppendOperation::apply(Task task) const
{
	int origValue = task.getBaseValue();
	
	int tmp = m_appendix;
	int digitCount = 0;
	while (tmp != 0) {
		tmp /= 10;
		digitCount++;
	}

	// we might want to append single '0'
	if (digitCount == 0) {
		digitCount = 1;
	}

	int modValue = origValue;
	while (digitCount != 0) {
		modValue *= 10;
		digitCount--;
	}

	if (modValue >= 0) {
		modValue += m_appendix;
	}
	else {
		modValue -= m_appendix;
	}

	if (!BaseOperation::verifyChange(origValue, modValue)) {
		return nullopt;
	}

	task.decreaseMoveCount();
	task.setBaseValue(modValue);
	return task;
}