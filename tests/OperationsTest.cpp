#include "Operations.h"
#include "gtest/gtest.h"

#include "Task.h"

#include <sstream>


using namespace std;

/********    SECTION1: common operation tests      ********/

struct OperationManipulationTestParams {
	const type_info& info;
	OperationParameters initialValue;
	OperationParameters modifiedValue;
};

class CommonOperationTest : public ::testing::TestWithParam<OperationManipulationTestParams> {

};

TEST_P(CommonOperationTest, CreateAndUpdate) {
	const OperationManipulationTestParams& values = GetParam();
	const type_info& info = values.info;
	const OperationParameters& vInit = values.initialValue;
	const OperationParameters& vMod = values.modifiedValue;


	// create
	unique_ptr<BaseOperation> testOp;
	if (info == typeid(AdditionOperation)) {
		testOp = make_unique<AdditionOperation>(vInit);
	}
	else if (info == typeid(MultiplicationOperation)) {
		testOp = make_unique<MultiplicationOperation>(vInit);
	}
	else if (info == typeid(DivisionOperation)) {
		testOp = make_unique<DivisionOperation>(vInit);
	}
	else if (info == typeid(CutOperation)) {
		testOp = make_unique<CutOperation>(vInit);
	}
	else if (info == typeid(AppendOperation)) {
		testOp = make_unique<AppendOperation>(vInit);
	}
	ASSERT_TRUE(testOp);
	EXPECT_EQ(testOp->getParams(), vInit);

	// update
	testOp->updateParams(vMod);
	EXPECT_EQ(testOp->getParams(), vMod);
	testOp->updateParams(vInit);
	EXPECT_EQ(testOp->getParams(), vInit);

	// copy
	unique_ptr<BaseOperation> copyOp;
	if (info == typeid(AdditionOperation)) {
		copyOp = make_unique<AdditionOperation>(*static_cast<AdditionOperation*>(testOp.get()));
	}
	else if (info == typeid(MultiplicationOperation)) {
		copyOp = make_unique<MultiplicationOperation>(*static_cast<MultiplicationOperation*>(testOp.get()));
	}
	else if (info == typeid(DivisionOperation)) {
		copyOp = make_unique<DivisionOperation>(*static_cast<DivisionOperation*>(testOp.get()));
	}
	else if (info == typeid(CutOperation)) {
		copyOp = make_unique<CutOperation>(*static_cast<CutOperation*>(testOp.get()));
	}
	else if (info == typeid(AppendOperation)) {
		copyOp = make_unique<AppendOperation>(*static_cast<AppendOperation*>(testOp.get()));
	}
	ASSERT_TRUE(copyOp);
	testOp->updateParams(vMod);
	EXPECT_EQ(copyOp->getParams(), vInit);
	testOp->updateParams(vInit);


	//clone 
	std::shared_ptr<BaseOperation> cloneOp = testOp->clone();
	testOp->updateParams(vMod);
	EXPECT_EQ(cloneOp->getParams(), vInit);
	testOp->updateParams(vInit);
}

INSTANTIATE_TEST_CASE_P(CommonOperationTests,
	CommonOperationTest,
	::testing::Values(
		OperationManipulationTestParams{ typeid(AdditionOperation), OperationParameters(5), OperationParameters(10) },
		OperationManipulationTestParams{ typeid(MultiplicationOperation), OperationParameters(5), OperationParameters(10) },
		OperationManipulationTestParams{ typeid(DivisionOperation), OperationParameters(5), OperationParameters(10) },
		OperationManipulationTestParams{ typeid(CutOperation), OperationParameters(), OperationParameters() },
		OperationManipulationTestParams{ typeid(AppendOperation), OperationParameters(5), OperationParameters(10) }
		)
);




/********    SECTION2: specific operation tests      ********/

void checkOperationResult(const BaseOperation& op, int initialValue, int finalValue) {
	ostringstream traceString;
	traceString << "Params: " << op.getParams() << "; initial value: " << initialValue << "; final value: " << finalValue << "\n";
	SCOPED_TRACE(traceString.str());

	Task task;
	task.setBaseValue(initialValue);
	task.setMoveCount(3);

	auto rez = op.apply(task);
	ASSERT_TRUE(rez.has_value());
	EXPECT_EQ(rez.value().getBaseValue(), finalValue);
	EXPECT_EQ(rez.value().getMoveCount(), 2);
}

