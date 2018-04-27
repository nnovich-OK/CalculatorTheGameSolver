#include "Solver.h"
#include "gtest/gtest.h"

#include <algorithm>

using namespace std;

// TODO: might add solution comparison to separate solution class
// TODO: also might add proper printing of solution to improve logging

bool solutionsIdentical(const Solution& rhs, const Solution& lhs) {
	if (rhs.size() != lhs.size()) {
		return false;
	}

	for (size_t i = 0; i < rhs.size(); i++) {
		if ((typeid(*rhs[i]) != typeid(*lhs[i]))
			|| rhs[i]->getParams() != lhs[i]->getParams())
		{
			return false;
		}
	}

	return true;
}

// params are vectors of solutions with same length
bool solutionSubvectorIdentical(vector<Solution> rhs, vector<Solution> lhs) {
	if (rhs.size() != lhs.size()) {
		return false;
	}

	auto it_r = rhs.begin();

	while (it_r != rhs.end()) {

		bool matchFound = false;
		auto it_l = lhs.begin();

		while (it_l != lhs.end()) {
			if (solutionsIdentical(*it_l, *it_r)) {
				matchFound = true;
				it_l = lhs.erase(it_l);
				it_r = rhs.erase(it_r);
				break;
			}
			else {
				++it_l;
			}
		}

		if (!matchFound) {
			return false;
		}
	}

	return true;
}


bool solutionVectorsIdentical(const vector<Solution>& rhs, const vector<Solution>& lhs) {
	if (rhs.size() != lhs.size()) {
		return false;
	}

	// solutions are sorted by their length, so solutions with the same length may go in an arbitrary order
	// find subset of solutions with the same length, compare such subsets with helper funciton

	size_t range_start = 0;
	size_t range_end = 0;

	while (range_end < rhs.size()) {
		range_start = range_end;
		do {
			range_end++;
		} while (range_end < rhs.size() && (rhs[range_end].size() == rhs[range_start].size()));

		if (!solutionSubvectorIdentical(
			vector<Solution>(rhs.begin() + range_start, rhs.begin() + range_end),
			vector<Solution>(lhs.begin() + range_start, lhs.begin() + range_end)
			))
		{
			return false;
		}
	}

	return true;
}

TEST(SolverTest, OneStepSolution) {
	Solver solver;

	Task task;
	task.setMoveCount(1);
	task.setBaseValue(9);
	task.setGoal(10);
	task.addOperation(typeid(AdditionOperation), 1);

	// finding trivial solution
	auto solutions = solver.getSolutions(task);
	vector<Solution> expectedSolutions = {
		{make_shared<AdditionOperation>(1)}
	};
	EXPECT_TRUE(solutionVectorsIdentical(solutions, expectedSolutions));

	// discovering absence of solutions
	task.setBaseValue(8);
	solutions = solver.getSolutions(task);
	EXPECT_TRUE(solutions.empty());
}

TEST(SolverTest, MultistepSolution) {
	Solver solver;

	Task task;
	task.setMoveCount(2);
	task.setBaseValue(1);
	task.setGoal(6);
	task.addOperation(typeid(AdditionOperation), 1);
	task.addOperation(typeid(MultiplicationOperation), 3);

	auto solutions = solver.getSolutions(task);
	vector<Solution> expectedSolutions = {
		{ make_shared<AdditionOperation>(1), make_shared<MultiplicationOperation>(3) }
	};
	EXPECT_TRUE(solutionVectorsIdentical(solutions, expectedSolutions));
}

