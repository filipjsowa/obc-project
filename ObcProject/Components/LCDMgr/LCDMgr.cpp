// ======================================================================
// \title  LCDMgr.cpp
// \author guife
// \brief  cpp file for LCDMgr component implementation class
// ======================================================================

#include "ObcProject/Components/LCDMgr/LCDMgr.hpp"

namespace ObcProject {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

LCDMgr ::LCDMgr(const char* const compName) : LCDMgrComponentBase(compName) {
    memset(m_cmdBuf, 0, sizeof(m_cmdBuf));
}

LCDMgr ::~LCDMgr() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void LCDMgr ::printLine_handler(FwIndexType portNum, U8 line_number, const Fw::StringBase& content) {
    this->printLine(line_number, content);
}

void LCDMgr ::run_handler(FwIndexType portNum, U32 context) {
    // TODO
}

void LCDMgr ::recv_handler(FwIndexType portNum, Fw::Buffer& buffer, const Drv::ByteStreamStatus& status) {
    if (this->isConnected_deallocate_OutputPort(0)) {
        this->deallocate_out(0, buffer);
    }
}
// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void LCDMgr ::PRINT_LINE_TEST_cmdHandler(FwOpcodeType opCode,
                                         U32 cmdSeq,
                                         U8 line_number,
                                         const Fw::CmdStringArg& content) {
    // TODO
    bool success = this->printLine(line_number, content);
    this->cmdResponse_out(opCode, cmdSeq, success ? Fw::CmdResponse::OK : Fw::CmdResponse::EXECUTION_ERROR);
}

void LCDMgr ::LCD_RESET_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

// ----------------------------------------------------------------------
// Helper functions
// ----------------------------------------------------------------------

// Fw::Success ?
bool LCDMgr ::sendCommand(const U8* data, U32 len) {
    FW_ASSERT(data != nullptr);
    FW_ASSERT(len > 0 && len < CMD_BUF_SIZE);

    if (!this->isConnected_uartWrite_OutputPort(0)) {
        return false;
    }

    Fw::Buffer buf(const_cast<U8*>(data), len);

    Drv::ByteStreamStatus status = this->uartWrite_out(0, buf);

    if (status != Drv::ByteStreamStatus::OP_OK) {
        this->log_WARNING_HI_LcdSendError(static_cast<I32>(status.e));
        return false;
    }

    return true;
}

bool LCDMgr ::printLine(U8 line_number, const Fw::StringBase& content) {
    // Build the LCD protocol command: "PRINT_LINE <line_number> <content>\n"
    I32 bytes_written = snprintf(reinterpret_cast<char*>(m_cmdBuf), CMD_BUF_SIZE, "PRINT_LINE %u %s\n",
                                 static_cast<unsigned>(line_number), content.toChar());

    // Fw::Success
    bool success = false;
    if (bytes_written > 0 && bytes_written < static_cast<I32>(CMD_BUF_SIZE)) {
        success = sendCommand(m_cmdBuf, static_cast<U32>(bytes_written));
    }

    if (success) {
        this->tlmWrite_LinesWritten(++m_linesWritten);
        this->log_ACTIVITY_LO_LcdPrintLine(line_number, content);
    } else {
        this->tlmWrite_ErrorCount(++m_errorCount);
    }

    return success;
}

}  // namespace ObcProject
