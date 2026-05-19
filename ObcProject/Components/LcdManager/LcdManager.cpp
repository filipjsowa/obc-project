// ======================================================================
// \title  LcdManager.cpp
// \author fsowa
// \brief  cpp file for LcdManager component implementation class
// ======================================================================

#include "ObcProject/Components/LcdManager/LcdManager.hpp"
#include "Fw/Logger/Logger.hpp"
#include "Fw/Types/StringUtils.hpp"
namespace ObcProject {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

LcdManager ::LcdManager(const char* const compName) : LcdManagerComponentBase(compName) {}

LcdManager ::~LcdManager() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void LcdManager::send_helper(const MpuImu::ImuData& data){
    Fw::String hello{};
    
    hello.format("PRINT_LINE,1,Acc x%f\0PRINT_LINE,2,Acc y%f\0PRINT_LINE,3,Acc z%f"
            ,data.get_acceleration().get_x()
            ,data.get_acceleration().get_y()
            ,data.get_acceleration().get_z());  

    
    // for null termination
    U32 needed_size = hello.length() + 1;
    Fw::Buffer my_buffer = this->allocate_out(0, needed_size);
    
    if (my_buffer.getSize() < needed_size) {
        this->deallocate_out(0, my_buffer);
        this->log_WARNING_LO_MemoryAllocationFailed();
    } else {
        my_buffer.setSize(needed_size);
        Fw::StringUtils::string_copy(
            reinterpret_cast<char*>(my_buffer.getData()), 
            hello.toChar(), 
            // +1 cause string_copy does NULL termination
            my_buffer.getSize() 
        );
        Drv::ByteStreamStatus tcp_send_status = this->tcpSend_out(0, my_buffer);
        // tcp_send_status should be handled, but it's good enough
        // with the basic driver handling

        this->deallocate_out(0, my_buffer);
    }
}

void LcdManager ::imu_data_handler(FwIndexType portNum, const MpuImu::ImuData& data) {
    if(m_tcpReady){
        send_helper(data);
    } else {
        Fw::Logger::log("Waiting for a connection!\n");
    }
}

void LcdManager::tcpReady_handler(FwIndexType portNum) {
    m_tcpReady = true;
}

void LcdManager ::tcpRecv_handler(FwIndexType portNum, Fw::Buffer& buffer, const Drv::ByteStreamStatus& status) {
    this->tcpRecvReturnIn_out(0, buffer);
}

}  // namespace ObcProject
