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
    int seventh = getParentWidth() / 7;
    setBounds(0, 6 * seventh, 7 * seventh, seventh);
    channelKnobs.push_back(&cn0);
    channelKnobs.push_back(&cn1);
    channelKnobs.push_back(&cn2);
    channelKnobs.push_back(&cn3);
    channelKnobs.push_back(&cn4);
    channelKnobs.push_back(&cn5);
    
    for( int i = 0; i < 6; ++i)
    {
        channelKnobs[i]->setSliderStyle(juce::Slider::Rotary);
        channelKnobs[i]->setRange(0.0f, 1.0f);
        channelKnobs[i]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        channelKnobs[i]->setValue(1.0);
        channelKnobs[i]->addListener(lstnr);
        addAndMakeVisible(channelKnobs[i]);
        channelKnobs[i]->setNumDecimalPlacesToDisplay(1);
        //printf("channel knob %d initialized\n", i);
    }
    masterKnob.setSliderStyle(juce::Slider::Rotary);
    masterKnob.setRange(0.0f, 1.0f);
    masterKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    masterKnob.setValue(1.0);
    masterKnob.addListener(lstnr);
    addAndMakeVisible(&masterKnob);
    masterKnob.setNumDecimalPlacesToDisplay(1);
}
void MixerComponent::paint(juce::Graphics &g)
{
    g.setColour(juce::Colours::slategrey);
    g.fillAll();
}

void MixerComponent::resized()
{
    
    
    int n = getParentWidth() / 35;
    
    cn0.setBounds(n, 31 * n, 3 * n, 3 * n);
    masterKnob.setBounds(31.0 * n, 31.0 * n, 3.0 * n, 3.0 * n);
    printf("mixer coords after resize: %d, %d, %d, %d\n", getX(), getY(), getWidth(), getHeight());
    printf("mixer screen coords after resize: %d, %d, %d, %d\n\n", getScreenX(), getScreenY(), getWidth(), getHeight());
    toFront(false);
    
    //auto boundsInParent = getBoundsInParent();
}
