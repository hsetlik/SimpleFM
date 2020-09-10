/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "OperatorGuiComponent.h"
#include "MixerComponent.h"


//==============================================================================
/**
*/
class SimpleFmAudioProcessorEditor  :
public juce::AudioProcessorEditor,
public juce::Slider::Listener,
public juce::ComboBox::Listener,
public juce::Button::Listener
{
public:
    SimpleFmAudioProcessorEditor (SimpleFmAudioProcessor&);
    ~SimpleFmAudioProcessorEditor() override;

    //==============================================================================
    void buttonClicked(juce::Button* button) override;
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;
    void comboBoxChanged(juce::ComboBox* box) override;
    
private:
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleFmAudioProcessor& audioProcessor;
    std::vector<OperatorGuiComponent*> OpComps;
    OperatorGuiComponent op0;
    OperatorGuiComponent op1;
    OperatorGuiComponent op2;
    OperatorGuiComponent op3;
    OperatorGuiComponent op4;
    OperatorGuiComponent op5;
    MixerComponent mixComp;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleFmAudioProcessorEditor)
};
