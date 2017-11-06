#ifndef OPERATION_PARAMS_H
#define OPERATION_PARAMS_H

#include <variant>
#include <utility>

using OperationParameters = std::variant<
	int,
	std::pair<int, int>
>;

#endif