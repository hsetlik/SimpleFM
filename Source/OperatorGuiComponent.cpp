/*
  ==============================================================================

    OperatorGuiComponent.cpp
    Created: 8 Sep 2020 9:25:58am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "OperatorGuiComponent.h"

OperatorGuiComponent::OperatorGuiComponent(int index, juce::Slider::Listener* thisListener, juce::ComboBox::Listener* boxListener)
{
    ComponentIndex = index;
    cAttackSlider.setSliderStyle(juce::Slider::LinearVertical);
    cAttackSlider.setRange(0.1, 4000.0); //attack from 0.1 ms to 4 seconds
    cAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    cAttackSlider.setValue(25.0);
    cAttackSlider.addListener(thisListener);
    addAndMakeVisible(&cAttackSlider);
    
    cDecaySlider.setSliderStyle(juce::Slider::LinearVertical);
    cDecaySlider.setRange(0.1, 4000.0);
    cDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    cDecaySlider.setValue(25.0);
    cDecaySlider.addListener(thisListener);
    addAndMakeVisible(&cDecaySlider);
    
    cSustainSlider.setSliderStyle(juce::Slider::LinearVertical);
    cSustainSlider.setRange(0.0, 1.0);
    cSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    cSustainSlider.setValue(0.4);
    cSustainSlider.addListener(thisListener);
    addAndMakeVisible(&cSustainSlider);
    
    cReleaseSlider.setSliderStyle(juce::Slider::LinearVertical);
    cReleaseSlider.setRange(0.1, 4000.0);
    cReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    cReleaseSlider.setValue(0.4);
    cReleaseSlider.addListener(thisListener);
    addAndMakeVisible(&cReleaseSlider);
    
    mAttackSlider.setSliderStyle(juce::Slider::LinearVertical);
    mAttackSlider.setRange(0.1, 4000.0);
    mAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    mAttackSlider.setNumDecimalPlacesToDisplay(1);
    mAttackSlider.setValue(0.4);
    mAttackSlider.addListener(thisListener);
    addAndMakeVisible(&mAttackSlider);
    
    mDecaySlider.setSliderStyle(juce::Slider::LinearVertical);
    mDecaySlider.setRange(0.1, 4000.0);
    mDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    mDecaySlider.setValue(0.4);
    mDecaySlider.addListener(thisListener);
    addAndMakeVisible(&mDecaySlider);
    mDecaySlider.setNumDecimalPlacesToDisplay(1);
   
    mSustainSlider.setSliderStyle(juce::Slider::LinearVertical);
    mSustainSlider.setRange(0.1, 4000.0);
    mSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    mSustainSlider.setValue(0.4);
    mSustainSlider.addListener(thisListener);
    mSustainSlider.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(&mSustainSlider);
    
    mReleaseSlider.setSliderStyle(juce::Slider::LinearVertical);
    mReleaseSlider.setRange(0.0, 0.1);
    mReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    mReleaseSlider.setValue(0.4);
    mReleaseSlider.addListener(thisListener);
    addAndMakeVisible(&mReleaseSlider);
    mReleaseSlider.setNumDecimalPlacesToDisplay(1);
    
    indexSlider.setSliderStyle(juce::Slider::Rotary);
    indexSlider.setRange(1.0, 250.0);
    indexSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    indexSlider.setValue(100.0);
    indexSlider.addListener(thisListener);
    addAndMakeVisible(&indexSlider);
    indexSlider.setNumDecimalPlacesToDisplay(1);

    factorSlider.setSliderStyle(juce::Slider::Rotary);
    factorSlider.setRange(-10.0, 10.0);
    factorSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    factorSlider.setValue(1.0);
    factorSlider.addListener(thisListener);
    addAndMakeVisible(&factorSlider);
    factorSlider.setNumDecimalPlacesToDisplay(1);
    
    addAndMakeVisible(&modSelector);
    for(int i = 1; i < 7; ++i)
    {
        juce::String idStr = juce::String(i);
        if(i != (ComponentIndex + 1))
            modSelector.addItem(idStr, i);
    }
    modSelector.addItem("-", 7);
}

void OperatorGuiComponent::resized()
{
    float n = getWidth() / 15.0f;
    cAttackSlider.setBounds(1.5 * n, 2 * n, 2 * n, 4 * n);
    cDecaySlider.setBounds(4.5 * n, 2 * n, 2 * n, 4 * n);
    cSustainSlider.setBounds(7.5 * n, 2 * n, 2 * n, 4 * n);
    cReleaseSlider.setBounds(10.5 * n, 2 * n, 2 * n, 4 * n);
    
    modSelector.setBounds(1.5 * n, 0.5 * n, 3 * n, 20);
    
    mAttackSlider.setBounds(1.5 * n, 6 * n, 2 * n, 4 * n);
    mDecaySlider.setBounds(4.5 * n, 6 * n, 2 * n, 4 * n);
    mSustainSlider.setBounds(7.5 * n, 6 * n, 2 * n, 4 * n);
    mReleaseSlider.setBounds(10.5 * n, 6 * n, 2 * n, 4 * n);
    
    factorSlider.setBounds(3 * n, 11 * n, 4 * n, 4 * n);
    indexSlider.setBounds(8 * n, 11 * n, 4 * n, 4 * n);
}
