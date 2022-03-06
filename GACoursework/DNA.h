#pragma once
#include <vector>
#include<iostream>

class DNA
{
public:
	DNA();
	DNA(std::string targetString);
	~DNA();

	void assessFitness();
	DNA crossover(DNA partner);
	void mutate();
	float normalise(float value, float min, float max);

	char getGene(int indexPos);
	float getFitnessScore();

private:
	void createString();

	std::vector<char> genes;
	std::string targetStr;
	int targetPhraseSize;
	float fitnessScore = 0.0f;
	int mutationRate = 1;  // 1% mutation rate, 1/100
};