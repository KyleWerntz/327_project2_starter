/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 */

//============================================================================
//	TODO add necessary includes here
#include "array_functions.h"
//#include "constants.h"
#include <array>
//============================================================================

//============================================================================
//	stuff you will need
//============================================================================
//TODO define a structure to track words and number of times they occur
struct wordCounter
{
	std::string word = "";
	int occurences = 0;
};

//TODO add a global array of entry structs (global to this file)
//std::array<wordCounter, 2100> wordCounterArray;
wordCounter wordCounterArray[2100];

//TODO add variable to keep track of next available slot in array
int nextAvailableSpot;

//TODO define all functions in header file
void clearArray()
{
	wordCounter temp;
	temp.occurences=0;
	temp.word="";

	std::fill_n(wordCounterArray, 6, temp);
}

int getArraySize()
{
	return sizeof(wordCounterArray);
}

std::string getArrayWordAt (int i)
{
	return wordCounterArray[i].word;
}

int getArrayWord_NumbOccur_At(int i)
{
	return wordCounterArray[i].occurences;
}

bool processFile(std::fstream &myfstream)
{
	if (myfstream.is_open())
	{
		std::string line;

		while(!myfstream.eof())
		{
			getline(myfstream, line);
			processLine(line);
		}

		return true;
	}
	return false;
}

void processLine(std::string &myString)
{
	std::stringstream ss(myString);
	std::string tempToken;

	while (getline(ss, tempToken, constants::CHAR_TO_SEARCH_FOR))
	{
		processToken(tempToken);
	}
}

void processToken(std::string &token)
{
	for (int i = 0; i < sizeof(wordCounterArray); ++i)
	{
		if (wordCounterArray[i].occurences == 0)
		{
			wordCounterArray[i].word = token;
			wordCounterArray[i].occurences++;
			return;
		}
		else if (wordCounterArray[i].word == token)
		{
			wordCounterArray[i].occurences++;
			return;
		}
	}
}

bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode)
{
	myfile.open(myFileName.c_str());
	if (myfile.is_open())
		return true;
	return false;
}

void closeFile(std::fstream &myfile)
{
	myfile.close();
}

int writeArraytoFile(const std::string &outputfilename)
{
	for (int i = 0; i < sizeof(wordCounterArray); i++)
	{
		if (wordCounterArray[i].occurences == 0)
			return 0;
		else
		{
			std::string occurence = std::to_string(wordCounterArray[i].occurences);
			std::string data = wordCounterArray[i].word + " " + occurence;

			std::ofstream mystream;
			mystream.open(outputfilename.c_str());

//			outputfilename << data << '/n';
		}
	}
	return 0;
}

void sortArray(constants::sortOrder so)
{
	if (wordCounterArray[1].occurences == 0)
		return;

	wordCounter temp;

	switch(so)
	{
	case 1:
		for (int i = 0; i < sizeof(wordCounterArray); ++i)
		{
			for (int j = 1; j < sizeof(wordCounterArray) - i; ++j)
			{
				if (wordCounterArray[j - 1].word > wordCounterArray[j].word)
				{
					temp = wordCounterArray[j - 1];
					wordCounterArray[j - 1] = wordCounterArray[j];
					wordCounterArray[j] = temp;
				}
			}
		}
		break;
	case 2:
		for (int i = 0; i < sizeof(wordCounterArray) - 1; ++i)
		{
			int smallLocation = i;
			for (int j = (1 + i); j < sizeof(wordCounterArray); ++j)
			{
				if (wordCounterArray[j - 1].word < wordCounterArray[j].word)
				{
					smallLocation = j;
				}
			}
			temp = wordCounterArray[smallLocation];
			wordCounterArray[smallLocation] = wordCounterArray[i];
			wordCounterArray[i] = temp;
		}
		break;
	case 3:
			for (int i = 0; i < sizeof(wordCounterArray); ++i)
			{
				for (int j = 1; j < sizeof(wordCounterArray) - i; ++j)
				{
					if (wordCounterArray[j - 1].occurences > wordCounterArray[j].occurences)
					{
						temp = wordCounterArray[j - 1];
						wordCounterArray[j - 1] = wordCounterArray[j];
						wordCounterArray[j] = temp;
					}
				}
			}
			break;
	}
}


