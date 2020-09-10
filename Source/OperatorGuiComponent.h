/*
  ==============================================================================

    OperatorGuiComponent.h
    Created: 8 Sep 2020 8:42:54am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>



class OperatorGuiComponent : public juce::Component
{
public:
    OperatorGuiComponent(int index, juce::Slider::Listener* thisListener, juce::ComboBox::Listener* boxListener);
    ~OperatorGuiComponent() {}
    void resized() override;
    int ComponentIndex;
    juce::Slider cAttackSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> caAttach;
    juce::Slider cDecaySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cdAttach;
    juce::Slider cSustainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> csAttach;
    juce::Slider cReleaseSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> crAttach;
    
    juce::Slider mAttackSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> maAttach;
    juce::Slider mDecaySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mdAttach;
    juce::Slider mSustainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> msAttach;
    juce::Slider mReleaseSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mrAttach;
    
    juce::Slider indexSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> iAttach;
    juce::Slider factorSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fAttach;
    
    juce::ComboBox modSelector;
    void modSelectorChanged();
    
    juce::TextButton sendToMixer;
};

