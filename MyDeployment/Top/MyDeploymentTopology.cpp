// ======================================================================
// \title  MyDeploymentTopology.cpp
// \brief cpp file containing the topology instantiation code
//
// ======================================================================
// Provides access to autocoded functions
#include <MyDeployment/Top/MyDeploymentTopologyAc.hpp>
// Note: Uncomment when using Svc:TlmPacketizer
// #include <MyDeployment/Top/MyDeploymentPacketsAc.hpp>

// Necessary project-specified types
#include <Fw/Types/MallocAllocator.hpp>

#include <Fw/Logger/Logger.hpp>
#include <Svc/BufferManager/BufferManager.hpp>

// Public functions for use in main program are namespaced with deployment module MyDeployment
// This is also the namespace where the topology components are instantiated by FPP.
namespace MyDeployment {

// Instantiate a malloc allocator for cmdSeq buffer allocation
Fw::MallocAllocator mallocator;

// Allocator for UART buffer manager
Fw::MallocAllocator uartBufAllocator;

// The reference topology divides the incoming clock signal (1Hz) into sub-signals: 1Hz, 1/2Hz, and 1/4Hz with 0 offset
Svc::RateGroupDriver::DividerSet rateGroupDivisorsSet{{{1, 0}, {2, 0}, {4, 0}}};

// Rate groups may supply a context token to each of the attached children whose purpose is set by the project. The
// reference topology sets each token to zero as these contexts are unused in this project.
U32 rateGroup1Context[Svc::ActiveRateGroup::CONNECTION_COUNT_MAX] = {};
U32 rateGroup2Context[Svc::ActiveRateGroup::CONNECTION_COUNT_MAX] = {};
U32 rateGroup3Context[Svc::ActiveRateGroup::CONNECTION_COUNT_MAX] = {};

enum TopologyConstants {
    COMM_PRIORITY = 34,
};

static constexpr const char* UART_DEVICE = "/dev/ttyUSB0";
static constexpr U32 UART_BUF_SIZE = 1024;
static constexpr U32 UART_BUF_COUNT = 10;

/**
 * \brief configure/setup components in project-specific way
 *
 * This is a *helper* function which configures/sets up each component requiring project specific input. This includes
 * allocating resources, passing-in arguments, etc. This function may be inlined into the topology setup function if
 * desired, but is extracted here for clarity.
 */
void configureTopology() {
    // Rate group driver needs a divisor list
    rateGroupDriver.configure(rateGroupDivisorsSet);

    // Rate groups require context arrays.
    rateGroup1.configure(rateGroup1Context, FW_NUM_ARRAY_ELEMENTS(rateGroup1Context));
    rateGroup2.configure(rateGroup2Context, FW_NUM_ARRAY_ELEMENTS(rateGroup2Context));
    rateGroup3.configure(rateGroup3Context, FW_NUM_ARRAY_ELEMENTS(rateGroup3Context));

    // Command sequencer needs to allocate memory to hold contents of command sequences
    cmdSeq.allocateBuffer(0, mallocator, 5 * 1024);

    // Configure buffer manager before opening the UART driver.
    Svc::BufferManager::BufferBins bins;
    ::memset(&bins, 0, sizeof(bins));
    bins.bins[0].bufferSize = UART_BUF_SIZE;  // must match recv size in open()
    bins.bins[0].numBuffers = UART_BUF_COUNT;

    uartBufMgr.setup(1,  // mgrId  — arbitrary, unique per manager instance
                     0,  // memId  — segment ID, 0 for MallocAllocator
                     uartBufAllocator, bins);

    bool open_success = uartDrv.open(UART_DEVICE, Drv::LinuxUartDriver::BAUD_115K, Drv::LinuxUartDriver::NO_FLOW,
                                     Drv::LinuxUartDriver::PARITY_NONE, UART_BUF_SIZE);
    if (open_success) {
        uartDrv.start();
    } else {
        Fw::Logger::log("Failed to open UART %s\n", UART_DEVICE);
    }
}

void setupTopology(const TopologyState& state) {
    // Autocoded initialization. Function provided by autocoder.
    initComponents(state);
    // Autocoded id setup. Function provided by autocoder.
    setBaseIds();
    // Autocoded connection wiring. Function provided by autocoder.
    connectComponents();
    // Autocoded command registration. Function provided by autocoder.
    regCommands();
    // Autocoded configuration. Function provided by autocoder.
    configComponents(state);
    if (state.hostname != nullptr && state.port != 0) {
        comDriver.configure(state.hostname, state.port);
    }
    // Project-specific component configuration. Function provided above. May be inlined, if desired.
    configureTopology();
    // Autocoded parameter loading. Function provided by autocoder.
    loadParameters();
    // Autocoded task kick-off (active components). Function provided by autocoder.
    startTasks(state);
    // Initialize socket communication if and only if there is a valid specification
    if (state.hostname != nullptr && state.port != 0) {
        Os::TaskString name("ReceiveTask");
        // Uplink is configured for receive so a socket task is started
        comDriver.start(name, COMM_PRIORITY, Default::STACK_SIZE);
    }
}

void startRateGroups(const Fw::TimeInterval& interval) {
    // The timer component drives the fundamental tick rate of the system.
    // Svc::RateGroupDriver will divide this down to the slower rate groups.
    // This call will block until the stopRateGroups() call is made.
    // For this Linux demo, that call is made from a signal handler.
    timer.startTimer(interval);
}

void stopRateGroups() {
    timer.quit();
}

void teardownTopology(const TopologyState& state) {
    // Autocoded (active component) task clean-up. Functions provided by topology autocoder.
    stopTasks(state);
    freeThreads(state);

    // Other task clean-up.
    comDriver.stop();
    (void)comDriver.join();

    uartDrv.quitReadThread();
    uartDrv.join();

    // Resource deallocation
    cmdSeq.deallocateBuffer(mallocator);

    tearDownComponents(state);
    deinitComponents(state);
}
};  // namespace MyDeployment
