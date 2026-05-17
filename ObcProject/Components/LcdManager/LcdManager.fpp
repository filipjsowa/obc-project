module ObcProject {
    @ Manager for the lcd
    passive component LcdManager {

        # # One async command/port is required for active components
        # # This should be overridden by the developers with a useful command/port
        # @ TODO
        # async command TODO opcode 0

        ##############################################################################
        #### Uncomment the following examples to start customizing your component ####
        ##############################################################################

        # @ Example async command
        # async command COMMAND_NAME(param_name: U32)

        # @ Example telemetry counter
        # telemetry ExampleCounter: U64

        # @ Example event
        # event ExampleStateEvent(example_state: Fw.On) severity activity high id 0 format "State set to {}"

        # @ Example port: receiving calls from the rate group
        # sync input port run: Svc.Sched

        # @ Example parameter
        # param PARAMETER_NAME: U32

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Enables command handling
        import Fw.Command

        @ Enables event handling
        import Fw.Event

        @ Enables telemetry channels handling
        import Fw.Channel

        @ Port to return the value of a parameter
        param get port prmGetOut

        @Port to set the value of a parameter
        param set port prmSetOut

        sync input port imu_data: MpuImu.ImuDataPort

        output port tcpSend: Drv.ByteStreamSend

        guarded input port tcpRecv: Drv.ByteStreamData
        sync input port tcpReady: Drv.ByteStreamReady
        output port tcpRecvReturnIn: Fw.BufferSend



        @ Add allocation and deallocation output ports for interfacing with a BufferManager
        import Svc.BufferAllocation

        @ Allocation failed event
        event MemoryAllocationFailed() severity warning low id 0 format "Failed to allocate memory"

    }
}