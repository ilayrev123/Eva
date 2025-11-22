#define _USE_MATH_DEFINES
#include "MFCC.h"
#include <math.h>

// Convert Hz to Mel
static float hz2mel(float hz)
{
    return 2595.0f * std::log10(1.0f + hz / 700.0f);
}

// Convert Mel to Hz
static float mel2hz(float mel)
{
    return 700.0f * (std::pow(10.0f, mel / 2595.0f) - 1.0f);
}

MFCC::MFCC(int sampleRate, int fftSize, int numFilters, int numCoeffs)
    :   sampleRate(sampleRate), fftSize(fftSize),
        numFilters(numFilters), numCoeffs(numCoeffs),
        fft((int)(std::log2(fftSize))),
        fftBuffer(2 * fftSize, 0.0f)
{
    window.resize(fftSize);
    for (int i = 0; i < fftSize; i++) {
        window[i] = 0.5f - 0.5f * std::cos(2.0f * M_PI * i / (fftSize - 1));
    }

    computeMelFilterBank();
}

void MFCC::computeMelFilterBank()
{
    int numFFTBins = fftSize / 2 + 1;

    float melLow = hz2mel(0);
    float melHigh = hz2mel(sampleRate / 2);
    float melStep = (melHigh - melLow) / (numFilters + 1);

    std::vector<float> melPoints(numFilters + 2);
    std::vector<int> bin(numFilters + 2);
    for (int i = 0; i < melPoints.size(); i++) {
        melPoints[i] = melLow + i * melStep;
        float hz = mel2hz(melPoints[i]);
        bin[i] = (int)std::floor((fftSize + 1) * hz / sampleRate);
    }

    filterbank.resize(numFilters, std::vector<float>(numFFTBins));

    for (int m = 1; m <= numFilters; m++) {
        for (int k = 0; k < numFFTBins; k++) {
            float w = 0.0f;
            if (k >= bin[m - 1] && k <= bin[m]) {
                w = (float)(k - bin[m - 1]) / (bin[m] - bin[m - 1]);
            }
            else if(k >= bin[m] && k <= bin[m + 1]) {
                w = (float)(bin[m + 1] - k) / (bin[m + 1] - bin[m]);
            }

            filterbank[m - 1][k] = w;
        }
    }
}

std::vector<float> MFCC::processFrame(const float* frame)
{
    // 1. Apply window
    for (int i = 0; i < fftSize; i++)
        fftBuffer[i] = frame[i] * window[i];

    // Zero imaginary part
    std::fill(fftBuffer.begin() + fftSize, fftBuffer.end(), 0.0f);

    // 2. FFT
    fft.performRealOnlyForwardTransform(fftBuffer.data());

    // 3. Compute magnitude spectrum
    int numFFTbins = fftSize / 2 + 1;
    std::vector<float> mag(numFFTbins);

    mag[0] = std::abs(fftBuffer[0]);
    for (int i = 1; i < numFFTbins - 1; i++)
        mag[i] = std::sqrt(fftBuffer[2 * i] * fftBuffer[2 * i] +
            fftBuffer[2 * i + 1] * fftBuffer[2 * i + 1]);
    mag[numFFTbins - 1] = std::abs(fftBuffer[1]);

    // 4. Apply Mel filterbank
    std::vector<float> melEnergies(numFilters, 0.0f);
    for (int m = 0; m < numFilters; m++)
        for (int k = 0; k < numFFTbins; k++)
            melEnergies[m] += mag[k] * filterbank[m][k];

    // Avoid log(0)
    for (auto& e : melEnergies)
        e = std::log(std::max(e, 1e-8f));

    // 5. DCT-II -> MFCC
    std::vector<float> mfcc(numCoeffs, 0.0f);

    for (int k = 0; k < numCoeffs; k++)
    {
        for (int n = 0; n < numFilters; n++)
            mfcc[k] += melEnergies[n] *
            std::cos(M_PI * k * (n + 0.5f) / numFilters);
    }
    return mfcc;
}
