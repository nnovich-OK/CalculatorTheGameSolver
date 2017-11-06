#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <optional>
#include <memory>
#include <typeinfo>

#include "OperationParams.h"
#include "Task.h"

class Task;

class BaseOperation {
public:
	virtual ~BaseOperation() {}

	virtual std::optional<Task> apply(Task task) = 0;

	virtual void updateParams(OperationParameters params) = 0;

	virtual OperationParameters getParams() = 0;

	virtual std::shared_ptr<BaseOperation> clone() = 0;

	static std::shared_ptr<BaseOperation> createOperation(const std::type_info& info, const OperationParameters& param);
};

class AdditionOperation : public BaseOperation {
private:
	int m_summand;
public:
	AdditionOperation(OperationParameters n) {
		m_summand = std::get<int>(n);
	}

	AdditionOperation(const AdditionOperation& operation)
		: m_summand(operation.m_summand) {}

	virtual std::optional<Task> apply(Task task);

	virtual void updateParams(OperationParameters params) {
		m_summand = std::get<int>(params);
	}

	virtual OperationParameters getParams() {
		return OperationParameters(m_summand);
	}

	virtual std::shared_ptr<BaseOperation> clone() {
		return std::make_shared<AdditionOperation>(*this);
	}
};

class MultiplicationOperation : public BaseOperation {
private:
	int m_multiplier;

public:
	MultiplicationOperation(OperationParameters n) {
		m_multiplier = std::get<int>(n);
	}

	MultiplicationOperation(const MultiplicationOperation& operation)
		: m_multiplier (operation.m_multiplier) {}

	virtual std::optional<Task> apply(Task task);

	virtual void updateParams(OperationParameters params) {
		m_multiplier = std::get<int>(params);
	}

	virtual OperationParameters getParams() {
		return OperationParameters(m_multiplier);
	}

	virtual std::shared_ptr<BaseOperation> clone() {
		return std::make_shared<MultiplicationOperation>(*this);
	}
};

#endif