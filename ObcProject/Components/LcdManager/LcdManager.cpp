// ======================================================================
// \title  LcdManager.cpp
// \author fsowa
// \brief  cpp file for LcdManager component implementation class
// ======================================================================

#include "ObcProject/Components/LcdManager/LcdManager.hpp"

namespace ObcProject {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

LcdManager ::LcdManager(const char* const compName) : LcdManagerComponentBase(compName),
    comm("TCP Client") {
    Fw::String hostname{"192.168.0.115"};
    U16 port_number = 9999;
    comm.configure(hostname.toChar(), port_number);

    Os::TaskString name("ReceiveTask");
    comm.start(name);

    char hello[] = "hello";
    // Fw::Buffer buffer{reinterpret_cast<U8*>(hello), 5};
    auto hello_c = reinterpret_cast<const U8*>(hello);
    comm.send(hello_c, 5);
}

LcdManager ::~LcdManager() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void LcdManager ::imu_data_handler(FwIndexType portNum, const MpuImu::ImuData& data) {
}

void LcdManager ::tcpRecv_handler(FwIndexType portNum, Fw::Buffer& buffer, const Drv::ByteStreamStatus& status) {
    // TODO
}

}  // namespace ObcProject
