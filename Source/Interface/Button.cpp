#include "Button.h"
#include <iostream>
#include <chrono>
#include <thread>

void sleepFunc();

void sleepFunc() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void analyze(juce::TextButton& button) {
    // Change the state of the button when it's clicked.
    button.setButtonText("Analysing...");
    button.setEnabled(false);
    button.repaint();
    
    std::thread t1(sleepFunc);
    t1.detach();

    button.setButtonText("Analyse");
    button.setEnabled(true);
    button.repaint();
};
