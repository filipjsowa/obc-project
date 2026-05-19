// ======================================================================
// \title  MathReceiver.hpp
// \author otsii
// \brief  hpp file for MathReceiver component implementation class
// ======================================================================

#ifndef ObcProject_MathReceiver_HPP
#define ObcProject_MathReceiver_HPP

#include "ObcProject/Components/MathReceiver/MathReceiverComponentAc.hpp"

namespace ObcProject {

class MathReceiver final : public MathReceiverComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct MathReceiver object
    MathReceiver(const char* const compName  //!< The component name
    );

    //! Destroy MathReceiver object
    ~MathReceiver();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    U32 numMathOps;

    //! Handler implementation for mathOpIn
    //!
    //! Port for receiving the math operation
    void mathOpIn_handler(FwIndexType portNum,            //!< The port number
                          F32 val1,                       //!< The first operand
                          const ObcProject::MathOp& op,  //!< The operation
                          F32 val2                        //!< The second operand
                          ) override;

    //! Handler implementation for schedIn
    //!
    //! The rate group scheduler input
    void schedIn_handler(FwIndexType portNum,  //!< The port number
                         U32 context           //!< The call order
                         ) override;

    // In: MathReceiver.hpp
    // As a Private under: Handler implementations for user-defined typed input ports
    void parameterUpdated(FwPrmIdType id) override;

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command CLEAR_EVENT_THROTTLE
    //!
    //! Clear the event throttle
    void CLEAR_EVENT_THROTTLE_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                                         U32 cmdSeq            //!< The command sequence number
                                         ) override;
};

}  // namespace ObcProject

#endif
