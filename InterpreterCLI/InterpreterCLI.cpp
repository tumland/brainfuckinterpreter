// InterpreterCLI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Interpreter.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CInterpreter interpreter("++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.");
	return interpreter.Interprete() ? 0 : 1;
}




