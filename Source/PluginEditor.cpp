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
    setSize (600, 400);
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
    
    mAttackSlider.setSliderStyle(juce::Slider::LinearVertical);
    mAttackSlider.setRange(0.1, 4000.0);
    mAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    mAttackSlider.setValue(0.4);
    mAttackSlider.addListener(this);
    addAndMakeVisible(&mAttackSlider);
    maAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "mAttack", mAttackSlider));
    
    mDecaySlider.setSliderStyle(juce::Slider::LinearVertical);
    mDecaySlider.setRange(0.1, 4000.0);
    mDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    mDecaySlider.setValue(0.4);
    mDecaySlider.addListener(this);
    addAndMakeVisible(&mDecaySlider);
    mdAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "mDecay", mDecaySlider));
    
    mSustainSlider.setSliderStyle(juce::Slider::LinearVertical);
    mSustainSlider.setRange(0.1, 4000.0);
    mSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    mSustainSlider.setValue(0.4);
    mSustainSlider.addListener(this);
    addAndMakeVisible(&mSustainSlider);
    msAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "mSustain", mSustainSlider));
    
    mReleaseSlider.setSliderStyle(juce::Slider::LinearVertical);
    mReleaseSlider.setRange(0.0, 0.1);
    mReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    mReleaseSlider.setValue(0.4);
    mReleaseSlider.addListener(this);
    addAndMakeVisible(&mReleaseSlider);
    mrAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "mRelease", mReleaseSlider));
    
    indexSlider.setSliderStyle(juce::Slider::Rotary);
    indexSlider.setRange(1.0, 250.0);
    indexSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    indexSlider.setValue(100.0);
    indexSlider.addListener(this);
    addAndMakeVisible(&indexSlider);
    iAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "index", indexSlider));
    
    factorSlider.setSliderStyle(juce::Slider::Rotary);
    factorSlider.setRange(-10.0, 10.0);
    factorSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    factorSlider.setValue(1.0);
    factorSlider.addListener(this);
    addAndMakeVisible(&factorSlider);
    fAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "factor", factorSlider));
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
    
    mAttackSlider.setBounds(220, 20, 40, 100);
    mDecaySlider.setBounds(270, 20, 40, 100);
    mSustainSlider.setBounds(320, 20, 40, 100);
    mReleaseSlider.setBounds(370, 20, 40, 100);
    
    indexSlider.setBounds(100, 150, 40, 60);
    factorSlider.setBounds(200, 150, 40, 60);
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
    }else if(slider == &mAttackSlider)
    {
        audioProcessor.mAttackTime = mAttackSlider.getValue();
    }else if(slider == &mDecaySlider)
    {
        audioProcessor.mDecayTime = mDecaySlider.getValue();
    }else if(slider == &mSustainSlider)
    {
        audioProcessor.mSustainLevel = mSustainSlider.getValue();
    }else if(slider == &mReleaseSlider)
    {
        audioProcessor.mReleaseTime = mReleaseSlider.getValue();
    } else if(slider == &indexSlider)
    {
        audioProcessor.fIndex = indexSlider.getValue();
    } else if(slider == &factorSlider)
    {
        audioProcessor.fFactor = factorSlider.getValue();
    }
    
}
