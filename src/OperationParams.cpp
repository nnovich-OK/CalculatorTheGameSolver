#include "OperationParams.h"

#include <type_traits>

using namespace std;

ostream & operator<<(ostream & stream, const OperationParameters & param)
{
	visit([&stream](auto&& arg) {
		using T = decay_t<decltype(arg)>;
		if constexpr (is_same_v<T, int>) {
			stream << "(" << arg << ")";
		}
		else if constexpr (is_same_v<T, pair<int, int>>) {
			stream << "(" << arg.first << ", " << arg.second << ")";
		}
	}, param);
	return stream;
}
