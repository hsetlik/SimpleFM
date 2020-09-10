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
    MixerComponent(juce::Slider::Listener* listr);
    ~MixerComponent() {}
    void resized() override;
    void paint(juce::Graphics& g) override;
    juce::Slider cn0;
    juce::Slider cn1;
    juce::Slider cn2;
    juce::Slider cn3;
    juce::Slider cn4;
    juce::Slider cn5;
    
    std::vector<juce::Slider*> channelKnobs;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> channelAttachments[6];
    juce::Slider masterKnob;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> masterAttachment;
};
