/*
  ==============================================================================

    Operator.cpp
    Created: 5 Sep 2020 9:55:33pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "Operator.h"

OperatorPanel::OperatorPanel()
{
    addAndMakeVisible(aSlider);
    aSlider.setSliderStyle(juce::Slider::Rotary);
    aSlider.setRange(0.0, 4000.0);
    aSlider.setValue(25.0);
    envelope->setAttack(25.0);
    
    addAndMakeVisible(dSlider);
    dSlider.setSliderStyle(juce::Slider::Rotary);
    dSlider.setRange(0.0, 4000.0);
    dSlider.setValue(75.0);
    envelope->setDecay(75.0);
    
    addAndMakeVisible(sSlider);
    sSlider.setSliderStyle(juce::Slider::Rotary);
    sSlider.setRange(0.0, 1.0);
    sSlider.setValue(0.45);
    envelope->setSustain(0.45);
    
    addAndMakeVisible(rSlider);
    rSlider.setSliderStyle(juce::Slider::Rotary);
    rSlider.setRange(0.0, 4000.0);
    rSlider.setValue(25.0);
    envelope->setRelease(25.0);
    
    setBounds(0, 0, 600, 200);
}

void OperatorPanel::resized()
{
    int quarterWidth = getWidth() / 4;
    int sixthWidth = getWidth() / 6;
    aSlider.setBounds(15, 25, sixthWidth, sixthWidth);
    dSlider.setBounds(15 + quarterWidth, 25, sixthWidth, sixthWidth);
    sSlider.setBounds(15 + (2 * quarterWidth), 25, sixthWidth, sixthWidth);
    rSlider.setBounds(15 + (3 * quarterWidth), 25, sixthWidth, sixthWidth);
}

void OperatorPanel::sliderValueChanged(juce::Slider *slider)
{
    if(slider == &aSlider)
        envelope->setAttack(aSlider.getValue());
    else if(slider == & dSlider)
        envelope->setDecay(dSlider.getValue());
    else if(slider == &sSlider)
        envelope->setSustain(sSlider.getValue());
    else
        envelope->setRelease(rSlider.getValue());
}
//==================================================
