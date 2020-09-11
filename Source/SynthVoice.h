/*
  ==============================================================================

    SynthVoice.h
    Created: 5 Sep 2020 6:44:09pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "OperatorAudioElement.h"
#include "SynthSound.h"
#include "MixerAudioElement.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    //=========================================
    void caVoiceSet(int index, std::atomic<float>* value)
    {
        voiceParamValues.cAttackValues[index] = value;
        voiceMaxiObjs.cMaxiEnvelopes[index].setAttack(*voiceParamValues.cAttackValues[index]);
    }
    void cdVoiceSet(int index, std::atomic<float>* value)
    {
        voiceParamValues.cDecayValues[index] = value;
        voiceMaxiObjs.cMaxiEnvelopes[index].setDecay(*voiceParamValues.cDecayValues[index]);
    }
    void csVoiceSet(int index, std::atomic<float>* value)
    {
        voiceParamValues.cSustainValues[index] = value;
        voiceMaxiObjs.cMaxiEnvelopes[index].setSustain(*voiceParamValues.cSustainValues[index]);
    }
    void crVoiceSet(int index, std::atomic<float>* value)
    {
        voiceParamValues.cReleaseValues[index] = value;
        voiceMaxiObjs.cMaxiEnvelopes[index].setRelease(*value);
    }
    void maVoiceSet(int index, std::atomic<float>* value)
    {
        voiceParamValues.mAttackValues[index] = value;
        voiceMaxiObjs.mMaxiEnvelopes[index].setAttack(*value);
    }
    void mdVoiceSet(int index, std::atomic<float>* value)
    {
        voiceParamValues.mDecayValues[index] = value;
        voiceMaxiObjs.mMaxiEnvelopes[index].setDecay(*value);
    }
    void msVoiceSet(int index, std::atomic<float>* value)
    {
        voiceParamValues.mSustainValues[index] = value;
        voiceMaxiObjs.mMaxiEnvelopes[index].setSustain(*value);
    }
    void mrVoiceSet(int index, std::atomic<float>* value)
    {
        voiceParamValues.mReleaseValues[index] = value;
        voiceMaxiObjs.mMaxiEnvelopes[index].setRelease(*value);
    }
    void iVoiceSet(int index, std::atomic<float>* value)
    {
        voiceParamValues.modIndexValues[index] = value;
        
    }
    void fVoiceSet(int index, std::atomic<float>* value)
    {
        voiceParamValues.modFactorValues[index] = value;
    }
    void selectorSet(int index, juce::RangedAudioParameter* param)
    {
        int indexNum = param->getParameterIndex();
        voiceParamValues.externalSampleSource[index] = indexNum;
    }
    void mixerOnSet(int index, bool state)
    {
        voiceParamValues.sendToMix[index] = state;
    }
    
    
    void mixerSet(int index, std::atomic<float>* value)
    {
        voiceParamValues.mixLevel[index] = *value;
    }
    //========================================
    void startNote (int midiNoteNumber,
                    float velocity,
                    juce::SynthesiserSound *sound,
                    int currentPitchWheelPosition)
    {
        fundamental = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        proc.triggerEnvelopes();
        proc.setModLayers();
    }
    //=============================================
    void stopNote (float velocity, bool allowTailOff)
    {
        carrierEnv.trigger = 0;
        modulatorEnv.trigger = 0;
        for(int i = 0; i < 6; ++i)
        {
            
        }
        allowTailOff = true;
        if(velocity == 0)
            clearCurrentNote();
    }
    //===========================================
    void pitchWheelMoved(int newPitchWheelVal)
    {
        
    }
    //=============================================
    void controllerMoved(int controllerNumber, int controllerValue)
    {
        
    }
    //===============================================
    void aftertouchChanged (int newAftertouchValue)
    {

    }
    //==============================================
    void channelPressureChanged (int newChannelPressureValue)
    {
        
    }
    //===============================================
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
    {
        if(parameterAssignmentFinished && buttonAssignmentFinished)
        {
        for(int sample = 0; sample < numSamples; ++sample) //calculate all the samples for this block
        {
            proc.calculateModFrequencies();
            proc.calculateCarFrequencies();
            proc.setCarSamplesToMix();
            float mixSample = proc.mixerOutputSample();
            for(int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, mixSample);
            }
            ++startSample;
        }
        }
    }
    //==============================================
    void setCurrentPlaybackSampleRate (double newRate)
    {
        
    }
    //===============================================
    ParameterValSet voiceParamValues;
    MaxiObjectSet voiceMaxiObjs;
    DspProcessor proc = DspProcessor(&voiceParamValues, &voiceMaxiObjs, &fundamental);
    bool parameterAssignmentFinished = false;
    bool buttonAssignmentFinished = false;
    double fundamental;
private:
    
    maxiOsc carrierOsc;
    maxiOsc modulatorOsc;
    maxiEnv carrierEnv;
    maxiEnv modulatorEnv;
    //==============================================
    
    //===============================================
    float modFactor;
    double modulatorPitch;
    double modIndex;
    
};
