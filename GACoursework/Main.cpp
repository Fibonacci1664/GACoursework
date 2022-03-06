#include<iostream>
#include <cstdlib>
#include <ctime>
#include "DNA.h"
#include <vector>
#include "Timer.h"

std::string targetPhrase = "To be, or not to be: that is the question";
//std::string targetPhrase = "Hello World!";
//std::string targetPhrase = "This is a test phrase!";
int PHRASE_SIZE = targetPhrase.size();
int POPULATION_SIZE = 1000;
int maxGenerations = 10000;

void initPopulation(std::vector<DNA>& population)
{
	for (int i = 0; i < POPULATION_SIZE; ++i)
	{
		population.push_back(DNA(targetPhrase));
	}
}

void showPopulation(std::vector<DNA>& population)
{
	for (int i = 0; i < POPULATION_SIZE; ++i)
	{
		std::cout << "String " << i << ": \t";

		for (int j = 0; j < PHRASE_SIZE; ++j)
		{
			std::cout << population[i].getGene(j);
		}

		std::cout << "\tFS - [" << population[i].getFitnessScore() << "]";

		std::cout << '\n';
	}
}

void assessFitness(std::vector<DNA>& population)
{
	for (int i = 0; i < POPULATION_SIZE; ++i)
	{
		population[i].assessFitness();
	}
}

void populateMatingPool(std::vector<DNA>& population, std::vector<DNA>& matingPool)
{
	for (int i = 0; i < POPULATION_SIZE; ++i)
	{
		// Convert the 0 - 1 floating point number into an int percentage 0 - 100
		int n = population[i].getFitnessScore() * 100;

		// Add each member of the population n number of times, this ensures
		// The fittest members have the highest probablity of passing on their genes
		// But also doe NOT rule out even the weakest members of the population
		for (int j = 0; j < n; ++j)
		{
			matingPool.push_back(population[i]);
		}
	}
}

int showHighestFitness(std::vector<DNA>& population)
{
	float bestScore = population[0].getFitnessScore();
	int indexSave = 0;

	for (int i = 0; i < POPULATION_SIZE; ++i)
	{
		if (population[i].getFitnessScore() > bestScore)
		{
			bestScore = population[i].getFitnessScore();
			indexSave = i;
		}
	}

	return indexSave;
}

std::string showBestPhrase(int bestIndex, std::vector<DNA>& population)
{
	std::string bestPhrase;

	for (int i = 0; i < PHRASE_SIZE; ++i)
	{
		bestPhrase += population[bestIndex].getGene(i);
	}

	return bestPhrase;
}

int main()
{
	std::srand(std::time(nullptr));

	std::vector<DNA> population;
	std::vector<DNA> matingPool;

	initPopulation(population);

	//showPopulation(population);
	int bestIndex = showHighestFitness(population);
	int counter = 0;
	std::string bestPhrase;
	bool targetFound = false;
	Timer timer;
	timer.start();

	while (std::strcmp(&targetPhrase[0], &bestPhrase[0]) != 0)
	{
		assessFitness(population);
		bestIndex = showHighestFitness(population);
		bestPhrase = showBestPhrase(bestIndex, population);

		std::cout << "Gen: " << counter << '\n';
		std::cout << "Best Phrase:\t" << bestPhrase;
		std::cout << "\tFS - [" << population[bestIndex].getFitnessScore() << "]\n";

		matingPool.clear();
		populateMatingPool(population, matingPool);

		for (int i = 0; i < population.size(); ++i)
		{
			int randIndexA = (int)rand() % matingPool.size();
			int randIndexB = (int)rand() % matingPool.size();

			DNA parentA = matingPool[randIndexA];
			DNA parentB = matingPool[randIndexB];
			DNA child = parentA.crossover(parentB);

			child.mutate();

			population[i] = child;
		}

		++counter;

		// Check if we have found our target phrase
		if (std::strcmp(&targetPhrase[0], &bestPhrase[0]) == 0)
		{
			// If we do then break out
			targetFound = true;
			break;
		}
	}

	timer.stop();
	int hours = timer.elapsedSeconds() / 3600;
	int minutes = timer.elapsedSeconds() / 60;
	int seconds = timer.elapsedSeconds();

	if (seconds >= 60)
	{
		seconds -= 60;
		++minutes;
	}

	if (targetFound)
	{
		std::cout << "\nTarget phrase found in " << (counter - 1) << " generations.\n";
		std::cout << "\nTime taken: " << hours << "hrs " << minutes << "mins " << seconds << "s\n";
	}

	return 0;
}