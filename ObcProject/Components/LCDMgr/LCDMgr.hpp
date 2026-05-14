// ======================================================================
// \title  LCDMgr.hpp
// \author guife
// \brief  hpp file for LCDMgr component implementation class
// ======================================================================

#ifndef ObcProject_LCDMgr_HPP
#define ObcProject_LCDMgr_HPP

#include "ObcProject/Components/LCDMgr/LCDMgrComponentAc.hpp"

namespace ObcProject {

class LCDMgr final : public LCDMgrComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct LCDMgr object
    LCDMgr(const char* const compName  //!< The component name
    );

    //! Destroy LCDMgr object
    ~LCDMgr();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for printLine
    //!
    //! Input ports for other components to print data
    void printLine_handler(FwIndexType portNum,  //!< The port number
                           U8 line_number,
                           const Fw::StringBase& content) override;

    //! Handler implementation for run
    //!
    //! Port receiving calls from the rate group
    void run_handler(FwIndexType portNum,  //!< The port number
                     U32 context           //!< The call order
                     ) override;

    //! Handler implementation for recv
    //!
    //! UART Receive Port
    void recv_handler(FwIndexType portNum,  //!< The port number
                      Fw::Buffer& buffer,
                      const Drv::ByteStreamStatus& status) override;

  private:
    // Telemetry counters
    U32 m_linesWritten;
    U32 m_resetCount;
    U32 m_errorCount;

    static constexpr U32 CMD_BUF_SIZE = 128;
    U8 m_cmdBuf[CMD_BUF_SIZE];

    bool sendCommand(const U8* cmd, U32 len);
    bool printLine(U8 line_number, const Fw::StringBase& content);
    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command PRINT_LINE_TEST
    //!
    //! Command to print string in LCD
    void PRINT_LINE_TEST_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                                    U32 cmdSeq,           //!< The command sequence number
                                    U8 line_number,
                                    const Fw::CmdStringArg& content  //!< Text to printed in the LCD
                                    ) override;

    //! Handler implementation for command LCD_RESET
    //!
    //! Reset LCD
    void LCD_RESET_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                              U32 cmdSeq            //!< The command sequence number
                              ) override;
};

}  // namespace ObcProject

#endif
