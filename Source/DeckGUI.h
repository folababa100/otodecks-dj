#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
// #include "StereoReverbGUI.h" // Include if you use StereoReverbGUI in your DeckGUI
#include "Initialise.h" // Corrected spelling if file exists and is necessary

//==============================================================================
/*
    This class represents a GUI component for a deck in a DJ application.
    It includes controls for loading, playing, pausing, and stopping tracks,
    as well as a waveform display and a position slider.
*/

class LibraryComponent;
class DeckGUI  : public Component,
    public Button::Listener,
    public Slider::Listener,
    public FileDragAndDropTarget,
    public Timer
{
public:
    DeckGUI(DJAudioPlayer* _player,
        AudioFormatManager& formatManagerToUse,
        AudioThumbnailCache& cacheToUse,
        Colour& colourToUse,
        TooltipWindow* _tooltipWindow);
    ~DeckGUI();

    void loadImageButtonImage(ImageButton& button, const void* imageData, size_t imageSize);
    void paint(Graphics& g) override;
    void resized() override;

    // Implements Button::Listener, pointer to the button that was clicked.
    void buttonClicked(Button* button) override;

    // Implements Slider::Listener, pointer to the slider whose value changed.
    void sliderValueChanged(Slider* slider) override;

    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;

    // Implements Timer.
    void timerCallback() override;

    // Loads track, name, duration & path as URL
    void loadTrack(String trackName, String trackDuration, URL trackPath);

    // Get track title
    static String getSongTitle(File songFile);

    // Get track length
    String getSongDuration(File songFile);

private:

    // Positioning buttons
    void posBtn(ImageButton& button, double x);

    // Apply rotation to disc record as a function of track's current position.
    AffineTransform getTransform();

    // Image buttons (Control buttons)
    ImageButton playButton;
    ImageButton pauseButton;
    ImageButton stopButton;
    ImageButton loadButton;

    // Slider
    Slider posSlider;

    // Disc image
    Image disc;

    // Colour for respective deck
    Colour accentColour;

    bool isLoaded;
    int userExp;

    AudioFormatManager& formatManager;
    WaveformDisplay waveformDisplay;
    DJAudioPlayer* player;
    TooltipWindow* tooltipWindow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};