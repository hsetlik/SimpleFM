/*
  ==============================================================================

    OperatorPanelComponent.h
    Created: 6 Sep 2020 5:47:00pm
    Author:  Hayden Setlik

  ==============================================================================
*/
#pragma once
#include <JuceHeader.h>

//some forward declarations...
std::vector<juce::Slider> cAttackSliders;
std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> caAttachments;
std::vector<juce::Slider> cDecaySliders;
std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> cdAttachments;
std::vector<juce::Slider> cSustainSliders;
std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> csAttachments;
std::vector<juce::Slider> cReleaseSliders;
std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> crAttachments;

std::vector<juce::Slider> mAttackSliders;
std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> maAttachments;
std::vector<juce::Slider> mDecaySliders;
std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> mdAttachments;
std::vector<juce::Slider> mSustainSliders;
std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> msAttachments;
std::vector<juce::Slider> mReleaseSliders;
std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> mrAttachments;

std::vector<juce::Slider> indexSliders;
std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> iAttachments;
std::vector<juce::Slider> factorSliders;
std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> fAttachments;
//end forward declarations

class ModulatorEnvelope : public juce::Component
{
public:
    ModulatorEnvelope(int index)
    {
        pmAttackSlider = &mAttackSliders[index];
        pmaAttach = &maAttachments[index];
        pmDecaySlider = &mDecaySliders[index];
        pmdAttach = &mdAttachments[index];
        pmSustainSlider = &mSustainSliders[index];
        pmsAttach = &msAttachments[index];
        pmReleaseSlider = &mReleaseSliders[index];
        pmrAttach = &mrAttachments[index];
        
        setBoundsRelative(0.5f, 0.0f, 0.5f, 0.5f);
        addAndMakeVisible(*pmAttackSlider);
        pmAttackSlider->setName("maSlider");
        pmAttackSlider->setSliderStyle(juce::Slider::LinearVertical);
        pmAttackSlider->setRange(0.1, 4000.0); //attack from 0.1 ms to 4 seconds
        pmAttackSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        pmAttackSlider->setValue(25.0);
        
        addAndMakeVisible(*pmDecaySlider);
        pmDecaySlider->setSliderStyle(juce::Slider::LinearVertical);
        pmDecaySlider->setRange(0.1, 4000.0); //attack from 0.1 ms to 4 seconds
        pmDecaySlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        pmDecaySlider->setValue(25.0);
        
        addAndMakeVisible(*pmSustainSlider);
        pmSustainSlider->setSliderStyle(juce::Slider::LinearVertical);
        pmSustainSlider->setRange(0.0, 1.0);
        pmSustainSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        pmSustainSlider->setValue(0.4);
        
        addAndMakeVisible(*pmReleaseSlider);
        pmReleaseSlider->setSliderStyle(juce::Slider::LinearVertical);
        pmReleaseSlider->setRange(0.1, 4000.0);
        pmReleaseSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        pmReleaseSlider->setValue(0.4);
    };
    ~ModulatorEnvelope(){};
    void resized() override
    {
        auto area = getLocalBounds();
        auto twentyfifth = getWidth() / 25;
        auto fifth = getWidth() / 5;
        pmAttackSlider->setBounds(area.removeFromLeft(twentyfifth + fifth));
        pmDecaySlider->setBounds(area.removeFromLeft(twentyfifth + fifth));
        pmSustainSlider->setBounds(area.removeFromLeft(twentyfifth + fifth));
        pmReleaseSlider->setBounds(area.removeFromLeft(twentyfifth + fifth));
        
    }
    //data/ object members
    juce::Slider* pmAttackSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>* pmaAttach;
    juce::Slider* pmDecaySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>* pmdAttach;
    juce::Slider* pmSustainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>* pmsAttach;
    juce::Slider* pmReleaseSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>* pmrAttach;
};

