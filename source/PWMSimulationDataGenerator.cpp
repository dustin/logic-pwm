#include "PWMSimulationDataGenerator.h"
#include "PWMAnalyzerSettings.h"

#include <AnalyzerHelpers.h>

PWMSimulationDataGenerator::PWMSimulationDataGenerator()
{
}

PWMSimulationDataGenerator::~PWMSimulationDataGenerator()
{
}

void PWMSimulationDataGenerator::Initialize(U32 simulation_sample_rate,
                                            PWMAnalyzerSettings *settings)
{
    mSimulationSampleRateHz = simulation_sample_rate;
    mSettings = settings;

    pulseLen = 1000;
    incr = 13;

    mPWMSimulationData.SetChannel(mSettings->mInputChannel);
    mPWMSimulationData.SetSampleRate(simulation_sample_rate);
    mPWMSimulationData.SetInitialBitState(BIT_LOW);

    mClockGenerator.Init(1000000, simulation_sample_rate);
}

U32 PWMSimulationDataGenerator::GenerateSimulationData(U64 largest_sample_requested,
                                                       U32 sample_rate,
                                                       SimulationChannelDescriptor **simulation_channel)
{
    U64 adjusted_largest_sample_requested = AnalyzerHelpers::AdjustSimulationTargetSample(largest_sample_requested,
                                            sample_rate,
                                            mSimulationSampleRateHz);

    while (mPWMSimulationData.GetCurrentSampleNumber() < adjusted_largest_sample_requested) {
        Pulse(pulseLen);
        pulseLen += incr;
        if (pulseLen > 2000) {
            pulseLen -= incr;
            incr = -incr;
        } else if (pulseLen < 1000) {
            pulseLen += incr;
            incr = -incr;
        }
    }

    *simulation_channel = &mPWMSimulationData;
    return 1;
}

void PWMSimulationDataGenerator::Pulse(double duration)
{
    mPWMSimulationData.Advance(mSimulationSampleRateHz / 50);

    mPWMSimulationData.TransitionIfNeeded(BIT_HIGH);
    mPWMSimulationData.Advance(mClockGenerator.AdvanceByTimeS(duration * 1E-6));
    mPWMSimulationData.TransitionIfNeeded(BIT_LOW);
}
