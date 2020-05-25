/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BakerVerbAudioProcessorEditor::BakerVerbAudioProcessorEditor (BakerVerbAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (315, 360);

	wetLevelSlider.onValueChange = [this]()
	{
		processor.setWet(wetLevelSlider.getValue());
	};

    dryLevelSlider.onValueChange = [this]()
	{
		processor.setDry(dryLevelSlider.getValue());
	};

	roomSizeSlider.onValueChange = [this]()
	{
		processor.setRoomSize(roomSizeSlider.getValue());
	};

	dampingSlider.onValueChange = [this]()
	{
		processor.setDamping(dampingSlider.getValue());
	};

	widthSlider.onValueChange = [this]()
	{
		processor.setWidth(widthSlider.getValue());
	};

	pitchSlider.onValueChange = [this]()
	{
		processor.setPitch(pitchSlider.getValue());
	};

	



	//dry slider
	dryLevelValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(p.parameters, "DRY_ID", dryLevelSlider);
	dryLevelSlider.setSliderStyle(Slider::LinearBarVertical);
	dryLevelSlider.setLookAndFeel(&myLook);
	dryLevelSlider.setRange(0.0, 1.0, 0.1);
	dryLevelSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	dryLevelSlider.setPopupDisplayEnabled(true, false, this);
	dryLevelSlider.setTextValueSuffix(" Dry Level");
	addAndMakeVisible(&dryLevelSlider);
	dryLabel.setFont(Font(13.0f));
	dryLabel.setColour(Label::textColourId, Colours::black);
	dryLabel.setJustificationType(Justification::centred);
	dryLabel.setText("Dry", dontSendNotification);
	addAndMakeVisible(&dryLabel);

	//wet slider
	wetLevelValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(p.parameters, "WET_ID", wetLevelSlider);
	wetLevelSlider.setSliderStyle(Slider::LinearBarVertical);
	wetLevelSlider.setLookAndFeel(&myLook);
	wetLevelSlider.setRange(0.0, 1.0, 0.1);
	wetLevelSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	wetLevelSlider.setPopupDisplayEnabled(true, false, this);
	wetLevelSlider.setTextValueSuffix(" Wet Level");
	addAndMakeVisible(&wetLevelSlider);
	wetLabel.setFont(Font(13.0f));
	wetLabel.setColour(Label::textColourId, Colours::black);
	wetLabel.setJustificationType(Justification::centred);
	wetLabel.setText("Wet", dontSendNotification);
	addAndMakeVisible(&wetLabel);

	//room size slider
	roomSizeValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(p.parameters, "ROOM_SIZE_ID", roomSizeSlider);
	roomSizeSlider.setSliderStyle(Slider::LinearBarVertical);
	roomSizeSlider.setLookAndFeel(&myLook);
	roomSizeSlider.setRange(0.0, 1.0, 0.1);
	roomSizeSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	roomSizeSlider.setPopupDisplayEnabled(true, false, this);
	roomSizeSlider.setTextValueSuffix(" Room Size");
	addAndMakeVisible(&roomSizeSlider);
	roomSize.setFont(Font(13.0f));
	roomSize.setColour(Label::textColourId, Colours::black);
	roomSize.setJustificationType(Justification::centred);
	roomSize.setText("Size", dontSendNotification);
	addAndMakeVisible(&roomSize);

	//damping slider
	dampingValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(p.parameters, "DAMPING_ID", dampingSlider);
	dampingSlider.setSliderStyle(Slider::LinearBarVertical);
	dampingSlider.setLookAndFeel(&myLook);
	dampingSlider.setRange(0.0, 1.0, 0.1);
	dampingSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	dampingSlider.setPopupDisplayEnabled(true, false, this);
	dampingSlider.setTextValueSuffix(" Damping");
	addAndMakeVisible(&dampingSlider);
	dampingLabel.setFont(Font(13.0f));
	dampingLabel.setColour(Label::textColourId, Colours::black);
	dampingLabel.setJustificationType(Justification::centred);
	dampingLabel.setText("Damp", dontSendNotification);
	addAndMakeVisible(&dampingLabel);


	//width slider
	widthValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(p.parameters, "WIDTH_ID", widthSlider);
	widthSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	widthSlider.setLookAndFeel(&myLook);
	widthSlider.setRange(0.0, 1.0, 0.1);
	widthSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	widthSlider.setPopupDisplayEnabled(true, false, this);
	widthSlider.setTextValueSuffix(" Width");
	addAndMakeVisible(&widthSlider);
	widthLabel.setFont(Font(13.0f));
	widthLabel.setColour(Label::textColourId, Colours::black);
	widthLabel.setJustificationType(Justification::centred);
	widthLabel.setText("Width", dontSendNotification);
	addAndMakeVisible(&widthLabel);

	//Audio Player

	//open
	addAndMakeVisible(&openButton);
	openButton.setButtonText("Open...");
	openButton.onClick = [this] { processor.openFile(); };

	//play
	addAndMakeVisible(&playButton);
	playButton.setButtonText("Play");
	playButton.onClick = [this] { processor.playFile(); };
	playButton.setColour(TextButton::buttonColourId, Colours::green);

	//stop
	addAndMakeVisible(&stopButton);
	stopButton.setButtonText("Stop");
	stopButton.onClick = [this] { processor.stopFile(); };
	stopButton.setColour(TextButton::buttonColourId, Colours::red);

	//pitch slider
	pitchValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(p.parameters, "PITCH_ID", pitchSlider);
	addAndMakeVisible(&pitchSlider);
	pitchSlider.setSliderStyle(Slider::LinearBar);
	pitchSlider.setLookAndFeel(&myLook);
	pitchSlider.setRange(-2.0f, 2.0f, 0.1f);
	pitchSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	pitchSlider.setPopupDisplayEnabled(true, false, this);
	pitchSlider.setTextValueSuffix(" Pitch");
	playbackLabel.setFont(Font(13.0f));
	playbackLabel.setColour(Label::textColourId, Colours::black);
	playbackLabel.setJustificationType(Justification::centred);
	playbackLabel.setText("Playback Speed", dontSendNotification);
	addAndMakeVisible(&playbackLabel);
	
}

