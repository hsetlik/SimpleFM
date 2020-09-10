/*
  ==============================================================================

    MixerComponent.cpp
    Created: 9 Sep 2020 2:45:39pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "MixerComponent.h"

MixerComponent::MixerComponent(juce::Slider::Listener* lstnr)
{
    for(int i = 0; i < 6; ++i)
    {
        levelKnobs[i].setSliderStyle(juce::Slider::Rotary);
        knobLabels[i].setText(juce::String(i + 1), juce::dontSendNotification);
        knobLabels[i].setEditable(false);
        knobLabels[i].attachToComponent(&levelKnobs[i], true);
        levelKnobs[i].setRange(0.0f, 1.0f);
        levelKnobs[i].setTextBoxStyle(juce::Slider::NoTextBox, false, 60, 20);
        levelKnobs[i].setValue(0.6f);
        levelKnobs[i].addListener(lstnr);
        addAndMakeVisible(&knobLabels[i]);
        addAndMakeVisible(&levelKnobs[i]);
    }
    thumbColour = levelKnobs[1].findColour(juce::Slider::thumbColourId);
    textColour = juce::Colours::white;
    
}

void MixerComponent::resized()
{
    float n = getWidth() / 35.0f;
    for(int i = 0; i < 6; ++i)
    {
        levelKnobs[i].setBounds((1 + (i * 5)) * n, 0.75 * n, 3 * n, 3 * n);
    }
}

void MixerComponent::setColorsFromChannel(int channelNum, bool isActive)
{
    if(isActive && channelNum != 50)
    {
        printf("changing channel: %d\n", channelNum);
        levelKnobs[channelNum].setColour(juce::Slider::thumbColourId, juce::Colours::lightseagreen);
        knobLabels[channelNum].setColour(juce::Label::textColourId, juce::Colours::lightseagreen);
    }
    else if(channelNum != 50)
    {
        levelKnobs[channelNum].setColour(juce::Slider::thumbColourId, thumbColour);
        knobLabels[channelNum].setColour(juce::Label::textColourId, textColour);
    }
    
}
