/*
  ==============================================================================

    SynthVoice.h
    Created: 5 Sep 2020 6:44:09pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include "maximilian.h"
#include <JuceHeader.h>
#include "SynthSound.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    void getCAttack(std::atomic<float>* attack)
    {
        carrierEnv.setAttack(*attack);
    }
    void getCDecay(std::atomic<float>* decay)
    {
        carrierEnv.setDecay(*decay);
    }
    void getCSustain(std::atomic<float>* sustain)
    {
        carrierEnv.setSustain(*sustain);
    }
    void getCRelease(std::atomic<float>* release)
    {
        carrierEnv.setRelease(*release);
    }
    //modulator envelope
    void getMAttack(std::atomic<float>* attack)
    {
        modulatorEnv.setAttack(*attack);
    }
    void getMDecay(std::atomic<float>* decay)
    {
        modulatorEnv.setDecay(*decay);
    }
    void getMSustain(std::atomic<float>* sustain)
    {
        modulatorEnv.setSustain(*sustain);
    }
    void getMRelease(std::atomic<float>* release)
    {
        modulatorEnv.setRelease(*release);
    }
    
    //========================================
    void startNote (int midiNoteNumber,
                    float velocity,
                    juce::SynthesiserSound *sound,
                    int currentPitchWheelPosition)
    {
        carrierEnv.trigger = 1;
        modulatorEnv.trigger = 1;
        fundamental = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        modulatorPitch = fundamental * modFactor;
        printf("fundamental pitch: %f\n", fundamental);
        printf("mod pitch: %f\n", modulatorPitch);
        carrierEnv.setAttack(150);
        carrierEnv.setDecay(1500);
        carrierEnv.setSustain(0.7);
        carrierEnv.setRelease(900);
        
        modulatorEnv.setAttack(1600);
        modulatorEnv.setDecay(1200);
        modulatorEnv.setSustain(0.4);
        modulatorEnv.setRelease(800);
    }
    //=============================================
    void stopNote (float velocity, bool allowTailOff)
    {
        carrierEnv.trigger = 0;
        modulatorEnv.trigger = 0;
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
private:
    double fundamental;
    maxiOsc carrierOsc;
    maxiOsc modulatorOsc;
    maxiEnv carrierEnv;
    maxiEnv modulatorEnv;
    float modFactor = (1.0 / 4.0); // modulator frequency = fundamental * modFactor
    double modulatorPitch;
    double modIndex = 85.0;
};
