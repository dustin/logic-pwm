#ifndef PWM_SIMULATION_DATA_GENERATOR
#define PWM_SIMULATION_DATA_GENERATOR

#include <AnalyzerHelpers.h>

#include <SimulationChannelDescriptor.h>
class PWMAnalyzerSettings;

class PWMSimulationDataGenerator
{
public:
    PWMSimulationDataGenerator();
    ~PWMSimulationDataGenerator();

    void Initialize(U32 simulation_sample_rate, PWMAnalyzerSettings *settings);
    U32 GenerateSimulationData(U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor **simulation_channel);

protected:
    PWMAnalyzerSettings *mSettings;
    U32 mSimulationSampleRateHz;

protected:
    SimulationChannelDescriptor mPWMSimulationData;
    ClockGenerator mClockGenerator;

    void Pulse(double duration);

    double pulseLen;
    double incr;

};
#endif //PWM_SIMULATION_DATA_GENERATOR
