/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleFmAudioProcessorEditor::SimpleFmAudioProcessorEditor (SimpleFmAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), op0(0, this, this, this),
                                                     op1(1, this, this, this),
                                                     op2(2, this, this, this),
                                                     op3(3, this, this, this),
                                                     op4(4, this, this, this),
                                                     op5(5, this, this, this),
                                                     mixComp(this)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (900 * 0.85, 700 * 0.85);
    //each operator needs to be added to the vector like so
    
    
    addAndMakeVisible(&op0);
    addAndMakeVisible(&op1);
    addAndMakeVisible(&op2);
    addAndMakeVisible(&op3);
    addAndMakeVisible(&op4);
    addAndMakeVisible(&op5);
    addAndMakeVisible(&mixComp);
    
    OpComps.push_back(&op0);
    OpComps.push_back(&op1);
    OpComps.push_back(&op2);
    OpComps.push_back(&op3);
    OpComps.push_back(&op4);
    OpComps.push_back(&op5);
    
    
    int third = getWidth() / 3;
    int half = 3 * (getHeight() / 7);
    int seventh = getHeight() / 7;
    
    op0.setBounds(0, 0, third, half);
    op1.setBounds(third, 0, third, half);
    op2.setBounds(2 * third, 0, third, half);
    op3.setBounds(0, half, third, half);
    op4.setBounds(third, half, third, half);
    op5.setBounds(2 * third, half, third, half);
    mixComp.setBounds(0, 6 * seventh, getWidth(), seventh);
    //if(mixer.isVisible())
        //printf("mixer is visible at editor construction\n");
    //printf("mixer coords after Operator setBounds: %d, %d, %d, %d\n", mixer.getX(), mixer.getY(), mixer.getWidth(), mixer.getHeight());
    //printf("mixer screen coords after Operator setBounds: %d, %d, %d, %d\n", mixer.getScreenX(), mixer.getScreenY(), mixer.getWidth(), mixer.getHeight());
    
    
    
    for(int i = 0; i < OpComps.size(); ++i)
    {
        juce::String iStr = juce::String(i);
        
        mixComp.mixKnobAttachments[i].reset(new juce::AudioProcessorValueTreeState::SliderAttachment(
        audioProcessor.tree,
        ("mixParam" + iStr),
        mixComp.levelKnobs[i]));
            
        OpComps[i]->caAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree,
                                                                                           ("cAttackParam" + iStr),
                                                                                           OpComps[i]->cAttackSlider));
        OpComps[i]->cdAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree,
                                                                                           ("cDecayParam" + iStr),
                                                                                            OpComps[i]->cDecaySlider));
        OpComps[i]->csAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree,
        ("cSustainParam" + iStr),
         OpComps[i]->cSustainSlider));
        OpComps[i]->crAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree,
        ("cReleaseParam" + iStr),
         OpComps[i]->cReleaseSlider));
        
        OpComps[i]->maAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree,
        ("mAttackParam" + iStr),
         OpComps[i]->mAttackSlider));
        OpComps[i]->mdAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree,
        ("mDecayParam" + iStr),
         OpComps[i]->mDecaySlider));
        OpComps[i]->msAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree,
        ("mSustainParam" + iStr),
         OpComps[i]->mSustainSlider));
        OpComps[i]->mrAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree,
        ("mReleaseParam" + iStr),
         OpComps[i]->mReleaseSlider));
        
        OpComps[i]->iAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree,
        ("indexParam" + iStr),
         OpComps[i]->indexSlider));
        OpComps[i]->fAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree,
        ("factorParam" + iStr),
        OpComps[i]->factorSlider));
        
        OpComps[i]->mixButtonAttach.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(
        audioProcessor.tree,
        ("mixParam" + iStr),
        OpComps[i]->sendToMixer));
        
        //=============================
        
    }
}

SimpleFmAudioProcessorEditor::~SimpleFmAudioProcessorEditor()
{
}

//==============================================================================
void SimpleFmAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.setColour(juce::Colours::darkslategrey);
    g.fillAll();
    if(OpComps.size() != 0)
    {
        for(int i = 0; i < 6; ++i)
        {
            bool isActive = OpComps[i]->sendToMixer.getToggleState();
            mixComp.setColorsFromChannel(i, isActive);
        }
    }
}

void SimpleFmAudioProcessorEditor::resized()
{
    for(int i = 0; i < OpComps.size(); ++i)
    {
        OpComps[i]->resized();
    }
}

void SimpleFmAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    for(int i = 0; i < OpComps.size(); ++i)
    {
        
    }
}

void SimpleFmAudioProcessorEditor::comboBoxChanged(juce::ComboBox *box)
{
    printf("combo box changed\n");
}

void SimpleFmAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    std::string str = button->getName().toStdString();
    const char* buttonName = str.c_str();
    printf("Button name: %s\n", buttonName);
    int bIndex = 50;
    bool active = button->getToggleState();
    //cout >> str >> endl;
    for(int i = 0; i < 6; ++i)
    {
        if(button == &OpComps[i]->sendToMixer)
        {
            if(active)
                printf("button # %d is active\n", i);
            else
                printf("button # %d is inactive\n", i);
            mixComp.setColorsFromChannel(bIndex, active);
            audioProcessor.thisVoice->mixerOnSet(i, button->getToggleState());
        }
    }
    audioProcessor.thisVoice->buttonAssignmentFinished = true;
}