class CarrierEnvelope : public juce::Component
{
public:
    CarrierEnvelope(int index)
    {
        //link the member pointers up with the forward-declared vectors
        pcAttackSlider = &cAttackSliders[index];
        pcaAttach = &caAttachments[index];
        pcDecaySlider = &cDecaySliders[index];
        pcdAttach = &cdAttachments[index];
        pcSustainSlider = &cSustainSliders[index];
        pcsAttach = &csAttachments[index];
        
        setBoundsRelative(0.0f, 0.0f, 0.5f, 0.5f);
        addAndMakeVisible(*pcAttackSlider);
        pcAttackSlider->setName("caSlider");
        pcAttackSlider->setSliderStyle(juce::Slider::LinearVertical);
        pcAttackSlider->setRange(0.1, 4000.0); //attack from 0.1 ms to 4 seconds
        pcAttackSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        pcAttackSlider->setValue(25.0);
        
        addAndMakeVisible(*pcDecaySlider);
        pcDecaySlider->setSliderStyle(juce::Slider::LinearVertical);
        pcDecaySlider->setRange(0.1, 4000.0); //attack from 0.1 ms to 4 seconds
        pcDecaySlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        pcDecaySlider->setValue(25.0);
        
        addAndMakeVisible(*pcSustainSlider);
        pcSustainSlider->setSliderStyle(juce::Slider::LinearVertical);
        pcSustainSlider->setRange(0.0, 1.0);
        pcSustainSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        pcSustainSlider->setValue(0.4);
        
        addAndMakeVisible(*pcReleaseSlider);
        pcReleaseSlider->setSliderStyle(juce::Slider::LinearVertical);
        pcReleaseSlider->setRange(0.1, 4000.0);
        pcReleaseSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
        pcReleaseSlider->setValue(0.4);
    }
    ~CarrierEnvelope() {}
    void resized() override
    {
        auto area = getLocalBounds();
        auto twentyfifth = getWidth() / 25;
        auto fifth = getWidth() / 5;
        pcAttackSlider->setBounds(area.removeFromLeft(twentyfifth + fifth));
        pcDecaySlider->setBounds(area.removeFromLeft(twentyfifth + fifth));
        pcSustainSlider->setBounds(area.removeFromLeft(twentyfifth + fifth));
        pcReleaseSlider->setBounds(area.removeFromLeft(twentyfifth + fifth));
    }
    //data/ object members...
    juce::Slider* pcAttackSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>* pcaAttach;
    juce::Slider* pcDecaySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>* pcdAttach;
    juce::Slider* pcSustainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>* pcsAttach;
    juce::Slider* pcReleaseSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>* pcrAttach;
};
//add any other panel components before the OperatorPanel class, which must have all other components as members
class IndexKnob : public juce::Component
{
public:
    IndexKnob(int index)
    {
    indexSlider = &indexSliders[index];
    iAttach = &iAttachments[index];
    indexSlider->setSliderStyle(juce::Slider::Rotary);
    indexSlider->setRange(1.0, 250.0);
    indexSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    indexSlider->setValue(100.0);
    addAndMakeVisible(*indexSlider);
    setBoundsRelative(0.0f, 0.5f, 0.5f, 0.5f);
    }
    ~IndexKnob(){}
    void resized() override
    {
        indexSlider->setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
    }
    juce::Slider* indexSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>* iAttach;
};
class FactorKnob : public juce::Component
{
public:
    FactorKnob(int index)
    {
    factorSlider = &factorSliders[index];
    fAttach = &fAttachments[index];
    factorSlider->setSliderStyle(juce::Slider::Rotary);
    factorSlider->setRange(-10.0, 10.0);
    factorSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    factorSlider->setValue(1.0);
    addAndMakeVisible(*factorSlider);
    setBoundsRelative(0.5f, 0.5f, 0.5f, 0.5f);
    }
    ~FactorKnob(){}
    void resized() override
    {
        factorSlider->setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
    }
    juce::Slider* factorSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>* fAttach;
};

