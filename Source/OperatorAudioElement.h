/*
  ==============================================================================

    OperatorAudioElements.h
    Created: 8 Sep 2020 8:43:18am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "maximilian.h"

class OperatorAudioElement
{
public:
    OperatorAudioElement(int index);
    ~OperatorAudioElement() {}
    maxiOsc carrierOsc;
    maxiOsc modulatorOsc;
    maxiEnv carrierEnv;
    maxiEnv modulatorEnv;
    //each of the set... functions gets called for each operator on each voice in the processor
    void setCAttack(std::atomic<float>* attack)
    {
        carrierEnv.setAttack(*attack);
    }
    void setCDecay(std::atomic<float>* decay)
    {
        carrierEnv.setDecay(*decay);
    }
    void setCSustain(std::atomic<float>* sustain)
    {
        carrierEnv.setSustain(*sustain);
    }
    void setCRelease(std::atomic<float>* release)
    {
        carrierEnv.setRelease(*release);
    }
    void setMAttack(std::atomic<float>* attack)
    {
        modulatorEnv.setAttack(*attack);
    }
    void setMDecay(std::atomic<float>* decay)
    {
        modulatorEnv.setDecay(*decay);
    }
    void setMSustain(std::atomic<float>* sustain)
    {
        modulatorEnv.setSustain(*sustain);
    }
    void setMRelease(std::atomic<float>* release)
    {
        modulatorEnv.setRelease(*release);
    }
    void setIndexVal(std::atomic<float>* iVal)
    {
        modIndex = *iVal;
    }
    void setFactorVal(std::atomic<float>* fVal)
    {
        float rawValue = *fVal;
        if(rawValue > 0)
            modFactor = rawValue;
        else
            modFactor = (1.0 / fabs(rawValue));
        
    }
    float modFactor;
    float modPitch;
    float modIndex;
    int OpIndex;
};

struct OperatorParameterNumbers
{
    float cAttackTime;
    float cDecayTime;
    float cSustainLevel;
    float cReleaseTime;
    
    float mAttackTime;
    float mDecayTime;
    float mSustainLevel;
    float mReleaseTime;
    
    double fIndex;
    double fFactor;
};
