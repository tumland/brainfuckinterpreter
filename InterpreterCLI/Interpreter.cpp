#include "stdafx.h"
#include "Interpreter.h"
#include <assert.h>

CInterpreter::CInterpreter(std::string strProgram)
	:m_strProgram(strProgram)
{
	m_data.push_back(0);
	m_cursor = m_data.begin();
}

std::string::iterator findMatchingLoopEnd(std::string::iterator begin, std::string::iterator end)
{
	std::string::iterator it = begin;
	it++; // get past the initial '['

	int depth = 0;
	for( ; it != end ; it++ )
	{
		if( *it == '[' )
			depth++;
		if( *it == ']' && depth == 0 )
			return it;
		if( *it == ']' && depth != 0 )
			depth--;
	}
	// it = end
	return it;
}

bool CInterpreter::Interprete()
{
	assert( !m_strProgram.empty() );

	for(auto it = m_strProgram.begin(); it != m_strProgram.end(); it++ )
	{
		char current = *it;
		switch( current )
		{
		case '>':
			assert(m_cursor != m_data.end());
			if( ++m_cursor == m_data.end() )
			{
				m_data.push_back(0);
				m_cursor-- = m_data.end();
			}
			break;
		case '<':
			if( m_cursor == m_data.begin() )
			{
				// can't go left
				assert(false);
				printf("Error: unable to move left of current position.");
				return false;
			}
			m_cursor--;
			break;
		case '+':
			assert(m_cursor != m_data.end());
			assert((*m_cursor) <= INT_MAX); // catch overflows
			(*m_cursor)++;
			break;
		case '-':
			assert(m_cursor != m_data.end());
			assert((*m_cursor) >= INT_MIN); // catch overflows
			(*m_cursor)--;
			break;
		case '.':
			assert(m_cursor != m_data.end());
			putchar(*m_cursor);
			break;
		case ',':
			assert(m_cursor != m_data.end());
			*m_cursor = getchar();
			break;
		case '[':
			// if byte at data pointer is zero
			if( (*m_cursor) > 0 )
			{
				// push current iter on the stack to jump back to
				m_loopStartStack.push(it);
			}
			else if( !m_loopEndStack.empty() )
			{
				it = m_loopEndStack.top(); // jump to after next ']'
				// loop is done
				m_loopEndStack.pop();
				m_loopStartStack.pop(); 
			}
			else
			{
				// someone wrote a loop with a 0 counter, i.e. while(false)
				// seek to next '['
				it = findMatchingLoopEnd(it,m_strProgram.end());
				if( it == m_strProgram.end() )
				{
					// unmatched []
					return false;
				}
			}
			break;
		case ']':
			// if byte at data pointer is nonzero
			if( (*m_cursor) > 0 )
			{
				if( m_loopStartStack.empty() )
				{
					printf("Error: unmatched []");
					return false;
				}

				// jump back to guy on top of the stack;
				it = m_loopStartStack.top(); // jump to after last ']'
				// don't pop off the stack, the loop is running
			}
			break;
		default:
			assert(false);
			printf("Error: Unrecognized character");
			return false;
		}
	}

	if( !m_loopStartStack.empty() || !m_loopEndStack.empty() )
	{
		// unmatched [] / brain fucked
		return false;
	}

	return true;
}

