#include <JuceHeader.h>
#include "Stereo.h"

//==============================================================================
Stereo::Stereo(MixerAudioSource* mixerSource) : reverbSource(mixerSource, false)
{
    // Set bypassed
    reverbSource.setBypassed(true);
    // Set default parameters to 0s
    defaultParameters.roomSize = 0;
    defaultParameters.damping = 0;
    defaultParameters.wetLevel = 0;
    defaultParameters.dryLevel = 0;
    defaultParameters.width = 0;
    defaultParameters.freezeMode = 0;
    reverbSource.setParameters(defaultParameters);
}

Stereo::~Stereo()
{

}

void Stereo::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    reverbSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void Stereo::releaseResources()
{
    reverbSource.releaseResources();
}

void Stereo::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    // Set parameters during callback
    reverbSource.setParameters(parameters);
    reverbSource.getNextAudioBlock(bufferToFill);
}

void Stereo::setBypass()
{
    reverbSource.setBypassed(false);
}


