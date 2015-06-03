#include "PWMAnalyzerSettings.h"
#include <AnalyzerHelpers.h>


PWMAnalyzerSettings::PWMAnalyzerSettings()
    :   mInputChannel(UNDEFINED_CHANNEL),
        mMinChange(3)
{
    mInputChannelInterface.reset(new AnalyzerSettingInterfaceChannel());
    mInputChannelInterface->SetTitleAndTooltip("PWM", "Simple Standard PWM Analyzer");
    mInputChannelInterface->SetChannel(mInputChannel);

    mMinChangeInterface.reset(new AnalyzerSettingInterfaceInteger());
    mMinChangeInterface->SetTitleAndTooltip("Min Change(μS)",
                                           "The minimum amount of value change before recording a frame.");
    mMinChangeInterface->SetMax(10000);
    mMinChangeInterface->SetMin(0);
    mMinChangeInterface->SetInteger(mMinChange);

    AddInterface(mInputChannelInterface.get());
    AddInterface(mMinChangeInterface.get());

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
    mMinChange = mMinChangeInterface->GetInteger();

    ClearChannels();
    AddChannel(mInputChannel, "PWM Analyzer", true);

    return true;
}

void PWMAnalyzerSettings::UpdateInterfacesFromSettings()
{
    mInputChannelInterface->SetChannel(mInputChannel);
    mMinChangeInterface->SetInteger(mMinChange);
}

void PWMAnalyzerSettings::LoadSettings(const char *settings)
{
    SimpleArchive text_archive;
    text_archive.SetString(settings);

    text_archive >> mInputChannel;
    text_archive >> mMinChange;

    ClearChannels();
    AddChannel(mInputChannel, "Simple PWM Analyzer", true);

    UpdateInterfacesFromSettings();
}

const char *PWMAnalyzerSettings::SaveSettings()
{
    SimpleArchive text_archive;

    text_archive << mInputChannel;
    text_archive << mMinChange;

    return SetReturnString(text_archive.GetString());
}
