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
        addAndMakeVisible(&cAttackSlider);
        cAttackSlider.setSliderStyle(juce::Slider::LinearVertical);
        cAttackSlider.setRange(0.1, 4000.0); //attack from 0.1 ms to 4 seconds
        cAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        cAttackSlider.setValue(25.0);
        
        addAndMakeVisible(cDecaySlider);
        cDecaySlider.setSliderStyle(juce::Slider::LinearVertical);
        cDecaySlider.setRange(0.1, 4000.0); //attack from 0.1 ms to 4 seconds
        cDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        cDecaySlider.setValue(25.0);
        
        addAndMakeVisible(cSustainSlider);
        cSustainSlider.setSliderStyle(juce::Slider::LinearVertical);
        cSustainSlider.setRange(0.0, 1.0);
        cSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        cSustainSlider.setValue(0.4);
        
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
    OperatorPanel(int index)
    {
        addAndMakeVisible(cEnv);
        addAndMakeVisible(mEnv);
        addAndMakeVisible(iKnob);
        addAndMakeVisible(fKnob);
        OpIndex = index;
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
        //initilize the carrier envelope
        
        cEnv.cAttackSlider.addListener(thisListener);
        juce::String caStr = "cAttack" + juce::String(OpIndex);
        cEnv.caAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, caStr, cEnv.cAttackSlider));
        
        
        cEnv.cDecaySlider.addListener(thisListener);
        cEnv.cdAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "cDecay" + juce::String(OpIndex), cEnv.cDecaySlider));
        
        
        cEnv.cSustainSlider.addListener(thisListener);
        cEnv.csAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "cSustain" + juce::String(OpIndex), cEnv.cSustainSlider));
        
        cEnv.cReleaseSlider.setSliderStyle(juce::Slider::LinearVertical);
        cEnv.cReleaseSlider.setRange(0.1, 4000.0);
        cEnv.cReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        cEnv.cReleaseSlider.setValue(0.4);
        cEnv.cReleaseSlider.addListener(thisListener);
        addAndMakeVisible(&cEnv.cReleaseSlider);
        cEnv.crAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "cRelease" + juce::String(OpIndex), cEnv.cReleaseSlider));
        //initialize the modulator envelope
        mEnv.mAttackSlider.setSliderStyle(juce::Slider::LinearVertical);
        mEnv.mAttackSlider.setRange(0.1, 4000.0); //attack from 0.1 ms to 4 seconds
        mEnv.mAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        mEnv.mAttackSlider.setValue(25.0);
        mEnv.mAttackSlider.addListener(thisListener);
        addAndMakeVisible(&mEnv.mAttackSlider);
        mEnv.maAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "mAttack"+ juce::String(OpIndex), mEnv.mAttackSlider));
        
        mEnv.mDecaySlider.setSliderStyle(juce::Slider::LinearVertical);
        mEnv.mDecaySlider.setRange(0.1, 4000.0); //attack from 0.1 ms to 4 seconds
        mEnv.mDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        mEnv.mDecaySlider.setValue(25.0);
        mEnv.mDecaySlider.addListener(thisListener);
        addAndMakeVisible(&mEnv.mDecaySlider);
        mEnv.mdAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "mDecay"+ juce::String(OpIndex), mEnv.mDecaySlider));
        
        mEnv.mSustainSlider.setSliderStyle(juce::Slider::LinearVertical);
        mEnv.mSustainSlider.setRange(0.0, 1.0);
        mEnv.mSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        mEnv.mSustainSlider.setValue(0.4);
        mEnv.mSustainSlider.addListener(thisListener);
        addAndMakeVisible(&mEnv.mSustainSlider);
        mEnv.msAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "mSustain"+ juce::String(OpIndex), mEnv.mSustainSlider));
        
        mEnv.mReleaseSlider.setSliderStyle(juce::Slider::LinearVertical);
        mEnv.mReleaseSlider.setRange(0.1, 4000.0);
        mEnv.mReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        mEnv.mReleaseSlider.setValue(0.4);
        mEnv.mReleaseSlider.addListener(thisListener);
        addAndMakeVisible(&mEnv.mReleaseSlider);
        mEnv.mrAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "mRelease"+ juce::String(OpIndex), mEnv.mReleaseSlider));
        //initialize the index knob
        iKnob.indexSlider.setSliderStyle(juce::Slider::Rotary);
        iKnob.indexSlider.setRange(1.0, 250.0);
        iKnob.indexSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        iKnob.indexSlider.setValue(100.0);
        iKnob.indexSlider.addListener(thisListener);
        addAndMakeVisible(&iKnob.indexSlider);
        iKnob.indexSlider.setNumDecimalPlacesToDisplay(1);
        iKnob.iAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "index"+ juce::String(OpIndex), iKnob.indexSlider));
        //initialize the factor knob
        fKnob.factorSlider.setSliderStyle(juce::Slider::Rotary);
        fKnob.factorSlider.setRange(-10.0, 10.0);
        fKnob.factorSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        fKnob.factorSlider.setValue(1.0);
        fKnob.factorSlider.addListener(thisListener);
        addAndMakeVisible(&fKnob.factorSlider);
        fKnob.factorSlider.setNumDecimalPlacesToDisplay(1);
        fKnob.fAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "factor"+ juce::String(OpIndex), fKnob.factorSlider));
    }
    
    void someValueChanged(juce::Slider* slider)
    { //call this for each operator in the editor's 'sliderValueChanged' method
        if(slider == &cEnv.cAttackSlider)
        {
            *pcAttackTime = cEnv.cAttackSlider.getValue();
        } else if(slider == &cEnv.cDecaySlider)
        {
            *pcDecayTime = cEnv.cDecaySlider.getValue();
        }else if(slider == &cEnv.cSustainSlider)
        {
            *pcSustainLevel = cEnv.cSustainSlider.getValue();
        }else if(slider == &cEnv.cReleaseSlider)
        {
            *pcReleaseTime = cEnv.cReleaseSlider.getValue();
        }else if(slider == &mEnv.mAttackSlider)
        {
            *pmAttackTime = mEnv.mAttackSlider.getValue();
        }else if(slider == &mEnv.mDecaySlider)
        {
            *pmDecayTime = mEnv.mDecaySlider.getValue();
        }else if(slider == &mEnv.mSustainSlider)
        {
            *pmSustainLevel = mEnv.mSustainSlider.getValue();
        }else if(slider == &mEnv.mReleaseSlider)
        {
            *pmReleaseTime = mEnv.mReleaseSlider.getValue();
        } else if(slider == &iKnob.indexSlider)
        {
            *pfIndex = iKnob.indexSlider.getValue();
        } else if(slider == &fKnob.factorSlider)
        {
            *pfFactor = fKnob.factorSlider.getValue();
        }
    }
    void addOperatorParameterLayout(int operatorIndex,
                                    juce::AudioProcessorValueTreeState::ParameterLayout* layout)
    { //creates the parameter layout to initialize the processor
        //append the operator's index to each ID string so they are distinct per operator
        juce::String opNum = juce::String(operatorIndex);
        juce::String cA = "cAttack" + opNum;
        juce::String cD = "cDecay" + opNum;
        juce::String cS = "cSustain" + opNum;
        juce::String cR = "cRelease" + opNum;
        
        juce::String mA = "mAttack" + opNum;
        juce::String mD = "mDecay" + opNum;
        juce::String mS = "mSustain" + opNum;
        juce::String mR = "mRelease" + opNum;
        
        juce::String indexID = "index" + opNum;
        juce::String factorID = "factor" + opNum;
        
        layout->add(std::make_unique<juce::AudioParameterFloat>
                   (cA, "Attack", 0.1f, 4000.0f, 1.0f));
        layout->add(std::make_unique<juce::AudioParameterFloat>
                   (cD, "Decay", 0.1f, 4000.0f, 55.0f));
        layout->add(std::make_unique<juce::AudioParameterFloat>
                   (cS, "Sustain", 0.0f, 1.0f, 0.6f));
        layout->add(std::make_unique<juce::AudioParameterFloat>
                   (cR, "Release", 0.1f, 4000.0f, 250.0f));
        
        layout->add(std::make_unique<juce::AudioParameterFloat>
                   (mA, "Attack", 0.1f, 4000.0f, 1.0f));
        layout->add(std::make_unique<juce::AudioParameterFloat>
                   (mD, "Decay", 0.1f, 4000.0f, 55.0f));
        layout->add(std::make_unique<juce::AudioParameterFloat>
                   (mS, "Sustain", 0.0f, 1.0f, 0.6f));
        layout->add(std::make_unique<juce::AudioParameterFloat>
                   (mR, "Release", 0.1f, 4000.0f, 250.0f));
        
        layout->add(std::make_unique<juce::AudioParameterFloat>
                   (indexID, "Mod Index", 0.0f, 250.0f, 100.0f));
        layout->add(std::make_unique<juce::AudioParameterFloat>
                   (factorID, "Mod Factor", -10.0f, 10.0f, 1.0f));
    }
    
    CarrierEnvelope cEnv;
    ModulatorEnvelope mEnv;
    IndexKnob iKnob;
    FactorKnob fKnob;
    int OpIndex; //assigned at initialization, keeps track of which operator this is
    
    //these point to the correct member of the value vectors in the processor
    //NOTE: these must be assigned via assignOperatorPointers in the constructor of the editor
    float* pcAttackTime;
    float* pcDecayTime;
    float* pcSustainLevel;
    float* pcReleaseTime;
    
    float* pmAttackTime;
    float* pmDecayTime;
    float* pmSustainLevel;
    float* pmReleaseTime;
    
    double* pfIndex;
    double* pfFactor;
};



