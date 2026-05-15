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

LcdManager ::LcdManager(const char* const compName) : LcdManagerComponentBase(compName) {}

LcdManager ::~LcdManager() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void LcdManager ::imu_data_handler(FwIndexType portNum, const MpuImu::ImuData& data) {
    // TODO
}

}  // namespace ObcProject
