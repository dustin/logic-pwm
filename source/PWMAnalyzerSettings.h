#ifndef PWM_ANALYZER_SETTINGS
#define PWM_ANALYZER_SETTINGS

#include <AnalyzerSettings.h>
#include <AnalyzerTypes.h>

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

protected:
    std::auto_ptr< AnalyzerSettingInterfaceChannel >    mInputChannelInterface;
};

#endif //PWM_ANALYZER_SETTINGS
