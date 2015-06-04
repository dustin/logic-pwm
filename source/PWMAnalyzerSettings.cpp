#include <iostream>
#include "PWMAnalyzerSettings.h"
#include <AnalyzerHelpers.h>


PWMAnalyzerSettings::PWMAnalyzerSettings()
    :   mInputChannel(UNDEFINED_CHANNEL),
        mMinChange(3),
        mAnalysisType(0)
{
    mInputChannelInterface.reset(new AnalyzerSettingInterfaceChannel());
    mInputChannelInterface->SetTitleAndTooltip("PWM", "Simple Standard PWM Analyzer");
    mInputChannelInterface->SetChannel(mInputChannel);

    mAnalysisTypeInterface.reset(new AnalyzerSettingInterfaceNumberList());
    mAnalysisTypeInterface->SetTitleAndTooltip("Analysis Type",
                                          "What is important in analyzing this pwm stream?");
    mAnalysisTypeInterface->AddNumber(0, "Pulse Width", "The width of high pulses");
    mAnalysisTypeInterface->AddNumber(1, "Duty Cycle", "The duty cycle between high and low");
    mAnalysisTypeInterface->SetNumber(mAnalysisType);

    mMinChangeInterface.reset(new AnalyzerSettingInterfaceInteger());
    mMinChangeInterface->SetTitleAndTooltip("Min Change(μS or %)",
                                           "The minimum amount of value change before recording a frame.");
    mMinChangeInterface->SetMax(10000);
    mMinChangeInterface->SetMin(0);
    mMinChangeInterface->SetInteger(mMinChange);

    AddInterface(mInputChannelInterface.get());
    AddInterface(mMinChangeInterface.get());
    AddInterface(mAnalysisTypeInterface.get());

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
    mAnalysisType = mAnalysisTypeInterface->GetNumber();

    ClearChannels();
    AddChannel(mInputChannel, "PWM Analyzer", true);

    return true;
}

void PWMAnalyzerSettings::UpdateInterfacesFromSettings()
{
    mInputChannelInterface->SetChannel(mInputChannel);
    mMinChangeInterface->SetInteger(mMinChange);
    mAnalysisTypeInterface->SetNumber(mAnalysisType);
}

void PWMAnalyzerSettings::LoadSettings(const char *settings)
{
    SimpleArchive text_archive;
    text_archive.SetString(settings);

    text_archive >> mInputChannel;
    text_archive >> mMinChange;
    text_archive >> mAnalysisType;

    ClearChannels();
    AddChannel(mInputChannel, "Simple PWM Analyzer", true);

    UpdateInterfacesFromSettings();
}

const char *PWMAnalyzerSettings::SaveSettings()
{
    SimpleArchive text_archive;

    text_archive << mInputChannel;
    text_archive << mMinChange;
    text_archive << mAnalysisType;

    return SetReturnString(text_archive.GetString());
}
