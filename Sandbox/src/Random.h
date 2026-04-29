#pragma once

#include <random>

class Random
{
public:
	static void Init();
	static float Float();

private:
	static std::mt19937 s_RandomEngine;
	static std::uniform_real_distribution<float> s_Distribution;
};
