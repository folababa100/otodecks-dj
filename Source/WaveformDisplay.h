#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay : public Component,
    public ChangeListener
{
public:

    WaveformDisplay(AudioFormatManager& formatManagerToUse,
                    AudioThumbnailCache& cacheToUse,
                    Colour& colourToUse);
    ~WaveformDisplay();

    void paint(Graphics& g) override;
    void resized() override;

    void changeListenerCallback(ChangeBroadcaster* source) override;

    void loadFile(String fileName, String fileLength, URL audioURL);

    // Set position of playhead relative to the track's length and between 0 and 1
    void setPositionRelative(double pos);

    // Calculate remaining duration of the track currently playing
    void updateTrackDuration(double currentPos);

private:
    // Calculate track length, inputing length in seconds and converts it to a string
    static String getSongDuration(double lengthInSecs);

    AudioThumbnail audioThumb;
    AudioFormatManager& formatManager;

    bool fileLoaded;
    double position;
    double posInSecs;

    String trackName;
    String trackDuration;
    Colour accentColour;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};