#include "PWMAnalyzerSettings.h"
#include <AnalyzerHelpers.h>


PWMAnalyzerSettings::PWMAnalyzerSettings()
    :   mInputChannel(UNDEFINED_CHANNEL)
{
    mInputChannelInterface.reset(new AnalyzerSettingInterfaceChannel());
    mInputChannelInterface->SetTitleAndTooltip("PWM", "Simple Standard PWM Analyzer");
    mInputChannelInterface->SetChannel(mInputChannel);

    AddInterface(mInputChannelInterface.get());

    AddExportOption(0, "Export as text/csv file");
    AddExportExtension(0, "text", "txt");
    AddExportExtension(0, "csv", "csv");

    ClearChannels();
    AddChannel(mInputChannel, "PWM", false);
}

PWMAnalyzerSettings::~PWMAnalyzerSettings()
{
}

bool PWMAnalyzerSettings::SetSettingsFromInterfaces()
{
    mInputChannel = mInputChannelInterface->GetChannel();

    ClearChannels();
    AddChannel(mInputChannel, "PWM Analyzer", true);

    return true;
}

void PWMAnalyzerSettings::UpdateInterfacesFromSettings()
{
    mInputChannelInterface->SetChannel(mInputChannel);
}

void PWMAnalyzerSettings::LoadSettings(const char *settings)
{
    SimpleArchive text_archive;
    text_archive.SetString(settings);

    text_archive >> mInputChannel;

    ClearChannels();
    AddChannel(mInputChannel, "Simple PWM Analyzer", true);

    UpdateInterfacesFromSettings();
}

const char *PWMAnalyzerSettings::SaveSettings()
{
    SimpleArchive text_archive;

    text_archive << mInputChannel;

    return SetReturnString(text_archive.GetString());
}
