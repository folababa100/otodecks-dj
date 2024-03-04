#include <JuceHeader.h>
#include "DeckGUI.h"
#include "Initialise.h"


DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 AudioFormatManager& formatManagerToUse,
                 AudioThumbnailCache& cacheToUse,
                 Colour& colourToUse,
                 TooltipWindow* _tooltipWindow
                ) : player(_player),
                    formatManager(formatManagerToUse),
                    waveformDisplay(formatManagerToUse, cacheToUse, colourToUse),
                    accentColour(colourToUse),
                    tooltipWindow(_tooltipWindow),
                    isLoaded(false),
                    userExp(0)
    {
    // Get disc record image to display.
    disc = ImageCache::getFromMemory(BinaryData::dj_9_png, BinaryData::dj_9_pngSize);

    loadImageButtonImage(playButton, BinaryData::play_png, BinaryData::play_pngSize);
    loadImageButtonImage(pauseButton, BinaryData::pause_png, BinaryData::pause_pngSize);
    loadImageButtonImage(stopButton, BinaryData::stop_png, BinaryData::stop_pngSize);
    loadImageButtonImage(loadButton, BinaryData::load_png, BinaryData::load_pngSize);

    Initialise::buttonOptions(this, &playButton, this, true, "", 0.8f);
    Initialise::buttonOptions(this, &pauseButton, this, true, "", 0.8f);
    Initialise::buttonOptions(this, &stopButton, this, true, "", 0.8f);
    Initialise::buttonOptions(this, &loadButton, this, true, "", 0.8f);

    addAndMakeVisible(posSlider);
    addAndMakeVisible(waveformDisplay);

    posSlider.addListener(this);
    posSlider.setRange(0.0, 1.0);

    startTimer(500);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::loadImageButtonImage(ImageButton& button, const void* imageData, size_t imageSize) {
    auto image = ImageCache::getFromMemory(imageData, imageSize);
    button.setImages(true, true, true, image, 1, Colours::transparentWhite, Image(nullptr), 1, Colours::transparentWhite, Image(nullptr), 1, Colours::transparentBlack);
}

void DeckGUI::paint(Graphics& g)
{

    // Background colour
    g.fillAll(Colour::fromRGBA(33, 0, 75, 255));

    // Set position, transform the disc
    g.setOrigin(getWidth() / 2, getHeight() / 1.8);

    // Set origin of disc rotation
    AffineTransform transform(AffineTransform::translation((float)(disc.getWidth() / -2),
        (float)(disc.getHeight() / -2)));

    // Draw disc rotation on file load & play
    transform = transform.followedBy(getTransform());

    // Draw disc img transformation
    g.drawImageTransformed(disc, transform, false);

    repaint();
}


void DeckGUI::resized()
{
    double rowH = (double)(getHeight() / 8);
    double rowW = (double)(getWidth() / 8);
    double buttonW = (double)(getWidth() / 10);
    double layoutH = (double)(getHeight() / 3);

    posBtn(playButton, buttonW - 8);
    posBtn(pauseButton, buttonW * 3);
    posBtn(stopButton, buttonW * 5 + 8);
    posBtn(loadButton, buttonW * 7 + 16);

    posSlider.setBounds(rowW, rowH * 2, rowW * 6, rowH * 5);
    posSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    posSlider.setMouseCursor(MouseCursor::DraggingHandCursor);
    posSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    posSlider.setColour(Slider::ColourIds::thumbColourId, accentColour);
    posSlider.setColour(Slider::ColourIds::rotarySliderFillColourId, Colour::fromRGBA(103, 0, 232, 255));
    posSlider.setRotaryParameters(MathConstants<float>::pi,
        MathConstants<float>::twoPi + MathConstants<float>::pi,
        true);

    waveformDisplay.setBounds(0, 0, getWidth(), layoutH - rowH / 2);
}

void DeckGUI::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        player->start();

        if (isLoaded)
        {
            playButton.setToggleState(true, NotificationType::dontSendNotification);
            pauseButton.setToggleState(false, NotificationType::dontSendNotification);
            stopButton.setToggleState(false, NotificationType::dontSendNotification);
            loadButton.setToggleState(false, NotificationType::dontSendNotification);
        }
    }

    if (button == &pauseButton)
    {
        player->pause();

        if (isLoaded)
        {
            playButton.setToggleState(false, NotificationType::dontSendNotification);
            pauseButton.setToggleState(true, NotificationType::dontSendNotification);
            stopButton.setToggleState(false, NotificationType::dontSendNotification);
            loadButton.setToggleState(false, NotificationType::dontSendNotification);
        }
    }

    if (button == &stopButton)
    {
        player->stop();

        if (isLoaded)
        {
            playButton.setToggleState(false, NotificationType::dontSendNotification);
            pauseButton.setToggleState(false, NotificationType::dontSendNotification);
            stopButton.setToggleState(true, NotificationType::dontSendNotification);
            loadButton.setToggleState(false, NotificationType::dontSendNotification);
        }
    }

    if (button == &loadButton)
    {
        if (isLoaded)
        {
            playButton.setToggleState(false, NotificationType::dontSendNotification);
            pauseButton.setToggleState(false, NotificationType::dontSendNotification);
            stopButton.setToggleState(false, NotificationType::dontSendNotification);
            loadButton.setToggleState(true, NotificationType::dontSendNotification);
        }

        FileChooser chooser{ "Select a music file..." };

        if (chooser.browseForFileToOpen())
        {
            File trackFile = chooser.getResult();
            String trackName = getSongTitle(trackFile);
            String trackDuration = getSongDuration(trackFile);
            URL trackPath = URL{ trackFile };

            player->loadURL(trackPath);
            waveformDisplay.loadFile(trackName, trackDuration, trackPath);

            isLoaded = true;
            playButton.setToggleState(false, NotificationType::dontSendNotification);
            pauseButton.setToggleState(false, NotificationType::dontSendNotification);
            stopButton.setToggleState(false, NotificationType::dontSendNotification);
            loadButton.setToggleState(false, NotificationType::dontSendNotification);

            userExp++;
        }
    }
}

