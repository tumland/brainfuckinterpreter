// InterpreterCLI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Interpreter.h"
#include <string>
#include "Mutator.h"
#include <vector>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	string strProgram = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";
	
	CMutator mutator;
	
	for( int i = 0; i < 10; i++ )
	{
		mutator.Mutate(strProgram);
	}


	CInterpreter interpreter(strProgram);

	if( !interpreter.Interprete() )
	{
		printf("\nUgly mutant, garbage!\n");
		return 1;
	}
	printf("\nSuccessful mutation!\n");
	return 0;
}




