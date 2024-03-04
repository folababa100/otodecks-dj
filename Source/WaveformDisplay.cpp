#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager& formatManagerToUse,
    AudioThumbnailCache& cacheToUse,
    Colour& colourToUse) :
    audioThumb(1000, formatManagerToUse, cacheToUse),
    fileLoaded(false),
    position(0.0),
    posInSecs(0.0),
    trackName(""),
    trackDuration(""),
    formatManager(formatManagerToUse),
    accentColour(colourToUse)

{
    audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint(Graphics& g)
{
    // Fill background
    g.fillAll(Colour::fromRGBA(255, 183, 197, 255));

    g.setColour(Colours::orangered);
    if (fileLoaded)
    {
        double rowW = getWidth() / 4.0;

        g.setFont(20.0f);
        g.setColour(Colours::white);

        // Draw song title.
        Rectangle<float> titleArea(10, 5, (float)(rowW * 3) - 5, 20);
        g.drawText(trackName, titleArea, Justification::centredLeft, true);

        // Draw song length.
        Rectangle<float> durationArea((float)(rowW * 2.8), 5, (float)rowW, 20);
        g.drawText(trackDuration, durationArea, Justification::centredRight, true);

        // Draw left channel.
        g.setColour(accentColour);
        Rectangle<int> waveformArea(0, 30, getWidth(), getHeight() - 30);
        audioThumb.drawChannel(g,
            waveformArea,
            0.0,
            audioThumb.getTotalLength(),
            0,
            1.0f);
        g.setColour(Colour::fromRGBA(76, 104, 215, 255));

        // Draw playhead.
        double playheadPos = position * getWidth();
        Line<float> arrowLine(Point<float>((float)playheadPos, 30),
            Point<float>((float)playheadPos, 40));
        g.drawArrow(arrowLine, 20, 20, 55);
        g.drawRect((int)playheadPos, 35, 2, getHeight() - 5);
    }
    else
    {
        g.setFont(20.0f);
        g.setColour(Colour::fromRGBA(102, 157, 246, 255));
        g.drawText("File not loaded...", getLocalBounds(),
            Justification::centred, true);   // draw some placeholder text
    }
}

void WaveformDisplay::resized()
{

}

void WaveformDisplay::loadFile(String fileName, String fileLength, URL audioURL)
{
    trackName = fileName;
    trackDuration = fileLength;

    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new URLInputSource(audioURL));
    if (fileLoaded)
    {
        repaint();
    }
    else {
        DBG("WaveformDisplay: not loaded!");
    }
}

void WaveformDisplay::changeListenerCallback(ChangeBroadcaster* source)
{
    repaint();
}

void WaveformDisplay::setPositionRelative(double pos)
{
    posInSecs = pos;

    if (pos != position && !isnan(pos))
    {
        position = pos; // goes from 0 to 1;
        repaint();
    }
}

String WaveformDisplay::getSongDuration(double lengthInSecs)
{
    int minutes = (int)floor(lengthInSecs / 60.0);
    int seconds = (int)floor(lengthInSecs - (minutes * 60.0));

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

void WaveformDisplay::updateTrackDuration(double currentPos)
{
    double remainingDuration;
    double totalDuration = audioThumb.getTotalLength();

    if (currentPos >= totalDuration)
    {
        remainingDuration = 0.0;
    }
    else
    {
        remainingDuration = totalDuration - currentPos;
    }

    trackDuration = getSongDuration(remainingDuration);
}