#ifndef PWM_ANALYZER_H
#define PWM_ANALYZER_H

#include <Analyzer.h>
#include "PWMAnalyzerResults.h"
#include "PWMSimulationDataGenerator.h"

class PWMAnalyzerSettings;
class ANALYZER_EXPORT PWMAnalyzer : public Analyzer2
{
public:
    PWMAnalyzer();
    virtual ~PWMAnalyzer();
    virtual void WorkerThread();
    virtual void SetupResults();

    virtual U32 GenerateSimulationData(U64 newest_sample_requested,
                                       U32 sample_rate,
                                       SimulationChannelDescriptor **simulation_channels);
    virtual U32 GetMinimumSampleRateHz();

    virtual const char *GetAnalyzerName() const;
    virtual bool NeedsRerun();

    double DutyCycle(U64 start, U64 mid, U64 end) { return 100.0 * double(mid-start) / double(end-start); }
    double Width(U64 l, U64 m) { return SamplesToUs(m - l); }
    double Value(U64 l, U64 m, U64 e);

protected: //vars
    std::auto_ptr< PWMAnalyzerSettings > mSettings;
    std::auto_ptr< PWMAnalyzerResults > mResults;
    AnalyzerChannelData *mPWM;

    PWMSimulationDataGenerator mSimulationDataGenerator;
    bool mSimulationInitilized;

    double SamplesToUs(U64 samples);

    //PWM analysis vars:
    U32 mSampleRateHz;
};

extern "C" ANALYZER_EXPORT const char *__cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer *__cdecl CreateAnalyzer();
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer(Analyzer *analyzer);

#endif //PWM_ANALYZER_H
