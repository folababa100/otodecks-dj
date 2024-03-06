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

    Initialise::labelOptions(this, &volume, "VOL", dontSendNotification, Justification::centred, 14.0f, label.textColourId, Colour::fromRGBA(11, 24, 98, 255));
    Initialise::labelOptions(this, &speed, "SPEED", dontSendNotification, Justification::centred, 14.0f, label.textColourId, Colour::fromRGBA(79, 0, 16, 255));
    Initialise::labelOptions(this, &loop, "Loop", dontSendNotification, Justification::centred, 16.0f, label.textColourId, Colour::fromRGBA(11, 24, 98, 255));
    Initialise::labelOptions(this, &hotCue, "HotCue", dontSendNotification, Justification::centred, 16.0f, label.textColourId, Colour::fromRGBA(79, 0, 16, 255));

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
    g.fillAll(Colour::fromRGBA(255, 183, 197, 255));

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
    const double rowH = getHeight() / 5;
    const double colW = getWidth() / 8;
    const double colH = getHeight() / 9;
    const double sliderW = getWidth() / 3;
    const double sliderH = getHeight() / 10;
    const double buttonW = sliderW * 1.2;
    const double buttonH = sliderH * 1.2;

    const Colour buttonOnColour1 = Colour::fromRGB(102, 157, 246);
    const Colour buttonOnColour2 = Colour::fromRGB(1, 30, 254);

    // Volume Slider
    volSlider.setNumDecimalPlacesToDisplay(0);
    volSlider.setBounds(colW, getHeight() / 15, sliderW, rowH * 1.8 );

    // Speed Slider
    speedSlider.setNumDecimalPlacesToDisplay(1);
    speedSlider.setBounds(colW * 4.5, getHeight() / 15, sliderW, rowH * 1.8);

    // Loop Slider
    loopSlider.setBounds(colW * 4.7, rowH * 3, buttonW, sliderH * 2.8);

    // Hot Cue Buttons
    setButtonProperties(hcBtn1, colW, colH * 4.615, buttonW, buttonH, buttonOnColour1);
    setButtonProperties(hcBtn2, colW, colH * 5.7, buttonW, buttonH, buttonOnColour2);
    setButtonProperties(hcBtn3, colW, colH * 6.8, buttonW, buttonH, buttonOnColour1);
    setButtonProperties(hcBtn4, colW, colH * 7.9, buttonW, buttonH, buttonOnColour2);
}

void DJPanel::setButtonProperties(TextButton& button, double x, double y, double width, double height, Colour colour)
{
    button.setBounds(x, y, width, height);
    button.setColour(TextButton::ColourIds::buttonOnColourId, colour);
    button.setColour(TextButton::ColourIds::textColourOnId, Colours::black);
    button.setMouseCursor(MouseCursor::PointingHandCursor);
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

void DJPanel::handleButtonClick(Button* button, double& hcPos)
{
    if (!isCommandDown())
    {
        if (hcPos == -1.0)
        {
            // Set cue
            hcPos = player->getPosInTrack();
            button->setToggleState(true, NotificationType::dontSendNotification);
        }
        else
        {
            // Recall cue
            player->setPosition(hcPos);
        }
    }
    else
    {
        // Reset when user press CTRL & click the button
        hcPos = -1.0;
        button->setToggleState(false, NotificationType::dontSendNotification);
    }
}

void DJPanel::buttonClicked(Button* button)
{
    if (button == &hcBtn1)
    {
        handleButtonClick(button, hcPos1);
    }
    else if (button == &hcBtn2)
    {
        handleButtonClick(button, hcPos2);
    }
    else if (button == &hcBtn3)
    {
        handleButtonClick(button, hcPos3);
    }
    else if (button == &hcBtn4)
    {
        handleButtonClick(button, hcPos4);
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