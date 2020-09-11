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
enum modLayer{
    base,
    first,
    second,
    third,
    fourth,
    fifth
};
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
    float modOutputSample[6];
    float carOutputSample[6];
    int externalSampleSource[6];
    int dummyIndex = 100;
    modLayer layerSettings[6];
    float mixLevel[6];
    bool sendToMix[6];
};

struct MaxiObjectSet
{
    maxiEnv cMaxiEnvelopes[6];
    maxiEnv mMaxiEnvelopes[6];
    maxiOsc cMaxiOsc[6];
    maxiOsc mMaxiOsc[6];
    
};

class DspProcessor //this only handles things for the operators separately, the mixing is done my the mixer element
{
public:
    DspProcessor(ParameterValSet* pSet, MaxiObjectSet* mSet)
    {
        pVals = pSet;
        mObjs = mSet;
    }
    ~DspProcessor() {}
    void triggerEnvelopes();
    void stopEnvelopes();
    void calculateModFrequencies(); //call this at the beginning of every block
    void setModLayers();//call this in the noteOn method, no need to do it every sample
    void calculateCarFrequencies();
    void setCarSamplesToMix();
    float mixerOutputSample();
    
    //all the assignment has to be done by pointer
    ParameterValSet* pVals;
    MaxiObjectSet* mObjs;
    double fundamental;
};