BakerVerbAudioProcessorEditor::~BakerVerbAudioProcessorEditor()
{
}

//==============================================================================
void BakerVerbAudioProcessorEditor::paint (Graphics& g)
{
	g.fillAll(Colours::black);

	g.setColour(Colours::black);

	g.setFont(30.0f);

	g.setColour(Colours::white);
	g.drawRect(6, 6, 90, 120, 2);
	g.fillRect(6, 6, 90, 120);
	g.setColour(Colours::white);
	g.drawRect(6, 130, 300, 220, 2);
	g.fillRect(6, 130, 300, 220);
	

	Rectangle<int> thumbnailBounds(100, 6, 206, 120);
	if (processor.fileWave.getNumChannels() == 0)
		paintIfNoFileLoaded(g, thumbnailBounds);
	else
		paintIfFileLoaded(g, thumbnailBounds);

	g.drawFittedText("BakerVerb", 0, 300, getWidth(), 30, Justification::centred, 1);




}

void BakerVerbAudioProcessorEditor::resized()
{
	//Audio Player
	openButton.setBounds(10, 10, 80, 25);
	playButton.setBounds(10, 40, 80, 25);
	stopButton.setBounds(10, 70, 80, 25);
	pitchSlider.setBounds(10, 97, 80, 15);
	playbackLabel.setBounds(6, 113, 90, 10);





	//reverb
	int areaMoveY = 110;
	int areaMoveX = 0;

	dryLevelSlider.setBounds(230 + areaMoveX, 30 + areaMoveY, 20, 180);
	dryLabel.setBounds(220 + areaMoveX, 220 + areaMoveY, 40, 10);
	wetLevelSlider.setBounds(270 + areaMoveX, 30 + areaMoveY, 20, 180);
	wetLabel.setBounds(260 + areaMoveX, 220 + areaMoveY, 40, 10);
	roomSizeSlider.setBounds(60 + areaMoveX, 30 + areaMoveY, 20, 180);
	roomSize.setBounds(50 + areaMoveX, 220 + areaMoveY, 40, 10);
	dampingSlider.setBounds(20 + areaMoveX, 30 + areaMoveY, 20, 180);
	dampingLabel.setBounds(areaMoveX, 220 + areaMoveY, 60, 10);
	widthSlider.setBounds(100 + areaMoveX, 80 + areaMoveY, 100, 100);
	widthLabel.setBounds(130 + areaMoveX, 70 + areaMoveY, 40, 10);
}

void BakerVerbAudioProcessorEditor::paintIfNoFileLoaded(Graphics& g, const Rectangle<int>& thumbnailBounds)
{
	g.setColour(Colours::white);
	g.fillRect(thumbnailBounds);
	g.setColour(Colours::black);
	g.drawFittedText("No File Loaded", thumbnailBounds, Justification::centred, 1.0f);
}


void BakerVerbAudioProcessorEditor::paintIfFileLoaded(Graphics& g, const Rectangle<int>& thumbnailBounds)
{
	if (processor.fileIsAdded == true)
	{
		repaint();
	}
	g.setColour(Colours::white);
	g.fillRect(thumbnailBounds);
	g.setColour(Colours::black);
	processor.fileWave.drawChannels(g, thumbnailBounds, 0.0, processor.fileWave.getTotalLength(), 1.0f);
}
