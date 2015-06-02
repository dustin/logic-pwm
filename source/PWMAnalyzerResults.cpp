#include "PWMAnalyzerResults.h"
#include <AnalyzerHelpers.h>
#include "PWMAnalyzer.h"
#include "PWMAnalyzerSettings.h"
#include <iostream>
#include <fstream>

PWMAnalyzerResults::PWMAnalyzerResults(PWMAnalyzer *analyzer, PWMAnalyzerSettings *settings)
    :   AnalyzerResults(),
        mSettings(settings),
        mAnalyzer(analyzer)
{
}

PWMAnalyzerResults::~PWMAnalyzerResults()
{
}

void PWMAnalyzerResults::GenerateBubbleText(U64 frame_index, Channel &channel, DisplayBase display_base)
{
    ClearResultStrings();
    Frame frame = GetFrame(frame_index);

    char number_str[128];
    snprintf(number_str, sizeof(number_str), "%d", frame.mData1);
    AddResultString(number_str);
}

void PWMAnalyzerResults::GenerateExportFile(const char *file, DisplayBase display_base, U32 export_type_user_id)
{
    std::ofstream file_stream(file, std::ios::out);

    U64 trigger_sample = mAnalyzer->GetTriggerSample();
    U32 sample_rate = mAnalyzer->GetSampleRate();

    file_stream << "Time [s],Value" << std::endl;

    U64 num_frames = GetNumFrames();
    for (U32 i = 0; i < num_frames; i++) {
        Frame frame = GetFrame(i);

        char time_str[128];
        AnalyzerHelpers::GetTimeString(frame.mStartingSampleInclusive, trigger_sample, sample_rate, time_str, 128);

        char number_str[128];
        snprintf(number_str, sizeof(number_str), "%d", frame.mData1);

        file_stream << time_str << "," << number_str << std::endl;

        if (UpdateExportProgressAndCheckForCancel(i, num_frames) == true) {
            file_stream.close();
            return;
        }
    }

    file_stream.close();
}

void PWMAnalyzerResults::GenerateFrameTabularText(U64 frame_index, DisplayBase display_base)
{
    Frame frame = GetFrame(frame_index);
    ClearTabularText();

    char number_str[128];
    snprintf(number_str, sizeof(number_str), "%d", frame.mData1);
    AddTabularText(number_str);
}

void PWMAnalyzerResults::GeneratePacketTabularText(U64 packet_id, DisplayBase display_base)
{
    ClearResultStrings();
    AddResultString("not supported");
}

void PWMAnalyzerResults::GenerateTransactionTabularText(U64 transaction_id, DisplayBase display_base)
{
    ClearResultStrings();
    AddResultString("not supported");
}
