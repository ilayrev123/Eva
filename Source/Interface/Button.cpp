#include "Button.h"
#include <iostream>
#include <chrono>
#include <thread>

void analyse(juce::TextButton& button) {
    // Change the state of the button when it's clicked.
    button.setButtonText("Analysing...");
    button.repaint();
    bool analysing = true;
    while (analysing) {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        analysing = false;
    }
    button.setButtonText("Analyse");
    button.repaint();
};
