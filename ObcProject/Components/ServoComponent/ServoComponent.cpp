// ======================================================================
// \title  ServoComponent.cpp
// \author diegoalmendrow
// \brief  cpp file for ServoComponent component implementation class
// ======================================================================

#include "ObcProject/Components/ServoComponent/ServoComponent.hpp"

namespace ObcProject {
ServoDriver::ServoDriver(int gpio)
: m_gpio(gpio)
{
    gpioInitialise();  //#########################################

}

int ServoDriver::angleToPulseUs(float angle)
{
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;

    return 1000 + (int)((angle / 180.0f) * 1000.0f);
}

void ServoDriver::setAngle(float angle)
{
    int pulse = angleToPulseUs(angle);

    gpioServo(m_gpio, pulse); //#########################################
}
// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

ServoComponent ::ServoComponent(const char* const compName) : ServoComponentComponentBase(compName) {}

ServoComponent ::~ServoComponent() {}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void ServoComponent::SET_ANGLE_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, F32 angle)
{
    if (angle < 0.0f || angle > 180.0f) {

        this->log_WARNING_HI_InvalidAngle(angle);

        this->cmdResponse_out(
            opCode,
            cmdSeq,
            Fw::CmdResponse::VALIDATION_ERROR
        );

        return;
    }

    m_servo.setAngle(angle);

    this->tlmWrite_Angle(angle);

    this->log_ACTIVITY_HI_AngleSet(angle);

    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // namespace ObcProject
