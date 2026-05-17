// ======================================================================
// \title  ServoComponent.hpp
// \author diegoalmendrow
// \brief  hpp file for ServoComponent component implementation class
// ======================================================================

#ifndef ObcProject_ServoComponent_HPP
#define ObcProject_ServoComponent_HPP

#include "ObcProject/Components/ServoComponent/ServoComponentComponentAc.hpp"
#include <pigpio.h>
// #include "pigpio.h"

namespace ObcProject {

class ServoDriver {

public:

    ServoDriver(int gpio);

    void setAngle(float angle);

private:

    int m_gpio;

    int angleToPulseUs(float angle);

};

class ServoComponent final : public ServoComponentComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct ServoComponent object
    ServoComponent(const char* const compName  //!< The component name
    );

    //! Destroy ServoComponent object
    ~ServoComponent();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command TODO
    //!
    //! TODO
    void SET_ANGLE_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                         U32 cmdSeq,            //!< The command sequence number
                         F32 angle              //!< The angle to set
                         ) override;
  
  private:
    ServoDriver m_servo{18};  // GPIO pin 18 (PWM0)
};

}  // namespace ObcProject

#endif
