#pragma once

#include <JuceHeader.h>
#include "StereoReverb.h"

//==============================================================================
/*
*/
class DJAudioPlayer : public AudioAppComponent,
    public Timer
{
public:
    DJAudioPlayer(AudioFormatManager& _formatManager);
    ~DJAudioPlayer();
    // Prepare to play
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    // Get next audio block
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;

   // Allows source to release irrelevents after playback stopped
    void releaseResources() override;


    // Reads and loads the track to be played. Inputing the url of audio
    void loadURL(URL audioURL);

    // Sets the track's volume, slider value
    void setGain(double gain);


    // Sets track's speed, slider value
    void setSpeed(double ratio);

    // Sets track's current position in seconds
    void setPosition(double posInSecs);

    // Sets position relative to the track's length and between 0 and 1
    void setPositionRelative(double pos);

    // Sets a section of the track to be played repeatedly.
    void setLoop(double seconds);

    // Call timer
    void timerCallback() override;

    // Plays track
    void start();

    // Pauses track
    void pause();

    // Stops track and restart
    void stop();

    // Get current position of track
    double getPosInTrack();

    // Get position of playhead with relative to track's length, between 0 and 1
    double getPositionRelative();

    // Checks if file have just been loaded & resets the flag
    bool fileJustLoaded();

private:
    AudioFormatManager& formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    ResamplingAudioSource resampleSource{ &transportSource, false, 2 };

    double loopStart;
    double loopEnd;
    double loopSeconds;
    bool justLoaded;
    bool loopIsActivated;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DJAudioPlayer)
};