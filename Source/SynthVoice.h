/*
  ==============================================================================

    SynthVoice.h
    Created: 5 Sep 2020 6:44:09pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
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
    void getIndexVal(std::atomic<float>* iVal)
    {
        modIndex = *iVal;
    }
    void getFactorVal(std::atomic<float>* fVal)
    {
        float rawValue = *fVal;
        if(rawValue > 0)
            modFactor = rawValue;
        else
            modFactor = (1.0 / fabs(rawValue));
    }
    void setCAttack(int index, std::atomic<float>* attack)
    {
        cEnvs[index].setAttack(*attack);
    }
    void setCDecay(int index, std::atomic<float>* decay)
    {
        cEnvs[index].setDecay(*decay);
    }
    void setCSustain(int index, std::atomic<float>* sustain)
    {
        cEnvs[index].setSustain(*sustain);
    }
    void setCRelease(int index, std::atomic<float>* release)
    {
        cEnvs[index].setRelease(*release);
    }
    //modulator envelope
    void setMAttack(int index, std::atomic<float>* attack)
    {
        mEnvs[index].setAttack(*attack);
    }
    void setMDecay(int index, std::atomic<float>* decay)
    {
        mEnvs[index].setDecay(*decay);
    }
    void setMSustain(int index, std::atomic<float>* sustain)
    {
        mEnvs[index].setSustain(*sustain);
    }
    void setMRelease(int index, std::atomic<float>* release)
    {
        mEnvs[index].setRelease(*release);
    }
    void setIndexVal(int index, std::atomic<float>* iVal)
    {
        modIndeces[index] = *iVal;
    }
    void setFactorVal(int index, std::atomic<float>* fVal)
    {
        float rawValue = *fVal;
        if(rawValue > 0)
            modFactors[index] = rawValue;
        else
            modFactors[index] = (1.0 / fabs(rawValue));
    }
    //========================================
    void setupPointers(std::vector<OperatorPanel*> allPanels)
    {
        allOps = allPanels;
    }
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
        for(int i = 0; i < numOperators; ++i)
        {
            cEnvs[i].trigger = 1;
            mEnvs[i].trigger = 1;
            modPitches[i] = fundamental * modFactors[i];
        }
    }
    //=============================================
    void stopNote (float velocity, bool allowTailOff)
    {
        carrierEnv.trigger = 0;
        modulatorEnv.trigger = 0;
        for(int i = 0; i < numOperators; ++i)
        {
            cEnvs[i].trigger = 0;
            mEnvs[i].trigger = 0;
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
     //each operator must be added to this vector
    std::vector<OperatorPanel*> allOps;
private:
    double fundamental;
    
    maxiOsc carrierOsc;
    maxiOsc modulatorOsc;
    maxiEnv carrierEnv;
    maxiEnv modulatorEnv;
    float modFactor; // modulator frequency = fundamental * modFactor
    double modulatorPitch;
    double modIndex;
    
    //vectors to store the above values for multiple operators
    int numOperators;
    std::vector<maxiOsc> cOscs;
    std::vector<maxiOsc> mOscs;
    std::vector<maxiEnv> cEnvs;
    std::vector<maxiEnv> mEnvs;
    std::vector<float> modFactors;
    std::vector<double> modPitches;
    std::vector<double> modIndeces;
   
};
