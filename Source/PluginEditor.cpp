/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleFmAudioProcessorEditor::SimpleFmAudioProcessorEditor (SimpleFmAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), op0(0, this), op1(1, this), op2(2, this),
                                                        op3(3, this), op4(4, this), op5(5, this)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    //each operator needs to be added to the vector like so
    
    OpComps.push_back(&op0);
    OpComps.push_back(&op1);
    OpComps.push_back(&op2);
    OpComps.push_back(&op3);
    OpComps.push_back(&op4);
    OpComps.push_back(&op5);
    
    
    addAndMakeVisible(&op0);
    addAndMakeVisible(&op1);
    addAndMakeVisible(&op2);
    addAndMakeVisible(&op3);
    addAndMakeVisible(&op4);
    addAndMakeVisible(&op5);
    
    setSize (900 * 0.85, 700 * 0.85);
    int third = getWidth() / 3;
    int half = 3 * (getHeight() / 7);
    op0.setBounds(0, 0, third, half);
    op1.setBounds(third, 0, third, half);
    op2.setBounds(2 * third, 0, third, half);
    op3.setBounds(0, half, third, half);
    op4.setBounds(third, half, third, half);
    op5.setBounds(2 * third, half, third, half);
    
    
    
    for(int i = 0; i < OpComps.size(); ++i)
    {
        juce::String iStr = juce::String(i);
        //printf("operator #%d made visible\n", i);
        printf("operator %d at X %d\n", i, OpComps[i]->getX());
        printf("operator %d at screen X %d\n", i, OpComps[i]->getScreenX());
        printf("operator %d width: %d\n", i, OpComps[i]->getWidth());
        if(OpComps[i]->isVisible())
            printf("Operator %d is visible\n", i);
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
        
        //OpComps[i]->ReinitOperator(this);
    }
}

SimpleFmAudioProcessorEditor::~SimpleFmAudioProcessorEditor()
{
}

//==============================================================================
void SimpleFmAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    
    g.setColour(juce::Colours::yellow);
    g.fillRect(OpComps[0]->getBounds());
    g.setColour(juce::Colours::lavender);
    g.fillRect(OpComps[1]->getBounds());
    g.setColour(juce::Colours::yellowgreen);
    g.fillRect(OpComps[2]->getBounds());
    g.setColour(juce::Colours::royalblue);
    g.fillRect(OpComps[3]->getBounds());
    g.setColour(juce::Colours::whitesmoke);
    g.fillRect(OpComps[4]->getBounds());
    g.setColour(juce::Colours::lightgrey);
    g.fillRect(OpComps[5]->getBounds());
    
    for(int i = 0; i < OpComps.size(); ++i)
    {
        OpComps[i]->paint(g);
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
