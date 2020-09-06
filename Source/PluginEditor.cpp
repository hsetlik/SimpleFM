/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleFmAudioProcessorEditor::SimpleFmAudioProcessorEditor (SimpleFmAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);
    //set up GUI stuff below here
    cAttackSlider.setSliderStyle(juce::Slider::LinearVertical);
    cAttackSlider.setRange(0.1, 4000.0); //attack from 0.1 ms to 4 seconds
    cAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    cAttackSlider.setValue(25.0);
    cAttackSlider.addListener(this);
    addAndMakeVisible(&cAttackSlider);
    caAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "cAttack", cAttackSlider));
    
    cDecaySlider.setSliderStyle(juce::Slider::LinearVertical);
    cDecaySlider.setRange(0.1, 4000.0); 
    cDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    cDecaySlider.setValue(25.0);
    cDecaySlider.addListener(this);
    addAndMakeVisible(&cDecaySlider);
    cdAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "cDecay", cDecaySlider));
    
    cSustainSlider.setSliderStyle(juce::Slider::LinearVertical);
    cSustainSlider.setRange(0.0, 1.0);
    cSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    cSustainSlider.setValue(0.4);
    cSustainSlider.addListener(this);
    addAndMakeVisible(&cSustainSlider);
    csAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "cSustain", cSustainSlider));
    
    cReleaseSlider.setSliderStyle(juce::Slider::LinearVertical);
    cReleaseSlider.setRange(0.1, 4000.0);
    cReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    cReleaseSlider.setValue(0.4);
    cReleaseSlider.addListener(this);
    addAndMakeVisible(&cReleaseSlider);
    crAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "cRelease", cReleaseSlider));
    
}

SimpleFmAudioProcessorEditor::~SimpleFmAudioProcessorEditor()
{
}

//==============================================================================
void SimpleFmAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

  
}

void SimpleFmAudioProcessorEditor::resized()
{
    cAttackSlider.setBounds(20, 20, 40, 100);
    cDecaySlider.setBounds(70, 20, 40, 100);
    cSustainSlider.setBounds(120, 20, 40, 100);
    cReleaseSlider.setBounds(170, 20, 40, 100);
}

void SimpleFmAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    if(slider == &cAttackSlider)
    {
        audioProcessor.cAttackTime = cAttackSlider.getValue();
    } else if(slider == &cDecaySlider)
    {
        audioProcessor.cDecayTime = cDecaySlider.getValue();
    }else if(slider == &cSustainSlider)
    {
        audioProcessor.cSustainLevel = cSustainSlider.getValue();
    }else if(slider == &cReleaseSlider)
    {
        audioProcessor.cReleaseTime = cReleaseSlider.getValue();
    }
    
}
