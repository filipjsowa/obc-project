// ======================================================================
// \title  MathSender.hpp
// \author otsii
// \brief  hpp file for MathSender component implementation class
// ======================================================================

#ifndef ObcProject_MathSender_HPP
#define ObcProject_MathSender_HPP

#include "ObcProject/Components/MathSender/MathSenderComponentAc.hpp"

namespace ObcProject {

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
                            ObcProject::MathOp op,  //!< The operation
                            F32 val2                 //!< The second operand
                            ) override;
                        
    void AUTO_ANGLE_cmdHandler(FwOpcodeType opCode,
                              U32 cmdSeq
                              ) override;

};

}  // namespace ObcProject

#endif
