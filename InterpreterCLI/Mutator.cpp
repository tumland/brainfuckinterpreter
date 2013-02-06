#include "stdafx.h"
#include "Mutator.h"
#include <vector>
#include <time.h>
#include <algorithm>
#include <assert.h>

using namespace std;

string chars = "<>+-.[]";
vector<char> acceptableChars(chars.begin(),chars.end());

static size_t g_numChoices = 2;

string::iterator getRandomStringIterator(string::iterator begin, string::iterator end)
{
	// select random index
	size_t len = distance(begin, end);
	size_t choice = rand() % len;
	
	string::iterator newIterator = begin;
	advance(newIterator, choice);
	return newIterator;
}

void replaceRandomChar(string& strProgram)
{
	string::iterator newIterator = getRandomStringIterator(strProgram.begin(), strProgram.end());

	random_shuffle(acceptableChars.begin(), acceptableChars.end());
	*newIterator = acceptableChars.front();
}

void tweakLength(string& strProgram)
{
	// shorter or longer?
	size_t choice = rand() % 1;
	if( choice )
	{
		// remove some shit
		string::iterator it = getRandomStringIterator(strProgram.begin(), strProgram.end());
		strProgram.erase(it);
	}
	else
	{
		// add some shit
		random_shuffle(acceptableChars.begin(), acceptableChars.end());
		strProgram += acceptableChars.front();
	}
}

void CMutator::Mutate(std::string& strProgram)
{
	srand( time(NULL) );
	size_t choice = rand() % g_numChoices + 1;

	switch( choice ) 
	{
	case 0: 
		// Do nothing, yawn
		break;
	case 1:
		// random replacement
		replaceRandomChar(strProgram);
		break;
	case 2:
		// length change
		tweakLength(strProgram);
		break;
	default:
		// we should never be here
		assert(false);
		break;
	}
}

