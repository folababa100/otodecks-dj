#include <JuceHeader.h>
#include "DJPanel.h"
#include "Initialise.h"

//==============================================================================
DJPanel::DJPanel(DJAudioPlayer* _player,
    TooltipWindow* _tooltipWindow)
    : player(_player),
    tooltipWindow(_tooltipWindow),
    hcPos1(-1.0),
    hcPos2(-1.0),
    hcPos3(-1.0),
    hcPos4(-1.0),
    experienceLevel(0)
{
    Initialise::sliderOptions(this, &volSlider, this, Slider::LinearVertical, Slider::TextBoxBelow, false, 50, 10, 0.0, 100.0, 1.0, &v1, volSlider.textBoxOutlineColourId, Colours::transparentWhite);
    Initialise::sliderOptions(this, &speedSlider, this, Slider::LinearVertical, Slider::TextBoxBelow, false, 50, 10, 0.01, 2.0, 0.1, &v1, speedSlider.textBoxOutlineColourId, Colours::transparentWhite);
    Initialise::sliderOptions(this, &loopSlider, this, Slider::IncDecButtons, Slider::TextBoxAbove, false, 50, 20, 0.0, 16.0, 1.0, &v1, loopSlider.textBoxOutlineColourId, Colours::transparentWhite);

    Initialise::labelOptions(this, &volume, "VOL", dontSendNotification, Justification::centred, 14.0f, label.textColourId, Colours::cyan);
    Initialise::labelOptions(this, &speed, "SPEED", dontSendNotification, Justification::centred, 14.0f, label.textColourId, Colours::fuchsia);
    Initialise::labelOptions(this, &loop, "Loop", dontSendNotification, Justification::centred, 16.0f, label.textColourId, Colours::cyan);
    Initialise::labelOptions(this, &hotCue, "HotCue", dontSendNotification, Justification::centred, 16.0f, label.textColourId, Colours::fuchsia);

    volume.attachToComponent(&volSlider, false);
    speed.attachToComponent(&speedSlider, false);
    loop.attachToComponent(&loopSlider, false);
    hotCue.attachToComponent(&hcBtn1, false);

    addAndMakeVisible(hcBtn1);
    addAndMakeVisible(hcBtn2);
    addAndMakeVisible(hcBtn3);
    addAndMakeVisible(hcBtn4);

    volSlider.setValue(50);
    speedSlider.setValue(1.0);

    volSlider.setTextValueSuffix("%");
    speedSlider.setTextValueSuffix(" x");
    loopSlider.setTextValueSuffix(" s");

     hcBtn1.addListener(this);
     hcBtn2.addListener(this);
     hcBtn3.addListener(this);
     hcBtn4.addListener(this);


    if (experienceLevel <= 2)
    {
        loopSlider.setTooltip("Select how many seconds from the \ncurrent position backwards to play repeatedly.");
        hcBtn1.setTooltip("Click to save the current position for easy callback.\n CTRL + click to cancel previously saved position.");
    }
}

DJPanel::~DJPanel()
{
}

void DJPanel::paint(Graphics& g)
{
    double rowH = getHeight() / 4;
    double rowW = getWidth() / 4;

    // Fill background.
    g.fillAll(Colour::fromRGBA(33, 0, 75, 255));

    g.setColour(Colours::white);
    g.setFont(16.0f);

    if (player->fileJustLoaded())
    {
        // Reset all controls.
        hcPos1 = -1.0;
        hcBtn1.setToggleState(false, NotificationType::dontSendNotification);
        hcPos2 = -1.0;
        hcBtn2.setToggleState(false, NotificationType::dontSendNotification);
        hcPos3 = -1.0;
        hcBtn3.setToggleState(false, NotificationType::dontSendNotification);
        hcPos4 = -1.0;
        hcBtn4.setToggleState(false, NotificationType::dontSendNotification);

        volSlider.setValue(50);
        speedSlider.setValue(1.0);
        loopSlider.setValue(0);

        experienceLevel++;

        if (experienceLevel >= 3)
        {
            // Remove tooltips.
            loopSlider.setTooltip("");
            hcBtn1.setTooltip("");

            // Reset loop tooltip to appear after 1 hour
            tooltipWindow->setMillisecondsBeforeTipAppears(3666666);
        }
    }

    repaint();
}

