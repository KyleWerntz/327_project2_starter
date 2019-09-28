/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 */

//============================================================================
//	TODO add necessary includes here
#include "array_functions.h"
#include "utilities.h"
#include "constants.h"
#include <array>
//============================================================================

//============================================================================
//	stuff you will need
//============================================================================
//TODO define a structure to track words and number of times they occur
struct wordCounter
{
	std::string word;
	int occurences;
};

//TODO add a global array of entry structs (global to this file)
//std::array<wordCounter, 2100> wordCounterArray;
wordCounter wordCounterArray[2100];

//TODO add variable to keep track of next available slot in array
int nextAvailableSpot;

//TODO define all functions in header file
void clearArray()
{
	for (int i = 0; i < sizeof(wordCounterArray); i++)	{
		if (wordCounterArray[i].occurences == 0)	{
			break;
		}
		else	{

			wordCounterArray[i].occurences = 0;
			wordCounterArray[i].word="";
		}
	}
}

int getArraySize()
{
	int size = 0;
	for (int i = 0; i < sizeof(wordCounterArray); i++)	{
		if (wordCounterArray[i].occurences != 0)
			size++;
		else if (wordCounterArray[i].occurences == 0)
			return size;
	}
	return size;
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
		int i = 0;
		std::string line;
		while(!myfstream.eof())
		{
			i++;
			getline(myfstream, line);
			processLine(line);
		}
		if (i == 1 && getArraySize() == 0)
			return false;
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
	if (strip_unwanted_chars(token) && getArraySize() == 0)	{
		//std::cout << "token: " + token << std::endl;
		wordCounterArray[0].word = token;
		wordCounterArray[0].occurences = 1;
		return;
	}

	for (int i = 0; i < sizeof(wordCounterArray); ++i)
	{
		if (strip_unwanted_chars(token))	{
			//std::cout << token << std::endl;
			std::string uppernew = token;
			std::string upperog = wordCounterArray[i].word;
			toUpper(upperog);
			toUpper(uppernew);
			if (wordCounterArray[i].occurences == 0)	{

				wordCounterArray[i].word = token;
				wordCounterArray[i].occurences = 1;
				break;
			}
			else if(upperog == uppernew)	{
				wordCounterArray[i].occurences++;
				break;
			}
			else if (wordCounterArray[i].word == token)	{
				wordCounterArray[i].occurences++;
				break;
			}
		}
	}
}

bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode)
{
	myfile.open(myFileName.c_str(), mode);
	if (myfile.is_open())	{
		return true;
	}
	return false;
}

void closeFile(std::fstream &myfile)
{
	if (myfile.is_open())
		myfile.close();
}

int writeArraytoFile(const std::string &outputfilename)
{
	std::ofstream myOutputfile;
	myOutputfile.open(outputfilename.c_str());

	for (int i = 0; i < sizeof(wordCounterArray); i++)
	{
		if (wordCounterArray[i].occurences == 0)	{
			myOutputfile.close();
			return 0;
		}
		else
		{
			std::string occurence = intToString(wordCounterArray[i].occurences);
			std::string data = wordCounterArray[i].word + " " + occurence;

			myOutputfile << data << std::endl;
		}
	}
	return -1;
}

void sortArray(constants::sortOrder so)
{
	if (wordCounterArray[1].occurences == 0)
		return;

	wordCounter temp;

	switch(so)
	{
	case 1:
		for (int i = 0; i < getArraySize(); i++)
		{
			for (int j = 1; j < getArraySize() - i; j++)
			{
				std::string word1 = wordCounterArray[j-1].word;
				std::string word2 = wordCounterArray[j].word;
				toUpper(word1);
				toUpper(word2);
				if (word1 > word2)
				{
					temp = wordCounterArray[j - 1];
					wordCounterArray[j - 1] = wordCounterArray[j];
					wordCounterArray[j] = temp;
				}
//				if (wordCounterArray[j - 1].word > wordCounterArray[j].word)
//				{
//					temp = wordCounterArray[j - 1];
//					wordCounterArray[j - 1] = wordCounterArray[j];
//					wordCounterArray[j] = temp;
//				}
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


