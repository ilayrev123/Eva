#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <chrono>
#include <thread>

constexpr int WIDTH = 400;
constexpr int HEIGHT = 400;

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);

    start_button.setButtonText("Analyse");
    start_button.onClick = [this]()
        {
            // Change the state of the button when it's clicked.
            start_button.setButtonText("Analysing...");
            start_button.repaint();
            bool analysing = true;
            while (analysing) {
                std::this_thread::sleep_for(std::chrono::seconds(3));
                analysing = false;
            }
            start_button.setButtonText("Analyse");
            start_button.repaint();
        };
    addAndMakeVisible(start_button);
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
