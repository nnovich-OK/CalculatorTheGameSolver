#ifndef OPERATION_PARAMS_H
#define OPERATION_PARAMS_H

#include <variant>
#include <utility>
#include <ostream>

using OperationParameters = std::variant<
	int,
	std::pair<int, int>
>;

std::ostream& operator<<(std::ostream& stream, const OperationParameters& param);

#endif