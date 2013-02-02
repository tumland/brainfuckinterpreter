#pragma once
#include <list>
#include <stack>

class CInterpreter
{
public:
	CInterpreter(std::string strProgram);
	~CInterpreter(void);

	std::list<int> m_data;

	// stack for storing loop start indices
	std::stack<std::string::iterator> m_loopStartStack;
	// stack for storing loop end indices
	std::stack<std::string::iterator> m_loopEndStack;

	std::list<int>::iterator m_cursor;

	bool Interprete();

	std::string m_strProgram;

};

