// ======================================================================
// \title  Orchestrator.cpp
// \author fsowa
// \brief  cpp file for Orchestrator component implementation class
// ======================================================================

#include "ObcProject/Components/Orchestrator/Orchestrator.hpp"

namespace ObcProject {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

Orchestrator ::Orchestrator(const char* const compName) : OrchestratorComponentBase(compName) {}

Orchestrator ::~Orchestrator() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void Orchestrator ::imu_data_handler(FwIndexType portNum, const MpuImu::ImuData& data) {
    // Fw::String temp;
    // data.toString(temp);
    // log_ACTIVITY_HI_imuReceived(temp);
    this->imu_data_out_out(0, data);
}

}  // namespace ObcProject
