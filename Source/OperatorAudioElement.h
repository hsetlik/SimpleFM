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
    float cAttackValues[6];
    float cDecayValues[6];
    float cSustainValues[6];
    float cReleaseValues[6];
    
    float mAttackValues[6];
    float mDecayValues[6];
    float mSustainValues[6];
    float mReleaseValues[6];
    
    double modIndexValues[6];
    double modFactorValues[6];
};

struct MaxiObjectSet
{
    maxiEnv cMaxiEnvelopes[6];
    maxiEnv mMaxiEnvelopes[6];
    maxiOsc cMaxiOsc[6];
    maxiOsc mMaxiOsc[6];
};


