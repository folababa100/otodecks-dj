#pragma once

#include <JuceHeader.h>


class DJAudioPlayer : public AudioAppComponent, public Timer {
public:
    explicit DJAudioPlayer(AudioFormatManager& formatManager);
    virtual ~DJAudioPlayer();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void loadURL(const URL& audioURL);
    void setGain(double gain);
    void setSpeed(double ratio);
    void setPosition(double posInSecs);
    void setPositionRelative(double pos);
    void setLoop(double seconds);
    void timerCallback() override;
    void start();
    void pause();
    void stop();

    double getPosInTrack() const;
    double getPositionRelative() const;
    bool fileJustLoaded();

private:
    AudioFormatManager& formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    ResamplingAudioSource resampleSource;

    double loopStart{0.0};
    double loopEnd{0.0};
    double loopSeconds{0.0};
    bool justLoaded{false};
    bool loopIsActivated{false};

    static constexpr double MAX_SPEED_RATIO = 100.0;
    static constexpr double MAX_LOOP_SECONDS = 16.0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DJAudioPlayer)
};
