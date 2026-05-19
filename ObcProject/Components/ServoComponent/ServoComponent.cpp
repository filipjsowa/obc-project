// ======================================================================
// \title  ServoComponent.cpp
// \author diegoalmendrow
// \brief  cpp file for ServoComponent component implementation class
// ======================================================================

#include "ObcProject/Components/ServoComponent/ServoComponent.hpp"
#include "Fw/Logger/Logger.hpp"

namespace ObcProject {

void ServoComponent::preamble(){
     if (!s_initialized) {
        #ifdef HAVE_PIGPIO
            const int initStatus = gpioInitialise();
        #else 
            const int initStatus = 0;
        #endif
        if (initStatus < 0) {
            m_status = initStatus;
            return;
        }
        s_initialized = true;
    }

    s_users += 1;
    m_registered = true;

    #ifdef HAVE_PIGPIO
    m_status = gpioSetMode(m_gpio, PI_OUTPUT);
    #endif 
    if (m_status < 0) {
        return;
    }
    
    #ifdef HAVE_PIGPIO
    m_status = gpioSetPWMfrequency(m_gpio, 50);
    #endif 
    if (m_status < 0) {
        return;
    }

    #ifdef HAVE_PIGPIO
    m_status = gpioServo(m_gpio, 1500);
    #endif 

    if (m_status < 0) {
        return;
    }

    m_status = 0;
    m_ready = true;
}

int ServoComponent::angleToPulseUs(float angle) const
{
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;

    return 1000 + (int)((angle / 180.0f) * 1000.0f);
}

int ServoComponent::setAngle(float angle)
{
    if (!m_ready) {
        return m_status;
    }
    const int pulse = angleToPulseUs(angle);
    #ifdef HAVE_PIGPIO
    m_status = gpioServo(m_gpio, pulse);
    #endif

    return m_status;
}

bool ServoComponent::isReady() const
{
    return m_ready;
}


int ServoComponent::status() const
{
    return m_status;
}
// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

ServoComponent::ServoComponent(const char* const compName, int gpioPin)
    : ServoComponentComponentBase(compName)
    , m_gpio(gpioPin)
{}

ServoComponent ::~ServoComponent() {
    if (!m_registered) {
        return;
    }

    #ifdef HAVE_PIGPIO
    (void) gpioServo(m_gpio, 0);
    #endif 
    s_users -= 1;

    if (s_users == 0 && s_initialized) {
        #ifdef HAVE_PIGPIO
        gpioTerminate();
        #endif 
        s_initialized = false;
    }
}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void ServoComponent::SET_ANGLE_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, F32 angle)
{
    // m_overwritten = !m_overwritten;
    if (angle < 0.0f || angle > 180.0f) {

        this->log_WARNING_HI_InvalidAngle(angle);

        this->cmdResponse_out(
            opCode,
            cmdSeq,
            Fw::CmdResponse::VALIDATION_ERROR
        );

        return;
    }

    if (!isReady()) {
        this->log_WARNING_HI_PigpioError(status());
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }

    const int pigpioStatus = setAngle(angle);
    if (pigpioStatus < 0) {
        this->log_WARNING_HI_PigpioError(pigpioStatus);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }


    this->tlmWrite_Angle(angle);

    this->log_ACTIVITY_HI_AngleSet(angle);

    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}


void ServoComponent ::angleIn_handler(FwIndexType portNum, F32 angle) {
    // if(!m_overwritten){
        Fw::String angle_s;
        angle_s.format("angle is %f\n", angle);
        Fw::Logger::log(angle_s);

        if (angle < 0.0f || angle > 180.0f) {

            this->log_WARNING_HI_InvalidAngle(angle);

            return;
        }

        if (!isReady()) {
            this->log_WARNING_HI_PigpioError(status());
            return;
        }



        int pigpioStatus = setAngle(angle);
        if (pigpioStatus < 0) {
            this->log_WARNING_HI_PigpioError(pigpioStatus);
            return;
        }
        // }
}

}  // namespace ObcProject
