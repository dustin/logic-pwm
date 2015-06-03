#include "PWMSimulationDataGenerator.h"
#include "PWMAnalyzerSettings.h"

#include <AnalyzerHelpers.h>

PWMSimulationDataGenerator::PWMSimulationDataGenerator() : rgen(),
                                                           rdist(.5),
                                                           pulseLen(1500)
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
        double by = 10*rdist(rgen)*(rgen()&1?1:-1);
        pulseLen += (pulseLen+by > 2000 || pulseLen+by < 1000) ? -by : by;

        mPWMSimulationData.Advance(mSimulationSampleRateHz / 50);

        mPWMSimulationData.TransitionIfNeeded(BIT_HIGH);
        mPWMSimulationData.Advance(mClockGenerator.AdvanceByTimeS(pulseLen * 1E-6));
        mPWMSimulationData.TransitionIfNeeded(BIT_LOW);
    }

    *simulation_channel = &mPWMSimulationData;
    return 1;
}
