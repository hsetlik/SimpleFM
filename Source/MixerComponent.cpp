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
        levelKnobs[i].setRange(0.0f, 1.0f);
        levelKnobs[i].setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
        levelKnobs[i].setValue(0.6f);
        levelKnobs[i].addListener(lstnr);
        addAndMakeVisible(&levelKnobs[i]);
    }
}

void MixerComponent::resized()
{
    float n = getWidth() / 35.0f;
    for(int i = 0; i < 6; ++i)
    {
        levelKnobs[i].setBounds((1 + (i * 5)) * n, 0.75 * n, 3 * n, 3 * n);
    }
}
