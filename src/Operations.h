#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <optional>

class BaseOperation {
public:
	virtual ~BaseOperation() {}

	virtual std::optional<int> apply(int param) {
		return std::nullopt;
	}

	virtual void modify(int delta) {}
};

class AdditionOperation : public BaseOperation {
private:
	int m_n;
public:
	AdditionOperation(int n)
		: m_n(n) {}

	virtual std::optional<int> apply(int param) {
		return param + m_n;
	}

	virtual void modify(int delta) {
		m_n += delta;
	}
};

class MultiplicationOperation : public BaseOperation {
private:
	int m_n;

public:
	MultiplicationOperation(int n)
		: m_n(n) {}

	virtual std::optional<int> apply(int param) {
		return param * m_n;
	}

	virtual void modify(int delta) {
		m_n += delta;
	}
};

#endif