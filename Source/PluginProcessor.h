/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "SynthVoice.h"


//==============================================================================
/**
*/
class SimpleFmAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    SimpleFmAudioProcessor();
    ~SimpleFmAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    juce::AudioProcessorValueTreeState tree;
    
    float cAttackTime = 25.0f;
    float cDecayTime = 25.0f;
    float cSustainLevel = 0.4f;
    float cReleaseTime = 25.0f;
    
    float mAttackTime = 25.0f;
    float mDecayTime = 25.0f;
    float mSustainLevel = 0.4f;
    float mReleaseTime = 25.0f;
    
    double fIndex = 80.0;
    double fFactor = 1.0;
    //vectors of the above
    std::vector<float> cAttackTimes{0, 0, 0, 0, 0, 0};
    std::vector<float> cDecayTimes{0, 0, 0, 0, 0, 0};
    std::vector<float> cSustainLevels{0, 0, 0, 0, 0, 0};
    std::vector<float> cReleaseTimes{0, 0, 0, 0, 0, 0};
    
    std::vector<float> mAttackTimes{0, 0, 0, 0, 0, 0};
    std::vector<float> mDecayTimes{0, 0, 0, 0, 0, 0};
    std::vector<float> mSustainLevels{0, 0, 0, 0, 0, 0};
    std::vector<float> mReleaseTimes{0, 0, 0, 0, 0, 0};
    
    std::vector<double> fIndeces{0, 0, 0, 0, 0, 0};
    std::vector<double> fFactors{0, 0, 0, 0, 0, 0};
    
    OperatorAudioElement oe0;
    OperatorAudioElement oe1;
private:
    juce::Synthesiser thisSynth;
    SynthVoice* thisVoice;
    double lastSampleRate;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleFmAudioProcessor)
};
