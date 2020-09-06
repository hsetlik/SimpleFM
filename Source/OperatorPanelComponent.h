/*
  ==============================================================================

    OperatorPanelComponent.h
    Created: 6 Sep 2020 5:47:00pm
    Author:  Hayden Setlik

  ==============================================================================
*/
#pragma once
#include <JuceHeader.h>

class ModulatorEnvelope : public juce::Component
{
public:
    ModulatorEnvelope()
    {
        //do all the addAndMakeVisible type stuff in here...
    };
    ~ModulatorEnvelope(){};
    void resized() override
    {
        
    }
    //data/ object members
    juce::Slider mAttackSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> maAttach;
    juce::Slider mDecaySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mdAttach;
    juce::Slider mSustainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> msAttach;
    juce::Slider mReleaseSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mrAttach;
};

class CarrierEnvelope : public juce::Component
{
public:
    CarrierEnvelope()
    {
        
    }
    ~CarrierEnvelope() {}
    void resized() override
    {
        
    }
    //data/ object members...
    juce::Slider cAttackSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> caAttach;
    juce::Slider cDecaySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cdAttach;
    juce::Slider cSustainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> csAttach;
    juce::Slider cReleaseSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> crAttach;
};
