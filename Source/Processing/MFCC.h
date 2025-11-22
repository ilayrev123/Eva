#pragma once
#include <vector>
#include <cmath>
#include <juce_dsp/juce_dsp.h>

class MFCC
{
public:
	MFCC(int sampleRate, int fftSize, int numFilters, int numCoeffs);

	std::vector<float> processFrame(const float* frame);

private:
	void computeMelFilterBank();

    int sampleRate;
    int fftSize;
    int numFilters;
    int numCoeffs;

    juce::dsp::FFT fft;
    std::vector<float> window;
    std::vector<std::vector<float>> filterbank;
    std::vector<float> fftBuffer;
};
