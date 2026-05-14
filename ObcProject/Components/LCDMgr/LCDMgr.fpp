module ObcProject {
    @ Component for F Prime FSW framework.
    passive component LCDMgr {

        # ----------------------------------------------------------------------
        # Commands
        # ----------------------------------------------------------------------

        @ Command to print string in LCD
        sync command PRINT_LINE_TEST(
            line_number: U8
            content: string size 20 @< Text to printed in the LCD
        )
        @ Reset LCD
        sync command LCD_RESET

        # ----------------------------------------------------------------------
        # Parameters
        # ----------------------------------------------------------------------

        @ Font size on LCD
        param FONT_SIZE: U8 \
            default 1

        @ Background Color
        param BACKGROUND_COLOR: LCDColor \
            default LCDColor.BLACK

        # ----------------------------------------------------------------------
        # Telemetry
        # ----------------------------------------------------------------------

        telemetry LinesWritten: U32
        telemetry ResetCount: U32
        telemetry ErrorCount: U32

        # ----------------------------------------------------------------------
        # Events
        # ----------------------------------------------------------------------

        event LcdPrintLine(line: U8, content: string size 64) \
            severity activity low \
            format "LCD print line {}: {}"

        event LcdReset() \
            severity activity low \
            format "LCD was reset"

        event LcdSetBackground(color: string size 16) \
            severity activity low \
            format "LCD background set to {}"

        # ----------------------------------------------------------------------
        # Ports
        # ----------------------------------------------------------------------

        @ Input ports for other components to print data
        sync input port printLine: ObcProject.LcdLine

        @ Port receiving calls from the rate group
        sync input port run: Svc.Sched

        @ UART Send Port
        output port uartWrite: Drv.ByteStreamSend

        @ UART Receive Port
        sync input port $recv: Drv.ByteStreamData

        @ Return received buffers to the buffer manager
        output port deallocate: Fw.BufferSend

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

    }
}
