/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


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
    juce::Slider cAttackSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> caAttach;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleFmAudioProcessorEditor)
};
