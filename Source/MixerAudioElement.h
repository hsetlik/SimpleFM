/*
  ==============================================================================

    MixerAudioElement.h
    Created: 9 Sep 2020 2:46:08pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

//
struct MixSampleInput
{
    int channel;
    float inputValue;
    float knobValue;
};

class MixCalculator
{
public:
    MixCalculator()
    {
        numChannelsOn = 0;
    }
    ~MixCalculator() {}
    void addInput(MixSampleInput input)
    {
        sampleInputs.push_back(input);
        ++numChannelsOn;
    }
    float MixSampleOutput()
    {
        float outputSample = 0.0f;
        for(int i = 0; i < sampleInputs.size(); ++i)
            outputSample += (sampleInputs[i].inputValue * sampleInputs[i].knobValue);
        outputSample /= numChannelsOn;
        return outputSample;
    }
private:
    int numChannelsOn;
    std::vector<MixSampleInput> sampleInputs;
};
