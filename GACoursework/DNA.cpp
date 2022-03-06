#include "DNA.h"
#include <cstdlib>
#include <cmath>

DNA::DNA()
{

}

DNA::DNA(std::string targetString)
{
	targetStr = targetString;
	targetPhraseSize = targetString.size();

	createString();
}

DNA::~DNA()
{
	
}

void DNA::assessFitness()
{
	// Max score = targetStr.size() as 1dp, i.e. targetStr.size() = 41, therefore max score = 4.1
	float score = 0.0f;

	for (int i = 0; i < genes.size(); ++i)
	{
		if (genes[i] == targetStr[i])
		{
			score += 0.1f;
		}
	}

	if (score > 0)
	{
		score = std::powf(2, score);
	}

	float max = std::powf(2, 4.1f);

	//fitnessScore = (float)score / targetStr.size();
	fitnessScore = normalise(score, 0, max);
}

float DNA::normalise(float value, float min, float max)
{
	return (value - min) / (max - min);
}

DNA DNA::crossover(DNA partner)
{
	DNA child(targetStr);

	// Pick some random point in the genes
	int randPoint = (int)rand() % genes.size();

	for (int i = 0; i < genes.size(); ++i)
	{
		// All indices before the randomly chose point are
		// populated with one of the parents genes
		if (i < randPoint)
		{
			child.genes[i] = genes[i];
		}
		else
		{
			// All other indices are populated with the other parents genes
			child.genes[i] = partner.genes[i];
		}
	}

	return child;
}

void DNA::mutate()
{
	for (int i = 0; i < genes.size(); ++i)
	{
		int randChance = rand() % 100;

		if (randChance < mutationRate)
		{
			char randChar = rand() % 96 + 32;
			genes[i] = randChar;
		}
	}
}

void DNA::createString()
{
	for (int i = 0; i < targetPhraseSize; ++i)
	{
		char randChar = rand() % 96 + 32;
		genes.push_back(randChar);
	}
}

char DNA::getGene(int indexPos)
{
	return genes[indexPos];
}

float DNA::getFitnessScore()
{
	return fitnessScore;
}
