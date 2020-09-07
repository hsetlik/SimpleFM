/*
  ==============================================================================

    OperatorPanelComponent.h
    Created: 6 Sep 2020 5:47:00pm
    Author:  Hayden Setlik

  ==============================================================================
*/
#pragma once
#include <JuceHeader.h>

class ModulatorEnvelope : public juce::Component
{
public:
    ModulatorEnvelope()
    {
        setBoundsRelative(0.5f, 0.0f, 0.5f, 0.5f);
        addAndMakeVisible(mAttackSlider);
        addAndMakeVisible(mDecaySlider);
        addAndMakeVisible(mSustainSlider);
        addAndMakeVisible(mReleaseSlider);
    };
    ~ModulatorEnvelope(){};
    void resized() override
    {
        auto area = getLocalBounds();
        auto twentyfifth = getWidth() / 25;
        auto fifth = getWidth() / 5;
        mAttackSlider.setBounds(area.removeFromLeft(twentyfifth + fifth));
        mDecaySlider.setBounds(area.removeFromLeft(twentyfifth + fifth));
        mSustainSlider.setBounds(area.removeFromLeft(twentyfifth + fifth));
        mReleaseSlider.setBounds(area.removeFromLeft(twentyfifth + fifth));
        
    }
    //data/ object members
    juce::Slider mAttackSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> maAttach;
    juce::Slider mDecaySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mdAttach;
    juce::Slider mSustainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> msAttach;
    juce::Slider mReleaseSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mrAttach;
};

class CarrierEnvelope : public juce::Component
{
public:
    CarrierEnvelope()
    {
        setBoundsRelative(0.0f, 0.0f, 0.5f, 0.5f);
        addAndMakeVisible(cAttackSlider);
        addAndMakeVisible(cDecaySlider);
        addAndMakeVisible(cSustainSlider);
        addAndMakeVisible(cReleaseSlider);
    }
    ~CarrierEnvelope() {}
    void resized() override
    {
        auto area = getLocalBounds();
        auto twentyfifth = getWidth() / 25;
        auto fifth = getWidth() / 5;
        cAttackSlider.setBounds(area.removeFromLeft(twentyfifth + fifth));
        cDecaySlider.setBounds(area.removeFromLeft(twentyfifth + fifth));
        cSustainSlider.setBounds(area.removeFromLeft(twentyfifth + fifth));
        cReleaseSlider.setBounds(area.removeFromLeft(twentyfifth + fifth));
    }
    //data/ object members...
    juce::Slider cAttackSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> caAttach;
    juce::Slider cDecaySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cdAttach;
    juce::Slider cSustainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> csAttach;
    juce::Slider cReleaseSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> crAttach;
};
//add any other panel components before the OperatorPanel class, which must have all other components as members
class IndexKnob : public juce::Component
{
public:
    IndexKnob()
    {
    indexSlider.setSliderStyle(juce::Slider::Rotary);
    indexSlider.setRange(1.0, 250.0);
    indexSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    indexSlider.setValue(100.0);
    addAndMakeVisible(indexSlider);
    setBoundsRelative(0.0f, 0.5f, 0.5f, 0.5f);
    }
    ~IndexKnob(){}
    void resized() override
    {
        indexSlider.setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
    }
    juce::Slider indexSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> iAttach;
};
class FactorKnob : public juce::Component
{
public:
    FactorKnob()
    {
    factorSlider.setSliderStyle(juce::Slider::Rotary);
    factorSlider.setRange(-10.0, 10.0);
    factorSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    factorSlider.setValue(1.0);
    addAndMakeVisible(factorSlider);
    setBoundsRelative(0.5f, 0.5f, 0.5f, 0.5f);
    }
    ~FactorKnob(){}
    void resized() override
    {
        factorSlider.setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
    }
    juce::Slider factorSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fAttach;
};

