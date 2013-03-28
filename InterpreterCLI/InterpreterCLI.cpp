// InterpreterCLI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Interpreter.h"
#include <string>
#include "Mutator.h"
#include <vector>
#include <iostream>
#include <conio.h>
#include <fstream>
using namespace std;

int printHelp(_TCHAR* argv[])
{
	wcout << "Unrecognized parameter" << endl;
	wcout << "Usage: " << argv[0] << " parameters" << endl;

	wcout << "\t -h | -? | -help : print this help text" << endl;
	wcout << "\t -f | -file <file path> : run Brain Fuck program text file" << endl;
	wcout << "\t -i | -interactive : run Brain Fuck interpreter in interactive mode" << endl;
	return 1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Hello World!
	// string strProgram = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";
	
	// 2 input methods : keyboard, or from file.

	cout << "Welcome to BrainFuckIntepreter!" << endl;
	cout << "\tCreated by Torrey Umland" << endl;
	cout << "\ttorreyumland@gmail.com" << endl;

	cout << "Licensed under the GNU General Public License, version 3" << endl;
	cout << "For more information see: http://opensource.org/licenses/GPL-3.0" << endl;
	
	if( argc < 2 )
		return printHelp(argv);
	
	for( int nArg = 1; nArg != argc; ++nArg )
	{
		if( _wcsnicmp(argv[nArg], L"-h", 2) == 0 )
		{
			return printHelp(argv);
		}
		else if( _wcsnicmp(argv[nArg], L"-i", 2) == 0 )
		{
			cout << "Have at ye! Hit 'Q' to stop.\n";
			cout << ">>> ";
			
			while( true )
			{
				wstring strIn;
				wcin >> strIn;

				if( _wcsnicmp(strIn.c_str(), L"q", 1) == 0 )
					break;
				else
				{
					wcout << L"Shazbot: Not fully implemented yet!" << endl;
				}
			}
		}
		else if( _wcsnicmp(argv[nArg], L"-f", 2) == 0 )
		{
			if( nArg+1 >= argc )
				return printHelp(argv);
			
			cout << "Have at ye!\n";
			cout << ">>> ";

			wstring strFilePath = argv[nArg+1];
			
			wifstream fInput(strFilePath);
			wstring strProgram;

			if( !fInput )
			{
				wcout << L"Failed to open the file!" << endl;
				return 1;
			}

			while( fInput )
			{
				fInput >> strProgram;
			}
			CInterpreter interpreter;

			if( !interpreter.Interprete(strProgram) )
			{
				wcout << L"Something's wrong!" << endl;
				return 1;
			}
		}
	}

	return 0;
}




