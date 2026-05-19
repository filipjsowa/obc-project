// ======================================================================
// \title  Orchestrator.cpp
// \author fsowa
// \brief  cpp file for Orchestrator component implementation class
// ======================================================================

#include "ObcProject/Components/Orchestrator/Orchestrator.hpp"
#include "Fw/Logger/Logger.hpp"

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
    //we only want to update the LCD every 2 seconds
    skip++;
    if (skip == 40){
        skip = 0;
        this->imu_data_out_out(0, data);
    }
    this->imu_data_for_angle_out(0, data.get_acceleration().get_x(), MathOp::ANG, data.get_acceleration().get_z());
}

}  // namespace ObcProject
