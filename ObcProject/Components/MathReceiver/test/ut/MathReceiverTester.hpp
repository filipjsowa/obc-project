// ======================================================================
// \title  MathReceiverTester.hpp
// \author otsii
// \brief  hpp file for MathReceiver component test harness implementation class
// ======================================================================

#ifndef ObcProject_MathReceiverTester_HPP
#define ObcProject_MathReceiverTester_HPP

#include "ObcProject/Components/MathReceiver/MathReceiver.hpp"
#include "ObcProject/Components/MathReceiver/MathReceiverGTestBase.hpp"

namespace ObcProject {

class MathReceiverTester final : public MathReceiverGTestBase {
  public:

  // ----------------------------------------------------------------------
  // Types
  // ----------------------------------------------------------------------

  enum class ThrottleState {
    THROTTLED,
    NOT_THROTTLED
  };

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

    //! Construct object MathReceiverTester
    MathReceiverTester();

    //! Destroy object MathReceiverTester
    ~MathReceiverTester();

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    void testAdd();

    void testSub();

    void testThrottle();

  private:
    // ----------------------------------------------------------------------
    // Helper functions
    // ----------------------------------------------------------------------

    F32 pickF32Value();

    void setFactor(F32 factor, ThrottleState throttleState);
    
    void doMathOp(MathOp op, F32 factor);

    F32 computeResult(F32 val1, MathOp op, F32 val2, F32 factor);

    //! Connect ports
    void connectPorts();

    //! Initialize components
    void initComponents();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The component under test
    MathReceiver component;
};

}  // namespace ObcProject

#endif
