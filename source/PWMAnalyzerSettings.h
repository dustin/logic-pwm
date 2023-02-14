#ifndef PWM_ANALYZER_SETTINGS
#define PWM_ANALYZER_SETTINGS

#include <AnalyzerSettings.h>
#include <AnalyzerTypes.h>

#define ANALYSIS_WIDTH 1
#define ANALYSIS_DUTY  2

class PWMAnalyzerSettings : public AnalyzerSettings
{
public:
    PWMAnalyzerSettings();
    virtual ~PWMAnalyzerSettings();

    virtual bool SetSettingsFromInterfaces();
    void UpdateInterfacesFromSettings();
    virtual void LoadSettings(const char *settings);
    virtual const char *SaveSettings();


    Channel mInputChannel;
    int mMinChange;
    int mAnalysisType;

protected:
    std::unique_ptr< AnalyzerSettingInterfaceChannel >    mInputChannelInterface;
    std::unique_ptr< AnalyzerSettingInterfaceInteger >    mMinChangeInterface;
    std::unique_ptr< AnalyzerSettingInterfaceNumberList > mAnalysisTypeInterface;
};

#endif //PWM_ANALYZER_SETTINGS
