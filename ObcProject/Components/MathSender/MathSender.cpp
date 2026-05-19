// ======================================================================
// \title  MathSender.cpp
// \author otsii
// \brief  cpp file for MathSender component implementation class
// ======================================================================

#include "ObcProject/Components/MathSender/MathSender.hpp"
#include <cmath>

namespace ObcProject {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

MathSender ::MathSender(const char* const compName) : MathSenderComponentBase(compName) {}

MathSender ::~MathSender() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void MathSender ::
  mathResultIn_handler(
      const FwIndexType portNum,
      F32 result
  )
{
    this->tlmWrite_RESULT(result);
    this->log_ACTIVITY_HI_RESULT(result);
}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void MathSender ::
  DO_MATH_cmdHandler(
      const FwOpcodeType opCode,
      const U32 cmdSeq,
      F32 val1,
      MathOp op,
      F32 val2
  )
{
  this->tlmWrite_VAL1(val1);
  this->tlmWrite_OP(op);
  this->tlmWrite_VAL2(val2);
  this->log_ACTIVITY_LO_COMMAND_RECV(val1, op, val2);
  this->mathOpOut_out(0, val1, op, val2);
  this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void MathSender ::
  AUTO_ANGLE_cmdHandler(
      const FwOpcodeType opCode,
      const U32 cmdSeq
  )
{
    // Placeholder values
    F32 x = 10.0f;
    F32 z = 5.0f;

    // Calculate angle in degrees
    F32 angle =
        std::atan2(x, z) * 180.0f / 3.14159265f;

    // Send telemetry
    this->tlmWrite_X_VAL(x);
    this->tlmWrite_Z_VAL(z);
    this->tlmWrite_ANGLE(angle);

    // Log result
    this->log_ACTIVITY_HI_ANGLE(angle);

    // Complete command
    this->cmdResponse_out(
        opCode,
        cmdSeq,
        Fw::CmdResponse::OK
    );
}

}  // namespace ObcProject