void checkOperationIgnored(const BaseOperation& op, int initialValue) {
	ostringstream traceString;
	traceString << "Params: " << op.getParams() << "; initial value: " << initialValue << "\n";
	SCOPED_TRACE(traceString.str());

	Task task;
	task.setBaseValue(initialValue);
	task.setMoveCount(3);

	auto rez = op.apply(task);
	EXPECT_FALSE(rez.has_value());
}

TEST(OperationTest, Addition) {
	//positive addition
	checkOperationResult(AdditionOperation(5),  1, 6);
	checkOperationResult(AdditionOperation(5),  0, 5);
	checkOperationResult(AdditionOperation(5), -1, 4);

	//negative addition
	checkOperationResult(AdditionOperation(-5),  1, -4);
	checkOperationResult(AdditionOperation(-5),  0, -5);
	checkOperationResult(AdditionOperation(-5), -1, -6);

	//zero addition is ignored
	checkOperationIgnored(AdditionOperation(0),  1);
	checkOperationIgnored(AdditionOperation(0),  0);
	checkOperationIgnored(AdditionOperation(0), -1);

	//overflow
	checkOperationIgnored(AdditionOperation( 500000),  500000);
	checkOperationIgnored(AdditionOperation(-500000), -500000);
}


TEST(OperationTest, Multiplication) {
	//positive mult
	checkOperationResult(MultiplicationOperation(5),  3,  15);
	checkOperationResult(MultiplicationOperation(5), -3, -15);

	//negative mult
	checkOperationResult(MultiplicationOperation(-5),  3, -15);
	checkOperationResult(MultiplicationOperation(-5), -3,  15);

	//mult by 1 is ignored
	checkOperationIgnored(MultiplicationOperation(1),  3);
	checkOperationIgnored(MultiplicationOperation(1), -3);

	//mult of 0 is ignored
	checkOperationIgnored(MultiplicationOperation(5),  0);
	checkOperationIgnored(MultiplicationOperation(0),  0);
	checkOperationIgnored(MultiplicationOperation(-5), 0);

	//overflow
	checkOperationIgnored(MultiplicationOperation(2),  500000);
	checkOperationIgnored(MultiplicationOperation(-2), 500000);
	checkOperationIgnored(MultiplicationOperation(2),  -500000);
	checkOperationIgnored(MultiplicationOperation(-2), -500000);
}


TEST(OperationTest, Division) {
	//positive div
	checkOperationResult(DivisionOperation(4),  12,  3);
	checkOperationResult(DivisionOperation(4), -12, -3);

	//negative div
	checkOperationResult(DivisionOperation(-4),  12, -3);
	checkOperationResult(DivisionOperation(-4), -12,  3);

	//div by 1 is ignored
	checkOperationIgnored(DivisionOperation(1),  12);
	checkOperationIgnored(DivisionOperation(1), -12);

	//div of 0 is ignored
	checkOperationIgnored(DivisionOperation(4), 0);
	checkOperationIgnored(DivisionOperation(-4), 0);

	//div by 0 is ignored
	checkOperationIgnored(DivisionOperation(0),  12);
	checkOperationIgnored(DivisionOperation(0), -12);

	//if not a proper divisor, division is ignored
	checkOperationIgnored(DivisionOperation(5),   12);
	checkOperationIgnored(DivisionOperation(5),  -12);
	checkOperationIgnored(DivisionOperation(-5),  12);
	checkOperationIgnored(DivisionOperation(-5), -12);
}

TEST(OperationTest, Cut) {
	//cut positive
	checkOperationResult(CutOperation({}), 123, 12);
	checkOperationResult(CutOperation({}),   5,  0);

	//cut negative
	checkOperationResult(CutOperation({}), -123, -12);
	checkOperationResult(CutOperation({}),   -5,   0);

	//cut of 0 is ignored
	checkOperationIgnored(CutOperation({}), 0);
}

TEST(OperationTest, Append) {
	//append to positive
	checkOperationResult(AppendOperation(3),  12,  123);
	checkOperationResult(AppendOperation(34), 12, 1234);

	//append to negative
	checkOperationResult(AppendOperation(3),  -12,  -123);
	checkOperationResult(AppendOperation(34), -12, -1234);

	//append to 0
	checkOperationResult(AppendOperation(3),  0,  3);
	checkOperationResult(AppendOperation(34), 0, 34);

	//append 0
	checkOperationResult(AppendOperation(0),  12,  120);
	checkOperationResult(AppendOperation(0), -12, -120);

	//ignore appending 0 to 0
	checkOperationIgnored(AppendOperation(0), 0);

	//overflow
	checkOperationIgnored(AppendOperation(0), 100000);
	checkOperationIgnored(AppendOperation(0), -100000);
}