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

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    //========================================
    void startNote (int midiNoteNumber,
                    float velocity,
                    juce::SynthesiserSound *sound,
                    int currentPitchWheelPosition)
    {
        fundamental = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        carrierEnv.trigger = 1;
        modulatorEnv.trigger = 1;
        modulatorPitch = fundamental * modFactor;
        printf("fundamental pitch: %f\n", fundamental);
        printf("mod pitch: %f\n", modulatorPitch);
       for(int i : modPitches)
       {
           cEnvs[i].trigger = 1;
           mEnvs[i].trigger = 1;
           modFactors[i] = voiceValueSet[i].fFactor;
           modPitches[i] = fundamental * modFactors[i];
       }
    }
    //=============================================
    void stopNote (float velocity, bool allowTailOff)
    {
        carrierEnv.trigger = 0;
        modulatorEnv.trigger = 0;
        allowTailOff = true;
        for(int i : modPitches)
        {
            cEnvs[i].trigger = 0;
            mEnvs[i].trigger = 0;
        }
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
        for(int sample = 0; sample < numSamples; ++sample) //calculate all the samples for this block
        {
            float modSample = modulatorOsc.sinewave(modulatorPitch);
            float modEnvSample = modulatorEnv.adsr(modSample, modulatorEnv.trigger);
            float carSample = carrierOsc.sinewave(fundamental +
                                                  (modEnvSample * modIndex));
            float carEnvSample = carrierEnv.adsr(carSample, carrierEnv.trigger);
            //calculate a sample for each channel
            for(int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, carEnvSample);
            }
            ++startSample;
        }
    }
    //==============================================
    void setCurrentPlaybackSampleRate (double newRate)
    {
        
    }
    //===============================================
    ParameterValSet voiceValueSet[6];
private:
    double fundamental;
    maxiOsc carrierOsc;
    maxiOsc modulatorOsc;
    maxiEnv carrierEnv;
    maxiEnv modulatorEnv;
    //==============================================
    maxiOsc cOscs[6];
    maxiOsc mOscs[6];
    maxiEnv cEnvs[6];
    maxiEnv mEnvs[6];
    float modFactors[6];
    float modPitches[6];
    
    //===============================================
    float modFactor;
    double modulatorPitch;
    double modIndex;
    
};
