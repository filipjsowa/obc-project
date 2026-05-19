// ======================================================================
// \title  ServoComponent.hpp
// \author diegoalmendrow
// \brief  hpp file for ServoComponent component implementation class
// ======================================================================

#ifndef ObcProject_ServoComponent_HPP
#define ObcProject_ServoComponent_HPP

#include "ObcProject/Components/ServoComponent/ServoComponentComponentAc.hpp"
#include <atomic>
#ifdef HAVE_PIGPIO
#include "/opt/pigpio/include/pigpio.h"
#endif

namespace ObcProject {

class ServoComponent final : public ServoComponentComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct ServoComponent object
    ServoComponent(const char* const compName, int gpioPin = 18  //!< The component name
    );

    //! Destroy ServoComponent object
    ~ServoComponent();
    int setAngle(float angle);
    bool isReady() const;
    int status() const;

    void preamble();

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
    int m_gpio;
    int m_status;
    bool m_ready;
    bool m_registered;
    int s_users{0};
    bool s_initialized{false};
    std::atomic<bool> m_overwritten{false};
        
    //! Handler implementation for angleIn
    void angleIn_handler(FwIndexType portNum,  //!< The port number
                         F32 result            //!< the result of the operation
                         ) override;

    int angleToPulseUs(float angle) const;
};

}  // namespace ObcProject

#endif
