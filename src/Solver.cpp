#include "Solver.h"

#include <optional>
#include <algorithm>

using namespace std;

const vector<Solution>& Solver::getSolutions(const Task& task)
{
	if (m_task != task) {
		solve(task);
	}

	return m_solutions;
}

void Solver::solve(const Task& task)
{
	// store new task
	m_task = task;

	// clear cached solutions
	m_solutions.clear();

	// find new set of solutions
	Solution solutionCandidate;
	solveHelper(m_task, solutionCandidate);

	sort(m_solutions.begin(), m_solutions.end(), [](const Solution& s1, const Solution& s2) {
		return (s1.size() < s2.size());
	});
}

void Solver::solveHelper(Task task, Solution solutionCandidate)
{
	if (task.isSolved()) {
		m_solutions.push_back(solutionCandidate);
		return;
	}

	if (task.isOutOfMoves()) {
		return;
	}

	for (auto operation : task.getOperations()) {
		std::optional<Task> modifiedTask = operation->apply(task);

		if (modifiedTask.has_value()) {
			Solution updatedCandidate(solutionCandidate);
			updatedCandidate.push_back(operation);
			solveHelper(modifiedTask.value(), updatedCandidate);
		}
	}
}

