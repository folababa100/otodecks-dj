#include <JuceHeader.h>
#include "StereoReverbGUI.h"
#include "Initialise.h"

//==============================================================================
StereoReverbGUI::StereoReverbGUI(StereoReverb* _stereoReverb) : stereoReverb(_stereoReverb)
{
    // Sliders
    Initialise::sliderOptions(this, &roomSizeSlider, this, Slider::LinearVertical, Slider::TextBoxBelow, false, 50, 10, 0.0, 1.0, 0.01, &v1, roomSizeSlider.textBoxOutlineColourId, Colours::transparentWhite);
    Initialise::sliderOptions(this, &dampingSlider, this, Slider::LinearVertical, Slider::TextBoxBelow, false, 50, 10, 0.0, 1.0, 0.01, &v1, dampingSlider.textBoxOutlineColourId, Colours::transparentWhite);
    Initialise::sliderOptions(this, &wetLevelSlider, this, Slider::LinearVertical, Slider::TextBoxBelow, false, 50, 10, 0.0, 1.0, 0.01, &v1, wetLevelSlider.textBoxOutlineColourId, Colours::transparentWhite);
    Initialise::sliderOptions(this, &dryLevelSlider, this, Slider::LinearVertical, Slider::TextBoxBelow, false, 50, 10, 0.0, 1.0, 0.01, &v1, dryLevelSlider.textBoxOutlineColourId, Colours::transparentWhite);
    Initialise::sliderOptions(this, &widthSlider, this, Slider::LinearVertical, Slider::TextBoxBelow, false, 50, 10, 0.0, 1.0, 0.01, &v1, widthSlider.textBoxOutlineColourId, Colours::transparentWhite);
    Initialise::sliderOptions(this, &freezeModeSlider, this, Slider::LinearVertical, Slider::TextBoxBelow, false, 50, 10, 0.0, 1.0, 0.01, &v1, freezeModeSlider.textBoxOutlineColourId, Colours::transparentWhite);

    // Labels
    Initialise::labelOptions(this, &label, "Stereo Reverb", dontSendNotification, Justification::centred, 14.0f, label.textColourId, Colour::fromRGBA(11, 24, 98, 255));
    Initialise::labelOptions(this, &roomSize, "RS", dontSendNotification, Justification::centred, 14.0f, label.textColourId, Colour::fromRGBA(79, 0, 16, 255));
    Initialise::labelOptions(this, &damping, "DMP", dontSendNotification, Justification::centred, 14.0f, label.textColourId, Colour::fromRGBA(11, 24, 98, 255));
    Initialise::labelOptions(this, &wetLevel, "WL", dontSendNotification, Justification::centred, 14.0f, label.textColourId, Colour::fromRGBA(79, 0, 16, 255));
    Initialise::labelOptions(this, &dryLevel, "DL", dontSendNotification, Justification::centred, 14.0f, label.textColourId, Colour::fromRGBA(11, 24, 98, 255));
    Initialise::labelOptions(this, &width, "W", dontSendNotification, Justification::centred, 14.0f, label.textColourId, Colour::fromRGBA(79, 0, 16, 255));
    Initialise::labelOptions(this, &freezeMode, "FM", dontSendNotification, Justification::centred, 14.0f, label.textColourId, Colour::fromRGBA(11, 24, 98, 255));

    // Slider labels
    roomSize.attachToComponent(&roomSizeSlider, false);
    damping.attachToComponent(&dampingSlider, false);
    wetLevel.attachToComponent(&wetLevelSlider, false);
    dryLevel.attachToComponent(&dryLevelSlider, false);
    width.attachToComponent(&widthSlider, false);
    freezeMode.attachToComponent(&freezeModeSlider, false);

    // Info button
    auto infoImage = ImageCache::getFromMemory(BinaryData::info_png, BinaryData::info_pngSize);
    infoBtn.setImages(true, true, true, infoImage, 1, Colours::mediumpurple, Image(nullptr), 1, Colour::fromRGBA(11, 24, 98, 255), Image(nullptr), 1, Colours::transparentBlack);
    addAndMakeVisible(infoBtn);
    infoBtn.setTooltip("R: Room Size, DMP: Damping, WL: Wet Level, DL: Dry Level, W: Width, FM: Freeze Mode");
}

StereoReverbGUI::~StereoReverbGUI()
{
    // Remove sliders lookandfeel
    roomSizeSlider.setLookAndFeel(nullptr);
    dampingSlider.setLookAndFeel(nullptr);
    wetLevelSlider.setLookAndFeel(nullptr);
    dryLevelSlider.setLookAndFeel(nullptr);
    widthSlider.setLookAndFeel(nullptr);
    freezeModeSlider.setLookAndFeel(nullptr);
}

void StereoReverbGUI::paint(Graphics& g)
{
    // Fill background
    g.fillAll(Colour::fromRGBA(255, 183, 197, 255));
    // Outline component
    g.setColour(Colour::fromRGBA(255, 183, 197, 255));
    g.drawRect(getLocalBounds(), 1);
    // Outline on header
    g.setColour(Colours::mediumpurple);
    g.drawRect(label.getBounds());

    // Placeholder text
    g.setColour(Colours::white);
    g.setFont(14.0f);
    g.drawText("", getLocalBounds(), Justification::centred, true);
}

void StereoReverbGUI::resized()
{
    double w = getWidth() / 6;
    double h = getHeight() * 0.2;
    double h2 = getHeight() * 0.3;

    // Sliders
    roomSizeSlider.setBounds(0, h, w, h * 3.25);
    dampingSlider.setBounds(w, h2, w, h * 3.25);
    wetLevelSlider.setBounds(w * 2, h, w, h * 3.25);
    dryLevelSlider.setBounds(w * 3, h2, w, h * 3.25);
    widthSlider.setBounds(w * 4, h, w, h * 3.25);
    freezeModeSlider.setBounds(w * 5, h2, w, h * 3.25);

    // Label
    label.setBounds(0, 0, getWidth(), getHeight() * 0.11);

    // Info button
    infoBtn.setBounds(w * 5.5, getHeight() * 0.02, w * 0.5, getHeight() * 0.06);
}

// Value of parameters of sliders
void StereoReverbGUI::sliderValueChanged(Slider* slider)
{
    if (slider == &roomSizeSlider)
    {
        stereoReverb->parameters.roomSize = slider->getValue();
        stereoReverb->setBypass();
    }

    if (slider == &dampingSlider)
    {
        stereoReverb->parameters.damping = slider->getValue();
        stereoReverb->setBypass();
    }

    if (slider == &wetLevelSlider)
    {
        stereoReverb->parameters.wetLevel = slider->getValue();
        stereoReverb->setBypass();
    }

    if (slider == &dryLevelSlider)
    {
        stereoReverb->parameters.dryLevel = slider->getValue();
        stereoReverb->setBypass();
    }

    if (slider == &widthSlider)
    {
        stereoReverb->parameters.width = slider->getValue();
        stereoReverb->setBypass();
    }

    if (slider == &freezeModeSlider)
    {
        stereoReverb->parameters.freezeMode = slider->getValue();
        stereoReverb->setBypass();
    }
};