class OperatorPanel : public juce::Component
{
public:
    OperatorPanel(int index) : cEnv(index), mEnv(index), iKnob(index), fKnob(index)
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
        
        cEnv.pcAttackSlider->addListener(thisListener);
        juce::String caStr = "cAttack" + juce::String(OpIndex);
        cEnv.pcaAttach->reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, caStr, *cEnv.pcAttackSlider));
        
        cEnv.pcDecaySlider->addListener(thisListener);
        cEnv.pcdAttach->reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "cDecay" + juce::String(OpIndex), *cEnv.pcDecaySlider));
        
        cEnv.pcSustainSlider->addListener(thisListener);
        cEnv.pcsAttach->reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "cSustain" + juce::String(OpIndex), *cEnv.pcSustainSlider));
        
        cEnv.pcReleaseSlider->addListener(thisListener);
        cEnv.pcrAttach->reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "cRelease" + juce::String(OpIndex), *cEnv.pcReleaseSlider));
        //initialize the modulator envelope
        
        mEnv.pmAttackSlider->addListener(thisListener);
        mEnv.pmaAttach->reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "mAttack"+ juce::String(OpIndex), *mEnv.pmAttackSlider));
        
        mEnv.pmDecaySlider->addListener(thisListener);
        mEnv.pmdAttach->reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "mDecay"+ juce::String(OpIndex), *mEnv.pmDecaySlider));
        
        mEnv.pmSustainSlider->addListener(thisListener);
        mEnv.pmsAttach->reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "mSustain"+ juce::String(OpIndex), *mEnv.pmSustainSlider));
        
        mEnv.pmReleaseSlider->addListener(thisListener);
        mEnv.pmrAttach->reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "mRelease"+ juce::String(OpIndex), *mEnv.pmReleaseSlider));
        //initialize the index knob
        
        iKnob.indexSlider->addListener(thisListener);
        iKnob.indexSlider->setNumDecimalPlacesToDisplay(1);
        iKnob.iAttach->reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "index"+ juce::String(OpIndex), *iKnob.indexSlider));
        //initialize the factor knob
        fKnob.factorSlider->addListener(thisListener);
        fKnob.factorSlider->setNumDecimalPlacesToDisplay(1);
        fKnob.fAttach->reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "factor"+ juce::String(OpIndex), *fKnob.factorSlider));
    }
    
    void someValueChanged(juce::Slider* slider)
    //NOTE: the pointers below need to be assigned in the editor constructor
    { //call this for each operator in the editor's 'sliderValueChanged' method
        if(slider == cEnv.pcAttackSlider)
        {
            *pcAttackTime = cEnv.pcAttackSlider->getValue();
        } else if(slider == cEnv.pcDecaySlider)
        {
            *pcDecayTime = cEnv.pcDecaySlider->getValue();
        }else if(slider == cEnv.pcSustainSlider)
        {
            *pcSustainLevel = cEnv.pcSustainSlider->getValue();
        }else if(slider == cEnv.pcReleaseSlider)
        {
            *pcReleaseTime = cEnv.pcReleaseSlider->getValue();
        }else if(slider == mEnv.pmAttackSlider)
        {
            *pmAttackTime = mEnv.pmAttackSlider->getValue();
        }else if(slider == mEnv.pmDecaySlider)
        {
            *pmDecayTime = mEnv.pmDecaySlider->getValue();
        }else if(slider == mEnv.pmSustainSlider)
        {
            *pmSustainLevel = mEnv.pmSustainSlider->getValue();
        }else if(slider == mEnv.pmReleaseSlider)
        {
            *pmReleaseTime = mEnv.pmReleaseSlider->getValue();
        } else if(slider == iKnob.indexSlider)
        {
            *pfIndex = iKnob.indexSlider->getValue();
        } else if(slider == fKnob.factorSlider)
        {
            *pfFactor = fKnob.factorSlider->getValue();
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



