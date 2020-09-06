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
    //========================================
    void startNote (int midiNoteNumber,
                    float velocity,
                    juce::SynthesiserSound *sound,
                    int currentPitchWheelPosition)
    {
        env1.trigger = 1;
        level = velocity;
        fundamental = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        printf("fundamental pitch: %f\n", fundamental);
        printf("note with midi no. %d is on \n", midiNoteNumber);
    }
    //=============================================
    void stopNote (float velocity, bool allowTailOff)
    {
        env1.trigger = 0;
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
            env1.setAttack(800);
            env1.setDecay(1500);
            env1.setSustain(0.6);
            env1.setRelease(2000);
            float thisSample = osc1.sinewave(fundamental);
            float envSample = env1.adsr(thisSample, env1.trigger) * level;
            //calculate a sample for each channel
            for(int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, envSample);
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
    double level;
    double fundamental;
    maxiOsc osc1;
    maxiEnv env1;
};
