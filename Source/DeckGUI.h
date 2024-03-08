#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "Initialise.h"

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

    void buttonClicked(Button* button) override;
    void sliderValueChanged(Slider* slider) override;

    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;
    void timerCallback() override;
    void loadTrack(String trackName, String trackDuration, URL trackPath);
    static String getSongTitle(File songFile);
    String getSongDuration(File songFile);

private:

    void posBtn(ImageButton& button, double x);
    AffineTransform getTransform();
    ImageButton playButton;
    ImageButton pauseButton;
    ImageButton stopButton;
    ImageButton loadButton;
    Slider posSlider;
    Image disc;
    Colour accentColour;

    bool isLoaded;
    int userExp;

    AudioFormatManager& formatManager;
    WaveformDisplay waveformDisplay;
    DJAudioPlayer* player;
    TooltipWindow* tooltipWindow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};