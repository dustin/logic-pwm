#ifndef PWM_ANALYZER_RESULTS
#define PWM_ANALYZER_RESULTS

#include <AnalyzerResults.h>

class PWMAnalyzer;
class PWMAnalyzerSettings;

class PWMAnalyzerResults : public AnalyzerResults
{
public:
    PWMAnalyzerResults(PWMAnalyzer *analyzer, PWMAnalyzerSettings *settings);
    virtual ~PWMAnalyzerResults();

    virtual void GenerateBubbleText(U64 frame_index, Channel &channel, DisplayBase display_base);
    virtual void GenerateExportFile(const char *file, DisplayBase display_base, U32 export_type_user_id);

    virtual void GenerateFrameTabularText(U64 frame_index, DisplayBase display_base);
    virtual void GeneratePacketTabularText(U64 packet_id, DisplayBase display_base);
    virtual void GenerateTransactionTabularText(U64 transaction_id, DisplayBase display_base);

protected: //functions

    double DutyCycle(Frame frame);
    double Width(Frame frame);
    void FillDelta(U64 frame_index, char *b, size_t len);

protected:  //vars
    PWMAnalyzerSettings *mSettings;
    PWMAnalyzer *mAnalyzer;
};

#endif //PWM_ANALYZER_RESULTS
