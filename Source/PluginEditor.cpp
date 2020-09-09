/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleFmAudioProcessorEditor::SimpleFmAudioProcessorEditor (SimpleFmAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), op0(0, this)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);
    //each operator needs to be added to the vector like so
    
    OpComps.push_back(&op0);
    
    for(int i = 0; i < OpComps.size(); ++i)
    {
        juce::String iStr = juce::String(i);
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
        ("cDecayParam" + iStr),
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
    }
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
