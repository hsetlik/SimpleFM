/*
  ==============================================================================

    Operator.h
    Created: 5 Sep 2020 9:55:33pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"

class OperatorPanel : public juce::Component, public juce::Slider::Listener
{
public:
    OperatorPanel();
    ~OperatorPanel() {}
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;
    //child components
    juce::Slider aSlider;
    juce::Slider dSlider;
    juce::Slider sSlider;
    juce::Slider rSlider;
    
    //points to the maxiEnv owned by an OperatorVoice object
    maxiEnv* envelope;
};


class OperatorVoice : public juce::SynthesiserVoice
{
    OperatorVoice();
    ~OperatorVoice() {}
    bool canPlaySound(juce::SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    void startNote (int midiNoteNumber,
                    float velocity,
                    juce::SynthesiserSound *sound,
                    int currentPitchWheelPosition);
    
    void stopNote (float velocity, bool allowTailOff);
    
    void pitchWheelMoved(int newPitchWheelVal)
    {
        
    }
    void controllerMoved(int controllerNumber, int controllerValue)
    {
        
    }
    void aftertouchChanged (int newAftertouchValue)
    {

    }
    void channelPressureChanged (int newChannelPressureValue)
    {
        
    }
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples);
    //these two are public bc the GUI needs to point to them
    maxiOsc thisOsc;
    maxiEnv thisEnv;
private:
    bool isModulated;
    maxiEnv* modEnv; //this points to the ouput sample of another Operator
    float modDepth; //between 0 and 1 coefficient for the modEnv
    int modFactor; // above 1, fundamental *= modFactor, below 0, fundamental /= (modFactor * -1)
    double fundamental; //pitch straight from MIDI number
    double frequency; //post-modulation pitch
    //note: frequency = (fundamental * modFactor) + (*modEnv * modDepth)
};
