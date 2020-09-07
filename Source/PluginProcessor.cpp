/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

juce::AudioProcessorValueTreeState::ParameterLayout createOpParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    //this will have to be repeated for each operator
    OperatorPanel panel(1);
    panel.addOperatorParameterLayout(1, &layout);
    return layout;
}

juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add(std::make_unique<juce::AudioParameterFloat>
               ("cAttack", "Attack", 0.1f, 4000.0f, 1.0f));
            // identifier, name, minimum Value, maximumValue, default value
    //use more layout.add calls to add more parameters
    layout.add(std::make_unique<juce::AudioParameterFloat>
               ("cDecay", "Decay", 0.1f, 4000.0f, 55.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>
               ("cSustain", "Sustain", 0.0f, 1.0f, 0.6f));
    layout.add(std::make_unique<juce::AudioParameterFloat>
               ("cRelease", "Release", 0.1f, 4000.0f, 250.0f));
    //now for the modulator envelope
    layout.add(std::make_unique<juce::AudioParameterFloat>
               ("mAttack", "Attack", 0.1f, 4000.0f, 1.0f));
            // identifier, name, minimum Value, maximumValue, default value
    //use more layout.add calls to add more parameters
    layout.add(std::make_unique<juce::AudioParameterFloat>
               ("mDecay", "Decay", 0.1f, 4000.0f, 55.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>
               ("mSustain", "Sustain", 0.0f, 1.0f, 0.6f));
    layout.add(std::make_unique<juce::AudioParameterFloat>
               ("mRelease", "Release", 0.1f, 4000.0f, 250.0f));
    
    layout.add(std::make_unique<juce::AudioParameterFloat>
               ("index", "Mod Index", 0.0f, 250.0f, 100.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>
               ("factor", "Mod Factor", -10.0f, 10.0f, 1.0f));
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
        tree(*this, nullptr, "ALLPARAMETERS", createParameterLayout())
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
            //call the callbacks for all the parameters
            thisVoice->getCAttack(tree.getRawParameterValue("cAttack"));
            thisVoice->getCDecay(tree.getRawParameterValue("cDecay"));
            thisVoice->getCSustain(tree.getRawParameterValue("cSustain"));
            thisVoice->getCRelease(tree.getRawParameterValue("cRelease"));
            
            thisVoice->getMAttack(tree.getRawParameterValue("mAttack"));
            thisVoice->getMDecay(tree.getRawParameterValue("mDecay"));
            thisVoice->getMSustain(tree.getRawParameterValue("mSustain"));
            thisVoice->getMRelease(tree.getRawParameterValue("mRelease"));
            
            thisVoice->getIndexVal(tree.getRawParameterValue("index"));
            thisVoice->getFactorVal(tree.getRawParameterValue("factor"));
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
