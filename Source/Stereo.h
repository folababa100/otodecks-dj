#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Stereo  : public AudioSource
{
public:
    Stereo(MixerAudioSource* mixerSource);
    ~Stereo();


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
