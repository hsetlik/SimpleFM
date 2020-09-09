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
//each SynthVoice owns an instance of each of these structs
struct ParameterValSet
{
    std::atomic<float>* cAttackValues[6];
    std::atomic<float>* cDecayValues[6];
    std::atomic<float>* cSustainValues[6];
    std::atomic<float>* cReleaseValues[6];
    
    std::atomic<float>* mAttackValues[6];
    std::atomic<float>* mDecayValues[6];
    std::atomic<float>* mSustainValues[6];
    std::atomic<float>* mReleaseValues[6];
    
    std::atomic<float>* modIndexValues[6];
    std::atomic<float>* modFactorValues[6];
};

struct MaxiObjectSet
{
    maxiEnv cMaxiEnvelopes[6];
    maxiEnv mMaxiEnvelopes[6];
    maxiOsc cMaxiOsc[6];
    maxiOsc mMaxiOsc[6];
    float maxiModIndeces[6];
    float maxiModFactors[6];
};


