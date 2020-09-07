/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "OperatorPanelComponent.h"


//==============================================================================
/**
*/
class SimpleFmAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener
{
public:
    SimpleFmAudioProcessorEditor (SimpleFmAudioProcessor&);
    ~SimpleFmAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleFmAudioProcessor& audioProcessor;
    //every slider /other control needs to have an attachment
    //putting all the sliders for one envelope in a single parent component
    
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
    
    OperatorPanel Panel1;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleFmAudioProcessorEditor)
};
