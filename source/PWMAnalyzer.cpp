#include <cmath>

#include "PWMAnalyzer.h"
#include "PWMAnalyzerSettings.h"
#include <AnalyzerChannelData.h>

PWMAnalyzer::PWMAnalyzer()
    :   Analyzer2(),
        mSettings(new PWMAnalyzerSettings()),
        mSimulationInitilized(false),
        mSampleRateHz(0)
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
    if (mPWM->GetBitState() == BIT_LOW) {
        mPWM->AdvanceToNextEdge();
    }

    int type = mSettings->mAnalysisType;

    double prevval(0);
    for (;;) {
        U64 start = mPWM->GetSampleNumber(); // Rising
        mPWM->AdvanceToNextEdge();
        U64 mid = mPWM->GetSampleNumber(); // Falling
        mPWM->AdvanceToNextEdge();
        U64 end = mPWM->GetSampleNumber(); // Rising

        double val = Value(start, mid, end);
        if (std::abs(val - prevval) >= mSettings->mMinChange) {
            mResults->AddMarker(end - ((end - start) / 2),
                                val > prevval ? AnalyzerResults::UpArrow : AnalyzerResults::DownArrow,
                                mSettings->mInputChannel);

            Frame frame;
            frame.mData1 = mid;
            frame.mStartingSampleInclusive = start;
            frame.mEndingSampleInclusive = end;
            mResults->AddFrame(frame);
            mResults->CommitResults();
            ReportProgress(frame.mEndingSampleInclusive);

            prevval = val;
        }
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

double PWMAnalyzer::Value(U64 start, U64 mid, U64 end)
{
    return mSettings->mAnalysisType == ANALYSIS_WIDTH ? Width(start, mid) : DutyCycle(start, mid, end);
}