void DJPanel::resized()
{
    double rowH = getHeight() / 5;
    double colW = getWidth() / 8;
    double colH = getHeight() / 9;
    double sliderW = getWidth() / 3;
    double sliderH = getHeight() / 10;
    double buttonW = sliderW * 1.2;
    double buttonH = sliderH * 1.2;


    // Volume Slider
    volSlider.setNumDecimalPlacesToDisplay(0);
    volSlider.setBounds(colW, getHeight() / 15, sliderW, rowH * 1.8 );

    // Speed Slider
    speedSlider.setNumDecimalPlacesToDisplay(1);
    speedSlider.setBounds(colW * 4.5, getHeight() / 15, sliderW, rowH * 1.8);

    // Loop Slider
    loopSlider.setBounds(colW * 4.7, rowH * 3, buttonW, sliderH * 2.8);

    // Hot Cue Buttons
    hcBtn1.setBounds(colW, colH * 4.615, buttonW, buttonH);
    hcBtn1.setColour(TextButton::ColourIds::buttonOnColourId, Colour::fromRGB(201, 0, 255));
    hcBtn1.setColour(TextButton::ColourIds::textColourOnId, Colours::black);
    hcBtn1.setMouseCursor(MouseCursor::PointingHandCursor);

    hcBtn2.setBounds(colW, colH * 5.7, buttonW, buttonH);
    hcBtn2.setColour(TextButton::ColourIds::buttonOnColourId, Colour::fromRGB(1, 30, 254));
    hcBtn2.setColour(TextButton::ColourIds::textColourOnId, Colours::black);
    hcBtn2.setMouseCursor(MouseCursor::PointingHandCursor);

    hcBtn3.setBounds(colW, colH * 6.8, buttonW, buttonH);
    hcBtn3.setColour(TextButton::ColourIds::buttonOnColourId, Colour::fromRGB(201, 0, 255));
    hcBtn3.setColour(TextButton::ColourIds::textColourOnId, Colours::black);
    hcBtn3.setMouseCursor(MouseCursor::PointingHandCursor);

    hcBtn4.setBounds(colW, colH * 7.9, buttonW, buttonH);
    hcBtn4.setColour(TextButton::ColourIds::buttonOnColourId, Colour::fromRGB(1, 30, 254));
    hcBtn4.setColour(TextButton::ColourIds::textColourOnId, Colours::black);
    hcBtn4.setMouseCursor(MouseCursor::PointingHandCursor);
}

void DJPanel::sliderValueChanged(Slider* slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }

    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }

    if (slider == &loopSlider)
    {
        player->setLoop(slider->getValue());
    }
}

void DJPanel::buttonClicked(Button* button)
{
    if (button == &hcBtn1)
    {
        if (!isCommandDown())
        {
            if (hcPos1 == -1.0)
            {
                // Set cue
                hcPos1 = player->getPosInTrack();
                hcBtn1.setToggleState(true, NotificationType::dontSendNotification);
            }
            else
            {
                // Recall cue
                player->setPosition(hcPos1);
            }
        }
        else
        {
            // Reset when user press CTRL & click the button
            hcPos1 = -1.0;
            hcBtn1.setToggleState(false, NotificationType::dontSendNotification);
        }
    }

    if (button == &hcBtn2)
    {
        if (!isCommandDown())
        {
            if (hcPos2 == -1.0)
            {
                // Set cue
                hcPos2 = player->getPosInTrack();
                hcBtn2.setToggleState(true, NotificationType::dontSendNotification);
            }
            else
            {
                // Recall cue
                player->setPosition(hcPos2);
            }
        }
        else
        {
            // Reset when user press CTRL & click the button
            hcPos2 = -1.0;
            hcBtn2.setToggleState(false, NotificationType::dontSendNotification);
        }
    }

    if (button == &hcBtn3)
    {
        if (!isCommandDown())
        {
            if (hcPos3 == -1.0)
            {
                // Set cue
                hcPos3 = player->getPosInTrack();
                hcBtn3.setToggleState(true, NotificationType::dontSendNotification);
            }
            else
            {
                // Recall cue
                player->setPosition(hcPos3);
            }
        }
        else
        {
            // Reset when user press CTRL & click the button
            hcPos3 = -1.0;
            hcBtn3.setToggleState(false, NotificationType::dontSendNotification);
        }
    }

    if (button == &hcBtn4)
    {
        if (!isCommandDown())
        {
            if (hcPos4 == -1.0)
            {
                // Set cue
                hcPos4 = player->getPosInTrack();
                hcBtn4.setToggleState(true, NotificationType::dontSendNotification);
            }
            else
            {
                // Recall cue
                player->setPosition(hcPos4);
            }
        }
        else
        {
            // Reset when user press CTRL & click the button
            hcPos4 = -1.0;
            hcBtn4.setToggleState(false, NotificationType::dontSendNotification);
        }
    }
}

bool DJPanel::isCommandDown() const noexcept
{
    // Check if CTRL key is pressed
    if (currentModifiers == ModifierKeys::Flags::commandModifier)
    {
        return true;
    }

    return false;
}