void DeckGUI::sliderValueChanged(Slider* slider)
{
    if (slider == &posSlider)
    {
        double sliderValue = slider->getValue();

        if (sliderValue >= 1.0)
        {
            sliderValue = 0.0;
            player->setPositionRelative(sliderValue);
            player->start();
        }
        else
        {
            player->setPositionRelative(sliderValue);
        }
    }
}

bool DeckGUI::isInterestedInFileDrag(const StringArray& files)
{
    return true;
}

void DeckGUI::filesDropped(const StringArray& files, int x, int y)
{
    if (files.size() == 1)
    {
        String trackName = getSongTitle(File{ files[0] });
        String trackDuration = getSongDuration(File{ files[0] });
        URL trackPath = URL{ File{files[0]} };
        player->loadURL(trackPath);
        waveformDisplay.loadFile(trackName, trackDuration, trackPath);

        isLoaded = true;
        playButton.setToggleState(false, NotificationType::dontSendNotification);
        pauseButton.setToggleState(false, NotificationType::dontSendNotification);
        stopButton.setToggleState(false, NotificationType::dontSendNotification);
        loadButton.setToggleState(false, NotificationType::dontSendNotification);

        userExp++;
    }
}

void DeckGUI::timerCallback()
{
    double relativePosition = player->getPositionRelative();

    if (!isnan(relativePosition))
    {
        waveformDisplay.setPositionRelative(relativePosition);
        waveformDisplay.updateTrackDuration(player->getPosInTrack());
        posSlider.setValue(relativePosition);
    }

    if (userExp <= 2)
    {
        posSlider.setTooltip("Click and drag disc to the right/left or \nup to change the current position.");
    }
    else
    {
        posSlider.setTooltip("");
    }
}

void DeckGUI::loadTrack(String trackName, String trackDuration, URL trackPath)
{
    player->loadURL(trackPath);
    waveformDisplay.loadFile(trackName, trackDuration, trackPath);

    isLoaded = true;
    playButton.setToggleState(false, NotificationType::dontSendNotification);
    pauseButton.setToggleState(false, NotificationType::dontSendNotification);
    stopButton.setToggleState(false, NotificationType::dontSendNotification);
    loadButton.setToggleState(false, NotificationType::dontSendNotification);

    userExp++;
}

String DeckGUI::getSongTitle(File songFile)
{
    String songTitle{ songFile.getFileNameWithoutExtension() };
    return songTitle;
}

String DeckGUI::getSongDuration(File songFile)
{
    int numSamples{ 0 };
    double sampleRate{ 0.0 };
    double lengthInSecs{ 0.0 };
    auto* reader = formatManager.createReaderFor(URL{ songFile }.createInputStream(false));

    if (reader != nullptr) // good file!
    {
        numSamples = reader->lengthInSamples;
        sampleRate = reader->sampleRate;
        lengthInSecs = numSamples / sampleRate;
    }

    // Delete reader after using to prevent any memory from leaking.
    delete reader;

    int minutes = floor(lengthInSecs / 60.0);
    int seconds = floor(lengthInSecs - (minutes * 60));

    String songLength;

    if (seconds >= 0 && seconds < 10)
    {
        songLength = String{ minutes } + ":0" + String{ seconds };
    }
    else
    {
        songLength = String{ minutes } + ":" + String{ seconds };
    }

    return songLength;
}

void DeckGUI::posBtn(ImageButton& button, double x)
{
    double rowH = (double)(getHeight() / 8);
    double buttonW = (double)(getWidth() / 10);

    button.setBounds(x, rowH * 7.1 - 2, buttonW * 2, rowH / 1.2);
    button.setMouseCursor(MouseCursor::PointingHandCursor);
}

AffineTransform DeckGUI::getTransform()
{
    AffineTransform t;
    t = t.rotated(fmod(0.15 * player->getPosInTrack(), 2.0) * MathConstants<float>::twoPi);

    return t;
}