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

	virtual std::optional<Task> apply(Task task) const = 0;

	virtual void updateParams(OperationParameters params) = 0;

	virtual OperationParameters getParams() const = 0;

	virtual std::shared_ptr<BaseOperation> clone() const = 0;

	static std::shared_ptr<BaseOperation> createOperation(const std::type_info& info, const OperationParameters& param);

protected:
	static bool verifyChange(int origValue, int modValue);
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

	virtual std::optional<Task> apply(Task task) const;

	virtual void updateParams(OperationParameters params) {
		m_summand = std::get<int>(params);
	}

	virtual OperationParameters getParams() const {
		return OperationParameters(m_summand);
	}

	virtual std::shared_ptr<BaseOperation> clone() const {
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

	virtual std::optional<Task> apply(Task task) const;

	virtual void updateParams(OperationParameters params) {
		m_multiplier = std::get<int>(params);
	}

	virtual OperationParameters getParams() const {
		return OperationParameters(m_multiplier);
	}

	virtual std::shared_ptr<BaseOperation> clone() const {
		return std::make_shared<MultiplicationOperation>(*this);
	}
};

class DivisionOperation : public BaseOperation {
private:
	int m_divisor;

public:
	DivisionOperation(OperationParameters n) {
		m_divisor = std::get<int>(n);
	}

	DivisionOperation(const DivisionOperation& operation)
		: m_divisor(operation.m_divisor) {}

	virtual std::optional<Task> apply(Task task) const;

	virtual void updateParams(OperationParameters params) {
		m_divisor = std::get<int>(params);
	}

	virtual OperationParameters getParams() const {
		return OperationParameters(m_divisor);
	}

	virtual std::shared_ptr<BaseOperation> clone() const {
		return std::make_shared<DivisionOperation>(*this);
	}
};

class CutOperation : public BaseOperation {
public:
	CutOperation(OperationParameters n) {}

	CutOperation(const CutOperation& operation) {}

	virtual std::optional<Task> apply(Task task) const;

	virtual void updateParams(OperationParameters params) {}

	virtual OperationParameters getParams() const {
		return OperationParameters();
	}

	virtual std::shared_ptr<BaseOperation> clone() const {
		return std::make_shared<CutOperation>(*this);
	}
};

#endif