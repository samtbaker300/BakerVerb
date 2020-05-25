/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>
#include <fstream>
#include <sstream>

//==============================================================================
BakerVerbAudioProcessor::BakerVerbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
	 ), parameters(*this, nullptr, "PARAMETERS", { std::make_unique<AudioParameterFloat>("DRY_ID", "DRY", 0.0f, 1.0f, 1.0f),
												   std::make_unique<AudioParameterFloat>("WET_ID", "WET", 0.0f, 1.0f, 0.0f),
												   std::make_unique<AudioParameterFloat>("ROOM_SIZE_ID", "ROOM_SIZE", 0.0f, 1.0f, 0.0f),
												   std::make_unique<AudioParameterFloat>("DAMPING_ID", "DAMPING", 0.0f, 1.0f, 0.0f),
												   std::make_unique<AudioParameterFloat>("WIDTH_ID", "WIDTH", 0.0f, 1.0f, 0.0f),
												   std::make_unique<AudioParameterFloat>("PITCH_ID", "PITCH", -2.0f, 2.0f, 1.0f)}),
	
		fileWaveCache(5), fileWave(512, formatManager, fileWaveCache)
#endif

{

	

	//register formats
	formatManager.registerBasicFormats();

	//set position
	position = 0;

	//state
	isPlaying = false;

	//playback speed default
	playbackSpeed = 1.0f;
}

BakerVerbAudioProcessor::~BakerVerbAudioProcessor()
{



}

//==============================================================================
const String BakerVerbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BakerVerbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BakerVerbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BakerVerbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BakerVerbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BakerVerbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BakerVerbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BakerVerbAudioProcessor::setCurrentProgram (int index)
{
}

const String BakerVerbAudioProcessor::getProgramName (int index)
{
    return {};
}

void BakerVerbAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void BakerVerbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	bakerVerb.setSampleRate(sampleRate);
}

void BakerVerbAudioProcessor::releaseResources()
{
	
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BakerVerbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BakerVerbAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	const int totalNumInputChannels = getTotalNumInputChannels();
	const int totalNumOutputChannels = getTotalNumOutputChannels();

	for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	//create pointer to direct to memory for mono and stereo
	float* leftChannel = buffer.getWritePointer(0);
	//only use if stereo
	float* rightChannel = buffer.getWritePointer(1);

	if (soundFile.getNumSamples() > 0 && isPlaying == true)
	{
		for (int i = 0; i < buffer.getNumSamples(); ++i)
		{
			//place filled buffer into pointer to memory
			leftChannel[i] += soundFile.getSample(0, position);
			rightChannel[i] += soundFile.getSample(1, position);
			//set the read speed of the position
			position += playbackSpeed;

			// if the position becomes more than the sound file it resets it back to 0
			if (position > soundFile.getNumSamples())
			{
				position = 0;
				isPlaying = false;
			}

			// if the position becomes less than zero put the position at the end of the sound file so it can play in reverse
			if (position < 0)
			{
				position = soundFile.getNumSamples();
				isPlaying = false;
			}
		}
	}
	// This is the place where you'd normally do the guts of your plugin's 
	// audio processing...

	const auto numChannels = jmin(totalNumInputChannels, totalNumOutputChannels);

	if (numChannels == 1)
		bakerVerb.processMono(buffer.getWritePointer(0), buffer.getNumSamples());

	else if (numChannels == 2)
		bakerVerb.processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), buffer.getNumSamples());


}


//==============================================================================
bool BakerVerbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* BakerVerbAudioProcessor::createEditor()
{
    return new BakerVerbAudioProcessorEditor (*this);
}

//==============================================================================
void BakerVerbAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

	auto state = parameters.copyState();
	std::unique_ptr<XmlElement> xml(state.createXml());
	copyXmlToBinary(*xml, destData);

	std::ofstream outfile("cachedfile.txt");
	outfile << audioFile.getFullPathName() << std::endl;
	outfile.close();

}

void BakerVerbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

	std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState.get() != nullptr)
		if (xmlState->hasTagName(parameters.state.getType()))
			parameters.replaceState(ValueTree::fromXml(*xmlState));

	std::ifstream infile("cachedfile.txt");
	if (!infile.fail())
	{
		std::string filePath;

		while (std::getline(infile, filePath))
		{
			audioFile = filePath;
		}

		readFile(audioFile);
	}




}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BakerVerbAudioProcessor();
}

void BakerVerbAudioProcessor::setWet(float value)
{
	bakerVerbParameters.wetLevel = value;
	bakerVerb.setParameters(bakerVerbParameters);
}

void BakerVerbAudioProcessor::setDry(float value)
{
	bakerVerbParameters.dryLevel = value;
	bakerVerb.setParameters(bakerVerbParameters);
}

void BakerVerbAudioProcessor::setRoomSize(float value)
{
	bakerVerbParameters.roomSize = value;
	bakerVerb.setParameters(bakerVerbParameters);

}

void BakerVerbAudioProcessor::setDamping(float value)
{
	bakerVerbParameters.damping = value;
	bakerVerb.setParameters(bakerVerbParameters);

}

void BakerVerbAudioProcessor::setWidth(float value)
{
	bakerVerbParameters.width = value;
	bakerVerb.setParameters(bakerVerbParameters);
}

void BakerVerbAudioProcessor::setPitch(float value)
{
	playbackSpeed = value;
	

}

void BakerVerbAudioProcessor::openFile()
{

	//opens directory for file to be selected
	FileChooser chooseFile("Please select a audio file you wish to play...", File(), "*.wav");
	if (chooseFile.browseForFileToOpen())
	{
		//get result of file and create reader to read file
		audioFile = chooseFile.getResult();
		readFile(audioFile);
		
	}
	

}

void BakerVerbAudioProcessor::playFile()
{
	isPlaying = true;
}

void BakerVerbAudioProcessor::stopFile()
{
	isPlaying = false;
	position = 0;
}

void BakerVerbAudioProcessor::readFile(File file)
{
	std::unique_ptr<AudioFormatReader> reader(formatManager.createReaderFor(file));
	//put data from file into buffer
	if (reader.get() != nullptr)
	{
		soundFile.setSize(reader->numChannels, (int)reader->lengthInSamples, false, true, false);
		reader->read(&soundFile, 0, (int)reader->lengthInSamples, 0, true, true);
		fileWave.setSource(new FileInputSource(file));
		fileIsAdded = true;

	}
}