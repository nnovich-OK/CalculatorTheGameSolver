#ifndef SOLVER_H
#define SOLVER_H

#include "Task.h"
#include "Operations.h"

#include <vector>
#include <memory>

using SolutionStep = std::shared_ptr<BaseOperation>;

using Solution = std::vector<SolutionStep>;

class Solver {
public:
	const std::vector<Solution>& getSolutions(const Task& task);

protected:
	void solve(const Task& task);
	void solveHelper(Task task, Solution solutionCandidate);

private:
	Task m_task;
	std::vector<Solution> m_solutions;
};


#endif