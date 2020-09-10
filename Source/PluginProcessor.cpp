/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

juce::AudioProcessorValueTreeState::ParameterLayout createLayout(int numOperators)
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    for( int i = 0; i < numOperators; ++i)
    {
        juce::String iStr = juce::String(i);
        //setting up the distinct name/ID strings for each operator
        //for the carrier envelope
        juce::String cAttackID = "cAttackParam" + iStr;
        juce::String cAttackName = "Carrier " + iStr + " Attack";
        juce::String cDecayID = "cDecayParam" + iStr;
        juce::String cDecayName = "Carrier " + iStr + " Decay";
        juce::String cSustainID = "cSustainParam" + iStr;
        juce::String cSustainName = "Carrier " + iStr + " Sustain";
        juce::String cReleaseID = "cReleaseParam" + iStr;
        juce::String cReleaseName = "Carrier " + iStr + " Release";
        //for the modualtor envelope
        juce::String mAttackID = "mAttackParam" + iStr;
        juce::String mAttackName = "Modulator " + iStr + " Attack";
        juce::String mDecayID = "mDecayParam" + iStr;
        juce::String mDecayName = "Modulator " + iStr + " Decay";
        juce::String mSustainID = "mSustainParam" + iStr;
        juce::String mSustainName = "Modulator " + iStr + " Sustain";
        juce::String mReleaseID = "mReleaseParam" + iStr;
        juce::String mReleaseName = "Modulator " + iStr + " Release";
        //for the knobs
        juce::String iKnobID = "indexParam" + iStr;
        juce::String iKnobName = "Operator " + iStr + " Index";
        juce::String fKnobID = "factorParam" + iStr;
        juce::String fKnobName = "Operator " + iStr + " Factor";
        //for the mixer
        juce::String cKnobID = "mixParam" + iStr;
        juce::String cKnobName = "Operator " + iStr + " level";
        //creating the parameters...
        layout.add(std::make_unique<juce::AudioParameterFloat>
           (cAttackID, cAttackName, 0.1f, 4000.0f, 8.0f));
        // identifier, name, minimum Value, maximumValue, default value
        layout.add(std::make_unique<juce::AudioParameterFloat>
                   (cDecayID, cDecayName, 0.1f, 4000.0f, 55.0f));
        layout.add(std::make_unique<juce::AudioParameterFloat>
                   (cSustainID, cSustainName, 0.0f, 1.0f, 0.6f));
        layout.add(std::make_unique<juce::AudioParameterFloat>
                   (cReleaseID, cReleaseName, 0.1f, 4000.0f, 250.0f));
        layout.add(std::make_unique<juce::AudioParameterFloat>
                   (mAttackID, mAttackName, 0.1f, 4000.0f, 8.0f));
        layout.add(std::make_unique<juce::AudioParameterFloat>
                   (mDecayID, mDecayName, 0.1f, 4000.0f, 55.0f));
        layout.add(std::make_unique<juce::AudioParameterFloat>
                   (mSustainID, mSustainName, 0.0f, 1.0f, 0.6f));
        layout.add(std::make_unique<juce::AudioParameterFloat>
                   (mReleaseID, mReleaseName, 0.1f, 4000.0f, 250.0f));
        
        layout.add(std::make_unique<juce::AudioParameterFloat>
                   (iKnobID, iKnobName, 0.0f, 250.0f, 100.0f));
        layout.add(std::make_unique<juce::AudioParameterFloat>
                   (fKnobID, fKnobName, -10.0f, 10.0f, 1.0f));
        layout.add(std::make_unique<juce::AudioParameterFloat>
                   (cKnobID, cKnobName, 0.0f, 1.0f, 0.6f));
    }
    return layout;
}

//==============================================================================
SimpleFmAudioProcessor::SimpleFmAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
        //Putting stuff into the valueTree
        tree(*this, nullptr, "ALLPARAMETERS", createLayout(6))
#endif
{
    for(int i = 0; i < 6; ++i)
    {
        thisSynth.addVoice(new SynthVoice());
    }
    thisSynth.clearSounds();
    thisSynth.addSound(new SynthSound());
    
    
}

SimpleFmAudioProcessor::~SimpleFmAudioProcessor()
{
}

//==============================================================================
const juce::String SimpleFmAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimpleFmAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimpleFmAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SimpleFmAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SimpleFmAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleFmAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SimpleFmAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleFmAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SimpleFmAudioProcessor::getProgramName (int index)
{
    return {};
}

void SimpleFmAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SimpleFmAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    thisSynth.setCurrentPlaybackSampleRate(lastSampleRate);
}

void SimpleFmAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleFmAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SimpleFmAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    for(int i = 0; i < thisSynth.getNumVoices(); ++i)
    {
        //yes that is supposed to be a single '='
        if((thisVoice =  dynamic_cast<SynthVoice*>(thisSynth.getVoice(i))))
        {
            for(int n = 0; n < numOperators; ++n)
            {
                juce::String iStr = juce::String(n);
                thisVoice->caVoiceSet(n, tree.getRawParameterValue("cAttackParam" + iStr));
                thisVoice->cdVoiceSet(n, tree.getRawParameterValue("cDecayParam" + iStr));
                thisVoice->csVoiceSet(n, tree.getRawParameterValue("cSustainParam" + iStr));
                thisVoice->crVoiceSet(n, tree.getRawParameterValue("cReleaseParam" + iStr));
                
                thisVoice->maVoiceSet(n, tree.getRawParameterValue("mAttackParam" + iStr));
                thisVoice->mdVoiceSet(n, tree.getRawParameterValue("mDecayParam" + iStr));
                thisVoice->msVoiceSet(n, tree.getRawParameterValue("mSustainParam" + iStr));
                thisVoice->mrVoiceSet(n, tree.getRawParameterValue("mReleaseParam" + iStr));
                
                thisVoice->iVoiceSet(n, tree.getRawParameterValue("indexParam" + iStr));
                thisVoice->fVoiceSet(n, tree.getRawParameterValue("factorParam" + iStr));
            }
            
        }
    }
    buffer.clear();
    thisSynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool SimpleFmAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SimpleFmAudioProcessor::createEditor()
{
    return new SimpleFmAudioProcessorEditor (*this);
}

//==============================================================================
void SimpleFmAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SimpleFmAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleFmAudioProcessor();
}
