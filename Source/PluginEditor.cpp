#include "PluginProcessor.h"
#include "PluginEditor.h"

constexpr int WIDTH = 400;
constexpr int HEIGHT = 300;

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (WIDTH, HEIGHT);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& window)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    window.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    window.setColour (juce::Colours::black);
    window.setFont (30.0f);
    window.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);

    window.drawFittedText("TEST", getLocalBounds(), juce::Justification::centred, 2);

}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto x_pos = 10;
    auto y_pos = 10;
    auto width = 100;
    auto height = 50;
}
