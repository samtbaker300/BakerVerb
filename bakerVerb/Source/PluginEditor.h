/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class CustomLook : public LookAndFeel_V4
{
public:
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
	{
		auto radius = jmin(width / 2, height / 2) - 4.0f;
		auto centreX = x + width * 0.5f;
		auto centreY = y + height * 0.5f;
		auto rx = centreX - radius;
		auto ry = centreY - radius;
		auto rw = radius * 2.0f;
		auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

		// fill
		g.setColour(Colours::black);
		g.fillEllipse(rx, ry, rw, rw);

		// outline
		g.setColour(Colours::black);
		g.drawEllipse(rx, ry, rw, rw, 1.0f);

		Path p;
		auto pointerLength = radius * 0.5f;
		auto pointerThickness = 5.0f;
		p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
		p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));

		// pointer
		g.setColour(Colours::white);
		g.fillPath(p);
	}
	CustomLook()
	{

		setColour(Slider::trackColourId, Colours::black);

	}
};

class BakerVerbAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    BakerVerbAudioProcessorEditor (BakerVerbAudioProcessor&);
    ~BakerVerbAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	void paintIfNoFileLoaded(Graphics& g, const Rectangle<int>& thumbnailBounds);
	void paintIfFileLoaded(Graphics& g, const Rectangle<int>& thumbnailBounds);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BakerVerbAudioProcessor& processor;

	//Reverb
	Slider dryLevelSlider;
	Slider wetLevelSlider;
	Slider roomSizeSlider;
	Slider dampingSlider;
	Slider widthSlider;
	Label widthLabel;
	Label dampingLabel;
	Label wetLabel;
	Label dryLabel;
	Label roomSize;

	//Audio Player
	TextButton openButton;
	TextButton stopButton;
	TextButton playButton;
	Slider pitchSlider;
	Label playbackLabel;


	//lookandfeel
	CustomLook myLook;

public:


	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> dryLevelValue;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> wetLevelValue;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> roomSizeValue;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> dampingValue;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> widthValue;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> pitchValue;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BakerVerbAudioProcessorEditor)
};
