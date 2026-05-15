// ======================================================================
// \title  MathReceiverTestMain.cpp
// \author otsii
// \brief  cpp file for MathReceiver component test main function
// ======================================================================

#include "MathReceiverTester.hpp"
#include "STest/Random/Random.hpp"

TEST(Nominal, AddCommand) {
    MathProject::MathReceiverTester tester;
    tester.testAdd();
    tester.testSub();
    tester.testThrottle();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
