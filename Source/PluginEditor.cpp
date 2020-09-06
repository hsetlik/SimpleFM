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
}

void SimpleFmAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    if(slider == &cAttackSlider)
    {
        audioProcessor.cAttackTime = cAttackSlider.getValue();
    }
    
}
