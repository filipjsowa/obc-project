// ======================================================================
// \title  MathSender.hpp
// \author otsii
// \brief  hpp file for MathSender component implementation class
// ======================================================================

#ifndef MathProject_MathSender_HPP
#define MathProject_MathSender_HPP

#include "MathProject/Components/MathSender/MathSenderComponentAc.hpp"

namespace MathProject {

class MathSender final : public MathSenderComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct MathSender object
    MathSender(const char* const compName  //!< The component name
    );

    //! Destroy MathSender object
    ~MathSender();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for mathResultIn
    //!
    //! Port for receiving the result
    void mathResultIn_handler(FwIndexType portNum,  //!< The port number
                              F32 result            //!< the result of the operation
                              ) override;

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command DO_MATH
    //!
    //! Do a math operation
    void DO_MATH_cmdHandler(FwOpcodeType opCode,     //!< The opcode
                            U32 cmdSeq,              //!< The command sequence number
                            F32 val1,                //!< The first operand
                            MathProject::MathOp op,  //!< The operation
                            F32 val2                 //!< The second operand
                            ) override;
                        
    void AUTO_ANGLE_cmdHandler(FwOpcodeType opCode,
                              U32 cmdSeq
                              ) override;

};

}  // namespace MathProject

#endif
