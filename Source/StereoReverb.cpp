#include <JuceHeader.h>
#include "StereoReverb.h"

//==============================================================================
StereoReverb::StereoReverb(MixerAudioSource* mixerSource) : reverbSource(mixerSource, false)
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

StereoReverb::~StereoReverb()
{

}

void StereoReverb::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    reverbSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void StereoReverb::releaseResources()
{
    reverbSource.releaseResources();
}

void StereoReverb::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    // Set parameters during callback
    reverbSource.setParameters(parameters);
    reverbSource.getNextAudioBlock(bufferToFill);
}

void StereoReverb::setBypass()
{
    reverbSource.setBypassed(false);
}


