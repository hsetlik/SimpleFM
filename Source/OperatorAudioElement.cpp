/*
  ==============================================================================

    OperatorAudioElements.cpp
    Created: 8 Sep 2020 9:25:23am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "OperatorAudioElement.h"


void DspProcessor::triggerEnvelopes()
{
    for(int i = 0; i < 6; ++i)
    {
        mObjs->cMaxiEnvelopes[i].setTrigger(1);
        mObjs->mMaxiEnvelopes[i].setTrigger(1);
    }
}

void DspProcessor::stopEnvelopes()
{
   for(int i = 0; i < 6; ++i)
    {
        mObjs->cMaxiEnvelopes[i].setTrigger(0);
        mObjs->mMaxiEnvelopes[i].setTrigger(0);
    }
}

void DspProcessor::setModLayers()
{
    for(int i = 0; i < 6; ++i)
    {
        if(pVals->externalSampleSource[i] == 7)
            pVals->layerSettings[i] = base;
        else if(pVals->externalSampleSource[pVals->externalSampleSource[i]] == 7)
            pVals->layerSettings[i] = first;
        else if(pVals->externalSampleSource[pVals->layerSettings[i]] == first)
            pVals->layerSettings[i] = second;
        else if(pVals->externalSampleSource[pVals->layerSettings[i]] == second)
            pVals->layerSettings[i] = third;
        else if(pVals->externalSampleSource[pVals->layerSettings[i]] == third)
            pVals->layerSettings[i] = fourth;
        else if(pVals->externalSampleSource[pVals->layerSettings[i]] == fourth)
            pVals->layerSettings[i] = fifth;
            
    }
}
void DspProcessor::setModSources()
{
    
}

void DspProcessor::calculateModFrequencies()
{
    for(int i = 0; i < 6; ++i)
    {
        if(pVals->layerSettings[i] == base)
        {
            auto baseFreq = *fundamental * *pVals->modFactorValues[i];
            auto preEnv = mObjs->mMaxiOsc[i].sinewave(baseFreq);
            auto postEnv = mObjs->mMaxiEnvelopes[i].adsr(preEnv);
            pVals->modOutputSample[i] = postEnv;
        } else if(pVals->layerSettings[i] == first)
        {
            auto baseFreq = *fundamental * *pVals->modFactorValues[i];
            auto modFreq = baseFreq + (pVals->modOutputSample[pVals->externalSampleSource[i]] * pVals->dummyIndex);
            auto preEnv = mObjs->mMaxiOsc[i].sinewave(modFreq);
            auto postEnv = mObjs->mMaxiEnvelopes[i].adsr(preEnv);
            pVals->modOutputSample[i] = postEnv;
        } else if(pVals->layerSettings[i] == second)
        {
            auto baseFreq = *fundamental * *pVals->modFactorValues[i];
            auto modFreq = baseFreq + pVals->modOutputSample[pVals->externalSampleSource[i]];
            auto preEnv = mObjs->mMaxiOsc[i].sinewave(modFreq);
            auto postEnv = mObjs->mMaxiEnvelopes[i].adsr(preEnv);
            pVals->modOutputSample[i] = postEnv;
        } else if(pVals->layerSettings[i] == third)
        {
            auto baseFreq = *fundamental * *pVals->modFactorValues[i];
            auto modFreq = baseFreq + (pVals->modOutputSample[pVals->externalSampleSource[i]] * pVals->dummyIndex);
            auto preEnv = mObjs->mMaxiOsc[i].sinewave(modFreq);
            auto postEnv = mObjs->mMaxiEnvelopes[i].adsr(preEnv);
            pVals->modOutputSample[i] = postEnv;
        } else if(pVals->layerSettings[i] == fourth)
        {
            auto baseFreq = *fundamental * *pVals->modFactorValues[i];
            auto modFreq = baseFreq + pVals->modOutputSample[pVals->externalSampleSource[i]];
            auto preEnv = mObjs->mMaxiOsc[i].sinewave(modFreq);
            auto postEnv = mObjs->mMaxiEnvelopes[i].adsr(preEnv);
            pVals->modOutputSample[i] = postEnv;
        } else if(pVals->layerSettings[i] == fifth)
        {
            auto baseFreq = *fundamental * *pVals->modFactorValues[i];
            auto modFreq = baseFreq + pVals->modOutputSample[pVals->externalSampleSource[i]];
            auto preEnv = mObjs->mMaxiOsc[i].sinewave(modFreq);
            auto postEnv = mObjs->mMaxiEnvelopes[i].adsr(preEnv, mObjs->mMaxiEnvelopes[i].trigger);
            pVals->modOutputSample[i] = postEnv;
        }
    }
}

void DspProcessor::calculateCarFrequencies()
{
    for(int i = 0; i < 6; ++i)
    {
        auto freq = *fundamental + pVals->modOutputSample[i];
        auto preEnv = mObjs->cMaxiOsc[i].sinewave(freq);
        auto postEnv = mObjs->cMaxiEnvelopes[i].adsr(preEnv, mObjs->cMaxiEnvelopes[i].trigger);
        pVals->carOutputSample[i] = postEnv;
    }
}

void DspProcessor::setCarSamplesToMix()
{
    for(int i = 0; i < 6; ++i)
    {
        float levelFactor = pVals->mixLevel[i];
        if(pVals->sendToMix[i] == false)
            levelFactor = 0.0f;
        pVals->carOutputSample[i] *= levelFactor;
    }
}

float DspProcessor::mixerOutputSample()
{
    double sampleSum = 0.0f;
    for(int i = 0; i < 6; ++i)
    {
        sampleSum += pVals->carOutputSample[i];
    }
    float output = sampleSum / 6.0f;
    return output;
}
