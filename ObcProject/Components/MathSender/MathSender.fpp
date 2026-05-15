# In: MathSender.fpp
module MathProject {

  @ Component for sending a math operation
  active component MathSender {

    # ----------------------------------------------------------------------
    # General ports
    # ----------------------------------------------------------------------

    @ Port for sending the operation request
    output port mathOpOut: OpRequest

    @ Port for receiving the result
    async input port mathResultIn: MathResult

    # ----------------------------------------------------------------------
    # Special ports
    # ----------------------------------------------------------------------

    @ Command receive port
    command recv port cmdIn

    @ Command registration port
    command reg port cmdRegOut

    @ Command response port
    command resp port cmdResponseOut

    @ Event port
    event port eventOut

    @ Telemetry port
    telemetry port tlmOut

    @ Text event port
    text event port textEventOut

    @ Time get port
    time get port timeGetOut

    # ----------------------------------------------------------------------
    # Commands
    # ----------------------------------------------------------------------

    @ Do a math operation
    async command DO_MATH(
                           val1: F32 @< The first operand
                           op: MathOp @< The operation
                           val2: F32 @< The second operand
                         )
    
    @ Automatically calculate angle from X and Z
    async command AUTO_ANGLE


    # ----------------------------------------------------------------------
    # Events
    # ----------------------------------------------------------------------

    @ Math command received
    event COMMAND_RECV(
                        val1: F32 @< The first operand
                        op: MathOp @< The operation
                        val2: F32 @< The second operand
                      ) \
      severity activity low \
      format "Math command received: {f} {} {f}"

    @ Received math result
    event RESULT(
                  result: F32 @< The math result
                ) \
      severity activity high \
      format "Math result is {f}"

    @ Spacecraft angle computed
    event ANGLE(
                  angle: F32 @< Calculated spacecraft angle
                ) \
      severity activity high \
      format "Spacecraft angle is {f} deg"

    # ----------------------------------------------------------------------
    # Telemetry
    # ----------------------------------------------------------------------

    @ The first value
    telemetry VAL1: F32

    @ The operation
    telemetry OP: MathOp

    @ The second value
    telemetry VAL2: F32

    @ The result
    telemetry RESULT: F32

    @ X value
    telemetry X_VAL: F32

    @ Z value
    telemetry Z_VAL: F32

    @ Calculated angle in degrees
    telemetry ANGLE: F32

  }

}