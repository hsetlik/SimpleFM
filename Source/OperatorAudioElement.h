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

struct ParameterValSet
{
    float cAttackTime;
    void setCAttack(std::atomic<float>* value)
    {
        cAttackTime = *value;
    }
    float cDecayTime;
    void setCDecay(std::atomic<float>* value)
    {
        cDecayTime = *value;
    }
    float cSustainLevel;
    void setCSustain(std::atomic<float>* value)
    {
        cSustainLevel = *value;
    }
    float cReleaseTime;
    void setCRelease(std::atomic<float>* value)
    {
        cReleaseTime = *value;
    }
    float mAttackTime;
    void setMAttack(std::atomic<float>* value)
    {
        mAttackTime = *value;
    }
    float mDecayTime;
    void setMDecay(std::atomic<float>* value)
    {
        mDecayTime = *value;
    }
    float mSustainLevel;
    void setMSustain(std::atomic<float>* value)
    {
        mSustainLevel = *value;
    }
    float mReleaseTime;
    void setMRelease(std::atomic<float>* value)
    {
        mReleaseTime = *value;
    }
    
    double fIndex;
    void setIndex(std::atomic<float>* value)
    {
        fIndex = *value;
    }
    double fFactor;
    void setFactor(std::atomic<float>* value)
    {
       fFactor = *value;
    }
};



