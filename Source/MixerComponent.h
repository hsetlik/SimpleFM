/*
  ==============================================================================

    MixerComponent.h
    Created: 9 Sep 2020 2:45:39pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class MixerComponent : public juce::Component
{
public:
    MixerComponent(juce::Slider::Listener* lstnr);
    ~MixerComponent() {}
    void resized() override;
    juce::Slider levelKnobs[6];
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixKnobAttachments[6];
    juce::Label knobLabels[6];
    void setColorsFromChannel(int channelNum, bool isActive);
    juce::Colour thumbColour;
    juce::Colour textColour;
};
