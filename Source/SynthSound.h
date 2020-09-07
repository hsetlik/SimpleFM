/*
  ==============================================================================

    SynthSound.h
    Created: 5 Sep 2020 6:58:45pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <stdio.h>
#if ! JUCE_PROJUCER_LIVE_BUILD
#include "maximilian.h"
#include "OperatorPanelComponent.h"
#endif

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int /*midiNoteNumber*/) //just plays this sound for any midi note
    {
        return true;
    }
    bool appliesToChannel(int /*midiChannel*/) //plays the sound on both channels
    {
        return true;
    }
};
