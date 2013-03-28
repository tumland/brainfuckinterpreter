#include "stdafx.h"
#include "Interpreter.h"
#include <assert.h>
#include <algorithm>

using namespace std;

bool CInterpreter::InterpreteChar(wchar_t c, list<int>& data, list<int>::iterator& cursor)
{
	switch( c )
	{
	case '>':
		assert(cursor != data.end());
		if( ++cursor == data.end() )
		{
			data.push_back(0);
			cursor-- = data.end();
		}
		break;
	case '<':
		if( cursor == data.begin() )
		{
			// can't go left
			wprintf(L"Error: unable to move left of current position.\n");
			return false;
		}
		cursor--;
		break;
	case '+':
		assert(cursor != data.end());
		assert((*cursor) <= INT_MAX); // catch overflows
		(*cursor)++;

		break;
	case '-':
		assert(cursor != data.end());
		assert((*cursor) >= INT_MIN); // catch overflows
		(*cursor)--;
		break;
	case '.':
		assert(cursor != data.end());
		putchar(*cursor);
		break;
	case ',':
		assert(cursor != data.end());
		*cursor = getchar();
		break;
	default:
		assert(false);
		wprintf(L"Error: Unrecognized character. [] should be handled in InterpreteChunk\n");
		return false;
	}
	return true;
}

wstring::iterator CInterpreter::seekToLoopClose(wstring::iterator begin, wstring::iterator end)
{
	size_t nDepth = 0;

	for( auto it = begin; it != end; it++ )
	{
		if( *it == '[' )
		{
			// seek to closing ']'
			nDepth++;
		}
		if( *it == ']' )
		{
			nDepth--;
			if( nDepth == 0 )
			{
				return it;
			}
		}
	}
	return end;
}

bool CInterpreter::InterpreteChunk(wstring::iterator chunkBegin, wstring::iterator chunkEnd, list<int>& data, list<int>::iterator& cursor)
{
	// Validate loop chars
	// Not the fastest way, but it's pretty
	if( count(chunkBegin, chunkEnd, '[') !=
		count(chunkBegin, chunkEnd, ']') )
	{
		return false;
	}

	for( auto it = chunkBegin; it != chunkEnd; it++ ) {
		if( *it == '[' )
		{
			// seek to closing ']'
			auto itEnd = seekToLoopClose(chunkBegin, chunkEnd);
			++it;
			// if cursor data is 0, this resembles a while(false)
			while( *cursor > 0 )
				// run to loop end
				if( !InterpreteChunk(it, itEnd, data, cursor) )
					return false;
			it = itEnd;
		}
		else if( *it == ']' )
		{
			it++;
		}
		else
		{
			if( !InterpreteChar(*it, data, cursor) )
				return false;
		}
	}
	return true;
}

bool CInterpreter::Interprete(wstring strProgram)
{
	list<int> data;
	data.push_back(0);
	list<int>::iterator cursor = data.begin();

	return InterpreteChunk(strProgram.begin(), strProgram.end(), data, cursor);
}
