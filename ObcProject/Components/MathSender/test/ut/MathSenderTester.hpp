// ======================================================================
// \title  MathSenderTester.hpp
// \author otsii
// \brief  hpp file for MathSender component test harness implementation class
// ======================================================================

#ifndef MathProject_MathSenderTester_HPP
#define MathProject_MathSenderTester_HPP

#include "MathProject/Components/MathSender/MathSender.hpp"
#include "MathProject/Components/MathSender/MathSenderGTestBase.hpp"

namespace MathProject {

class MathSenderTester final : public MathSenderGTestBase {
  public:
    // ----------------------------------------------------------------------
    // Constants
    // ----------------------------------------------------------------------

    // Maximum size of histories storing events, telemetry, and port outputs
    static const FwSizeType MAX_HISTORY_SIZE = 10;

    // Instance ID supplied to the component instance under test
    static const FwEnumStoreType TEST_INSTANCE_ID = 0;

    // Queue depth supplied to the component instance under test
    static const FwSizeType TEST_INSTANCE_QUEUE_DEPTH = 10;

  public:
    // ----------------------------------------------------------------------
    // Construction and destruction
    // ----------------------------------------------------------------------

    //! Construct object MathSenderTester
    MathSenderTester();

    //! Destroy object MathSenderTester
    ~MathSenderTester();

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    void testDoMath(MathOp op);

    void testAddCommand();

    void testResult();

  private:
    // ----------------------------------------------------------------------
    // Helper functions
    // ----------------------------------------------------------------------

    //! Connect ports
    void connectPorts();

    //! Initialize components
    void initComponents();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The component under test
    MathSender component;
};

}  // namespace MathProject

#endif
