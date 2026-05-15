// ======================================================================
// \title  Orchestrator.hpp
// \author fsowa
// \brief  hpp file for Orchestrator component implementation class
// ======================================================================

#ifndef ObcProject_Orchestrator_HPP
#define ObcProject_Orchestrator_HPP

#include "ObcProject/Components/Orchestrator/OrchestratorComponentAc.hpp"

namespace ObcProject {

class Orchestrator final : public OrchestratorComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct Orchestrator object
    Orchestrator(const char* const compName  //!< The component name
    );

    //! Destroy Orchestrator object
    ~Orchestrator();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for imu_data
    //!
    //! Get data from the imu
    void imu_data_handler(FwIndexType portNum,  //!< The port number
                          const MpuImu::ImuData& data) override;
};

}  // namespace ObcProject

#endif