class OperatorPanel : public juce::Component
{
public:
    OperatorPanel()
    {
        addAndMakeVisible(cEnv);
        addAndMakeVisible(mEnv);
        addAndMakeVisible(iKnob);
        addAndMakeVisible(fKnob);
    }
    ~OperatorPanel() {}
    void resized() override
    {
        auto area = getLocalBounds();
        auto quarter = getWidth() / 4;
        auto hQuarter = getHeight() / 4;
        auto bottomQuarter = area.removeFromBottom(hQuarter);
        iKnob.setBounds(bottomQuarter.removeFromLeft(quarter));
        fKnob.setBounds(bottomQuarter.removeFromLeft(quarter));
        mEnv.setBounds(area.removeFromLeft(2 * quarter));
        cEnv.setBounds(area.removeFromLeft(2 * quarter));
    }
    void initializeAll(juce::AudioProcessorValueTreeState* pTree, juce::Slider::Listener* thisListener)
    {
        cEnv.cAttackSlider.setSliderStyle(juce::Slider::LinearVertical);
        cEnv.cAttackSlider.setRange(0.1, 4000.0); //attack from 0.1 ms to 4 seconds
        cEnv.cAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        cEnv.cAttackSlider.setValue(25.0);
        cEnv.cAttackSlider.addListener(thisListener);
        addAndMakeVisible(&cEnv.cAttackSlider);
        cEnv.caAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "cAttack", cEnv.cAttackSlider));
        
        cEnv.cDecaySlider.setSliderStyle(juce::Slider::LinearVertical);
        cEnv.cDecaySlider.setRange(0.1, 4000.0); //attack from 0.1 ms to 4 seconds
        cEnv.cDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        cEnv.cDecaySlider.setValue(25.0);
        cEnv.cDecaySlider.addListener(thisListener);
        addAndMakeVisible(&cEnv.cDecaySlider);
        cEnv.cdAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "cDecay", cEnv.cDecaySlider));
        
        cEnv.cSustainSlider.setSliderStyle(juce::Slider::LinearVertical);
        cEnv.cSustainSlider.setRange(0.0, 1.0);
        cEnv.cSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        cEnv.cSustainSlider.setValue(0.4);
        cEnv.cSustainSlider.addListener(thisListener);
        addAndMakeVisible(&cEnv.cSustainSlider);
        cEnv.csAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "cSustain", cEnv.cSustainSlider));
        
        cEnv.cReleaseSlider.setSliderStyle(juce::Slider::LinearVertical);
        cEnv.cReleaseSlider.setRange(0.1, 4000.0);
        cEnv.cReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        cEnv.cReleaseSlider.setValue(0.4);
        cEnv.cReleaseSlider.addListener(thisListener);
        addAndMakeVisible(&cEnv.cReleaseSlider);
        cEnv.crAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "cRelease", cEnv.cReleaseSlider));
        
        mEnv.mAttackSlider.setSliderStyle(juce::Slider::LinearVertical);
        mEnv.mAttackSlider.setRange(0.1, 4000.0); //attack from 0.1 ms to 4 seconds
        mEnv.mAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        mEnv.mAttackSlider.setValue(25.0);
        mEnv.mAttackSlider.addListener(thisListener);
        addAndMakeVisible(&mEnv.mAttackSlider);
        mEnv.maAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "mAttack", mEnv.mAttackSlider));
        
        mEnv.mDecaySlider.setSliderStyle(juce::Slider::LinearVertical);
        mEnv.mDecaySlider.setRange(0.1, 4000.0); //attack from 0.1 ms to 4 seconds
        mEnv.mDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        mEnv.mDecaySlider.setValue(25.0);
        mEnv.mDecaySlider.addListener(thisListener);
        addAndMakeVisible(&mEnv.mDecaySlider);
        mEnv.mdAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "mDecay", mEnv.mDecaySlider));
        
        mEnv.mSustainSlider.setSliderStyle(juce::Slider::LinearVertical);
        mEnv.mSustainSlider.setRange(0.0, 1.0);
        mEnv.mSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        mEnv.mSustainSlider.setValue(0.4);
        mEnv.mSustainSlider.addListener(thisListener);
        addAndMakeVisible(&mEnv.mSustainSlider);
        mEnv.msAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "mSustain", mEnv.mSustainSlider));
        
        mEnv.mReleaseSlider.setSliderStyle(juce::Slider::LinearVertical);
        mEnv.mReleaseSlider.setRange(0.1, 4000.0);
        mEnv.mReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        mEnv.mReleaseSlider.setValue(0.4);
        mEnv.mReleaseSlider.addListener(thisListener);
        addAndMakeVisible(&mEnv.mReleaseSlider);
        mEnv.mrAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "mRelease", mEnv.mReleaseSlider));
        
    }
    CarrierEnvelope cEnv;
    ModulatorEnvelope mEnv;
    IndexKnob iKnob;
    FactorKnob fKnob;
};
