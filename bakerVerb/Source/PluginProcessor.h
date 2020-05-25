/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class BakerVerbAudioProcessor  : public AudioProcessor
{
public:


    //==============================================================================
    BakerVerbAudioProcessor();
    ~BakerVerbAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	void setWet(float value);
	void setDry(float value);
	void setRoomSize(float value);
	void setDamping(float value);
	void setWidth(float value);

	void openFile();
	void playFile();
	void stopFile();
	void readFile(File file);

	void setPitch(float value);

private:

	//reverb
	Reverb bakerVerb;
	Reverb::Parameters bakerVerbParameters;

	//buffer for data to be input
	AudioSampleBuffer soundFile;

	//position to play from
	float position;

	//state check
	bool isPlaying;

	//playback speed variable
	float playbackSpeed;

public:

	//saving and loading
	AudioProcessorValueTreeState parameters;

	//format manager to register usable formats
	AudioFormatManager formatManager;

	//thumbnail
	AudioThumbnailCache fileWaveCache;
	AudioThumbnail fileWave;

	bool fileIsAdded = false;

	File audioFile;
	File txtFile;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BakerVerbAudioProcessor)
};
