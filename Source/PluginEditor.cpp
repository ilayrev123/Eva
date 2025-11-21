#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Interface/Button.h"
#include <chrono>
#include <thread>

constexpr int WIDTH = 400;
constexpr int HEIGHT = 400;

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    initialiseGUI();
}

void AudioPluginAudioProcessorEditor::initialiseGUI() {
    start_button.setButtonText("Analyse");
    start_button.onClick = [this] { analyse(start_button); };
    addAndMakeVisible(start_button);

    // Must be set before constructor is finished.
    setSize(WIDTH, HEIGHT);
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
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    int button_x_pos = 10;
    int button_y_pos = 10;
    int button_width = 100;
    int button_height = 50;
    start_button.setBounds(button_x_pos, button_y_pos, button_width, button_height);
}
