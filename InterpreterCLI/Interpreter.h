#pragma once
#include <list>


class IInterpreter
{
public:
	virtual bool Interprete(std::wstring strProgram) = 0;

	typedef std::auto_ptr<IInterpreter> Ptr;
};


class CInterpreter : IInterpreter
{
public:
	bool Interprete(std::wstring strProgram);
	bool InterpreteChunk(std::wstring::iterator chunkBegin, std::wstring::iterator chunkEnd, std::list<int>& data, std::list<int>::iterator& cursor);
	bool InterpreteChar(wchar_t c, std::list<int>& data, std::list<int>::iterator& cursor);

private:
	std::wstring::iterator seekToLoopClose(std::wstring::iterator begin, std::wstring::iterator end);
};

