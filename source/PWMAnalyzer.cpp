#include <cmath>

#include "PWMAnalyzer.h"
#include "PWMAnalyzerSettings.h"
#include <AnalyzerChannelData.h>

PWMAnalyzer::PWMAnalyzer()
    :   Analyzer2(),
        mSettings(new PWMAnalyzerSettings()),
        mSimulationInitilized(false)
{
    SetAnalyzerSettings(mSettings.get());
}

PWMAnalyzer::~PWMAnalyzer()
{
    KillThread();
}

void PWMAnalyzer::SetupResults()
{
    mResults.reset(new PWMAnalyzerResults(this, mSettings.get()));
    SetAnalyzerResults(mResults.get());
    mResults->AddChannelBubblesWillAppearOn(mSettings->mInputChannel);
}

void PWMAnalyzer::WorkerThread()
{

    mSampleRateHz = GetSampleRate();

    mPWM = GetAnalyzerChannelData(mSettings->mInputChannel);

    // Wait for a clean start
    if (mPWM->GetBitState() == BIT_HIGH) {
        mPWM->AdvanceToNextEdge();
    }
    mPWM->AdvanceToNextEdge();

    double prev = 0;
    for (;;) {
        U64 start = mPWM->GetSampleNumber(); // Falling Edge

        mPWM->AdvanceToNextEdge();

        U64 end = mPWM->GetSampleNumber();
        U64 width = SamplesToUs(end - start);

        if (std::abs(double(width) - prev) >= mSettings->mMinChange) {
            mResults->AddMarker(end - ((end - start) / 2),
                                width > prev ? AnalyzerResults::UpArrow : AnalyzerResults::DownArrow,
                                mSettings->mInputChannel);

            //we have a byte to save.
            Frame frame;
            frame.mData1 = width;
            frame.mData2 = prev > 0 ? width - prev : 0;
            frame.mFlags = 0;
            frame.mStartingSampleInclusive = start;
            frame.mEndingSampleInclusive = mPWM->GetSampleNumber();

            mResults->AddFrame(frame);
            mResults->CommitResults();
            ReportProgress(frame.mEndingSampleInclusive);

            prev = width;
        }

        mPWM->AdvanceToNextEdge(); // Rising edge
    }
}

bool PWMAnalyzer::NeedsRerun()
{
    return false;
}

U32 PWMAnalyzer::GenerateSimulationData(U64 minimum_sample_index, U32 device_sample_rate, SimulationChannelDescriptor **simulation_channels)
{
    if (mSimulationInitilized == false) {
        mSimulationDataGenerator.Initialize(GetSimulationSampleRate(), mSettings.get());
        mSimulationInitilized = true;
    }

    return mSimulationDataGenerator.GenerateSimulationData(minimum_sample_index, device_sample_rate, simulation_channels);
}

U32 PWMAnalyzer::GetMinimumSampleRateHz()
{
    return 1000000;
}

const char *PWMAnalyzer::GetAnalyzerName() const
{
    return "PWM";
}

const char *GetAnalyzerName()
{
    return "PWM";
}

Analyzer *CreateAnalyzer()
{
    return new PWMAnalyzer();
}

void DestroyAnalyzer(Analyzer *analyzer)
{
    delete analyzer;
}

U64 PWMAnalyzer::SamplesToUs(U64 samples)
{
    return (samples * 1000000) / mSampleRateHz;
}
