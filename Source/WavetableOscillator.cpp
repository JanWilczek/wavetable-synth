#include <cmath>
#include "JuceHeader.h"
#include "WavetableOscillator.h"

WavetableOscillator::WavetableOscillator(std::vector<float> waveTable, double sampleRate)
: waveTable{ std::move(waveTable) },
	sampleRate{ sampleRate }
{}

float WavetableOscillator::getSample()
{
	jassert(isPlaying());
	index += indexIncrement;
	index = std::fmod(index, static_cast<float>(waveTable.size()));
	const auto truncatedIndex = static_cast<int>(index);
	return waveTable[truncatedIndex];
}

void WavetableOscillator::setFrequency(float frequency)
{
	indexIncrement = frequency * static_cast<float>(waveTable.size()) / static_cast<float>(sampleRate);
}

void WavetableOscillator::stop()
{
	index = 0.f;
	indexIncrement = 0.f;
}

bool WavetableOscillator::isPlaying() const
{
	return indexIncrement != 0.f;
}


