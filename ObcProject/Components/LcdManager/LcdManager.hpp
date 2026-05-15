// ======================================================================
// \title  LcdManager.hpp
// \author fsowa
// \brief  hpp file for LcdManager component implementation class
// ======================================================================

#ifndef ObcProject_LcdManager_HPP
#define ObcProject_LcdManager_HPP

#include "ObcProject/Components/LcdManager/LcdManagerComponentAc.hpp"

namespace ObcProject {

class LcdManager final : public LcdManagerComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct LcdManager object
    LcdManager(const char* const compName  //!< The component name
    );

    //! Destroy LcdManager object
    ~LcdManager();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for imu_data
    void imu_data_handler(FwIndexType portNum,  //!< The port number
                          const MpuImu::ImuData& data) override;
};

}  // namespace ObcProject

#endif
