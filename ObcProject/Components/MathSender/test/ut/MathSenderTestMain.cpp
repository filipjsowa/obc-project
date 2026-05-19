// ======================================================================
// \title  MathSenderTestMain.cpp
// \author otsii
// \brief  cpp file for MathSender component test main function
// ======================================================================

#include "MathSenderTester.hpp"
#include "STest/Random/Random.hpp"

TEST(Nominal, AddCommand) {
    ObcProject::MathSenderTester tester;
    tester.testAddCommand();
}

TEST(Nominal, Result) {
    ObcProject::MathSenderTester tester;
    tester.testResult();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
