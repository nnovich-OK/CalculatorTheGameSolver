#include "Operations.h"
#include "gtest/gtest.h"

#include "Task.h"


using namespace std;

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


TEST(OperationTest, Addition) {
	Task task;
	task.setMoveCount(3);
	task.setBaseValue(1);

	//positive addition
	AdditionOperation op(5);
	auto rez = op.apply(task);
	ASSERT_TRUE(rez.has_value());
	EXPECT_EQ(rez.value().getBaseValue(), 6);
	EXPECT_EQ(rez.value().getMoveCount(), 2);

	//negative addition
	op.updateParams(-5);
	rez = op.apply(task);
	ASSERT_TRUE(rez.has_value());
	EXPECT_EQ(rez.value().getBaseValue(), -4);
	EXPECT_EQ(rez.value().getMoveCount(), 2);

	//zero addition is ignored
	op.updateParams(0);
	rez = op.apply(task);
	EXPECT_FALSE(rez.has_value());

	//positive overflow
	task.setBaseValue(500000);
	op.updateParams(500000);
	rez = op.apply(task);
	EXPECT_FALSE(rez.has_value());

	//negative overflow
	task.setBaseValue(-500000);
	op.updateParams(-500000);
	rez = op.apply(task);
	EXPECT_FALSE(rez.has_value());
}


TEST(OperationTest, Multiplication) {
	Task task;
	task.setMoveCount(3);
	task.setBaseValue(2);

	//positive mult
	MultiplicationOperation op(5);
	auto rez = op.apply(task);
	ASSERT_TRUE(rez.has_value());
	EXPECT_EQ(rez.value().getBaseValue(), 10);
	EXPECT_EQ(rez.value().getMoveCount(), 2);

	//negative mult
	op.updateParams(-5);
	rez = op.apply(task);
	ASSERT_TRUE(rez.has_value());
	EXPECT_EQ(rez.value().getBaseValue(), -10);
	EXPECT_EQ(rez.value().getMoveCount(), 2);

	//mult by 1 is ignored
	op.updateParams(1);
	rez = op.apply(task);
	EXPECT_FALSE(rez.has_value());

	//mult of 0 is ignored
	op.updateParams(5);
	task.setBaseValue(0);
	rez = op.apply(task);
	EXPECT_FALSE(rez.has_value());

	//positive overflow
	task.setBaseValue(500000);
	op.updateParams(2);
	rez = op.apply(task);
	EXPECT_FALSE(rez.has_value());

	//negative overflow
	task.setBaseValue(-500000);
	op.updateParams(-2);
	rez = op.apply(task);
	EXPECT_FALSE(rez.has_value());
}


TEST(OperationTest, Division) {
	Task task;
	task.setMoveCount(3);
	task.setBaseValue(12);

	//positive div
	DivisionOperation op(4);
	auto rez = op.apply(task);
	ASSERT_TRUE(rez.has_value());
	EXPECT_EQ(rez.value().getBaseValue(), 3);
	EXPECT_EQ(rez.value().getMoveCount(), 2);

	//negative div
	op.updateParams(-4);
	rez = op.apply(task);
	ASSERT_TRUE(rez.has_value());
	EXPECT_EQ(rez.value().getBaseValue(), -3);
	EXPECT_EQ(rez.value().getMoveCount(), 2);

	//div by 1 is ignored
	op.updateParams(1);
	rez = op.apply(task);
	EXPECT_FALSE(rez.has_value());

	//div of 0 is ignored
	op.updateParams(5);
	task.setBaseValue(0);
	rez = op.apply(task);
	EXPECT_FALSE(rez.has_value());

	//if not a proper divisor, division is ignored
	task.setBaseValue(12);
	op.updateParams(5);
	rez = op.apply(task);
	EXPECT_FALSE(rez.has_value());
}