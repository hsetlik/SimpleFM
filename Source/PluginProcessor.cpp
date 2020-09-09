/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

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

juce::AudioProcessorValueTreeState::ParameterLayout createLayout(int numOperators)
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    for( int i = 0; i < numOperators; ++i)
    {
        juce::String iStr = juce::String(i);
        //setting up the distinct name/ID strings for each operator
        //for the carrier envelope
        juce::String cAttackID = "cAttack" + iStr;
        juce::String cAttackName = "Carrier " + iStr + " Attack";
        juce::String cDecayID = "cDecay" + iStr;
        juce::String cDecayName = "Carrier " + iStr + " Decay";
        juce::String cSustainID = "cSustain" + iStr;
        juce::String cSustainName = "Carrier " + iStr + " Sustain";
        juce::String cReleaseID = "cRelease" + iStr;
        juce::String cReleaseName = "Carrier " + iStr + " Release";
        //for the modualtor envelope
        juce::String mAttackID = "mAttack" + iStr;
        juce::String mAttackName = "Modulator " + iStr + " Attack";
        juce::String mDecayID = "mDecay" + iStr;
        juce::String mDecayName = "Modulator " + iStr + " Decay";
        juce::String mSustainID = "mSustain" + iStr;
        juce::String mSustainName = "Modulator " + iStr + " Sustain";
        juce::String mReleaseID = "mRelease" + iStr;
        juce::String mReleaseName = "Modulator " + iStr + " Release";
        //for the knobs
        juce::String iKnobID = "index" + iStr;
        juce::String iKnobName = "Operator " + iStr + " Index";
        juce::String fKnobID = "factor" + iStr;
        juce::String fKnobName = "Operator " + iStr + " Factor";
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
        tree(*this, nullptr, "ALLPARAMETERS", createLayout(2))
#endif
{
    for(int i = 0; i < 6; ++i)
    {
        thisSynth.addVoice(new SynthVoice());
    }
    thisSynth.clearSounds();
    thisSynth.addSound(new SynthSound());
    
    //value sets need to be added like so
    
    ParameterValSet set0;
    ParameterValSet set1;
    ParameterValSet set2;
    ParameterValSet set3;
    ParameterValSet set4;
    ParameterValSet set5;
    ValueSets.push_back(set1);
    ValueSets.push_back(set2);
    ValueSets.push_back(set3);
    ValueSets.push_back(set4);
    ValueSets.push_back(set0);
    ValueSets.push_back(set5);
    
    for(int i = 0; i < 6; ++i) //directly accessing data members with = works
    {
        
        ValueSets[i].cAttackTime = 0;
        ValueSets[i].cDecayTime = 0;
        ValueSets[i].cReleaseTime = 0;
        ValueSets[i].cSustainLevel = 0;
        
        ValueSets[i].cAttackTime = 0;
        ValueSets[i].cDecayTime = 0;
        ValueSets[i].cReleaseTime = 0;
        ValueSets[i].cSustainLevel = 0;
        
        ValueSets[i].mAttackTime = 0;
        ValueSets[i].mDecayTime = 0;
        ValueSets[i].mReleaseTime = 0;
        ValueSets[i].mSustainLevel = 0;
        
        ValueSets[i].fFactor = 0.0;
        ValueSets[i].fIndex = 0.0;
    }
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
            for(int n = 0; n < ValueSets.size(); ++n) //getting the parameters per voice
            {
                juce::String iStr = juce::String(n);
                juce::String caStr = "cAttack" + iStr;
                thisVoice->voiceValueSet[i].cAttackTime = *(tree.getRawParameterValue(caStr));
                thisVoice->voiceValueSet[i].cDecayTime = *(tree.getRawParameterValue("cDecay" + iStr));
                thisVoice->voiceValueSet[i].setCSustain(tree.getRawParameterValue("cSustain" + iStr));
                thisVoice->voiceValueSet[i].setCRelease(tree.getRawParameterValue("cRelease" + iStr));
                
                thisVoice->voiceValueSet[i].setMAttack(tree.getRawParameterValue("mAttack" + iStr));
                thisVoice->voiceValueSet[i].setMDecay(tree.getRawParameterValue("mDecay" + iStr));
                thisVoice->voiceValueSet[i].setMSustain(tree.getRawParameterValue("mSustain" + iStr));
                thisVoice->voiceValueSet[i].setMRelease(tree.getRawParameterValue("mRelease" + iStr));
                
                thisVoice->voiceValueSet[i].setIndex(tree.getRawParameterValue("index" + iStr));
                thisVoice->voiceValueSet[i].setFactor(tree.getRawParameterValue("factor" + iStr));
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
