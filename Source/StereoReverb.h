#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class StereoReverb  : public AudioSource
{
public:
    StereoReverb(MixerAudioSource* mixerSource);
    ~StereoReverb();


    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void setBypass();

    // Parameters for reverb audio filters
    Reverb::Parameters parameters;
    Reverb::Parameters defaultParameters;
private:
     // Reverb audio source apply -> audio source
     // &mixerSource -> MainComponent
        ReverbAudioSource reverbSource;
};
