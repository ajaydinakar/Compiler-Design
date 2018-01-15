//********************************************************************************************
//                             Ajay Dinakar Kandavalli, Assignment 2      
//                         cmps5223- Language Translators and Interpreters
//                 Program to implement Scanner for programs written in L756 language 
//********************************************************************************************
#include <iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cstring>
using namespace std;

//function declarations

void initialize_Tables();
string NEXTLN(ifstream &);
void NEXTCHAR(ifstream &, char &);
void SCANTOKEN(ifstream &,int &,int &,string & );
int scanTabindex(char);
void Action(int, string &,int & ,int &);
void LOOKID(string,int &,int &);
void LOOKINT(int,int &,int &);
void printsymtab(int);
void ERROR();

//Global variables

string symtab[100][3];          //declaring 2D arrays
int inttab[100][2];
int M[13][13];
int pos, length, symb_count,int_count,int_index,num;
//string clas, value;
string line;
string outputfile;
string inputfile;
bool error=false, eof = false;
ifstream infile;
ofstream outfile;
/********************************************/
//main function
/*********************************************/
int main()
{
	cout << "enter the Input file Name:";
	cin >> inputfile;
	cout << "enter the output file Name:";
	cin >> outputfile;
	initialize_Tables();
	infile.open(inputfile);
	outfile.open(outputfile);
	outfile << "Ajay Dinakar Kandavalli\n\n";
	int i = 0;
	string token = " ";
		int clas=0, val=0;
	while (!infile.eof())
	{
		SCANTOKEN(infile,clas,val,token);
		cout << clas << "    " << val << "     " << token<<endl;
	}
	//releaseMEM();
	infile.close();
	outfile.close();
	system("pause");
}
//***************************************************************
//function SCANTOKEN,parameters:filename
/***************************************************************/
void SCANTOKEN(ifstream& file,int &clas,int &value,string &token)
{
	bool done = false;
	int state = 0;
	
	char getchr;
	do
	{
		if (state < 0)
		{
			done = true;
			//cout << state << "token"<<token<<endl;
			token.erase(token.end());
			Action(state, token,clas,value);
			if (token == "REM ")//ignoring the comments
				length = 0;
		}
		else
		{
			NEXTCHAR(file, getchr);
			string s(1, getchr);
			
			int chr = scanTabindex(getchr);
			token = token + s;
			state = M[state][chr];		
//cout<< "state= " << state << "\t char= " << getchr << "\t token " << token << endl;
		}
	} while (!done);

}
/***************************************************************/
//function Action,parameters: state value,string token
/****************************************************************/
void Action(int state, string &token,int &clas,int& value)
{
	//cout << "in acion state:" << state << chr << endl;
	
	switch (state)
	{
	case -1:
		LOOKID(token,clas,value); 
		//outfile << "\t" << clas << "\t" << value << endl;
		//cout << "state" << state << "token" << chr << endl;

		break;
	case -2:
		num = stoi(token);
		LOOKINT(num,clas,value);
		//outfile << "\t" << clas << "\t" <<  << endl;
	case -3:
		if (token == "+ ")
		{
			clas = 15;
			value = 0;
			//outfile << "\t" << "15" << "\t" << "0" << endl;
		}
		else
		{
			outfile << "\t" << "15" << "\t" << "1" << endl;
			clas = 15;
			value = 0;
		}
		break;
	case -4:
		if (token == "* ")
			outfile << "\t" << "16" << "\t" << "0" << endl;
		else
			outfile << "\t" << "16" << "\t" << "1" << endl;
		break;
	case -5:
		if (token == "( ")
			outfile << "\t" << "17" << "\t" << " " << endl;	
		break;
	case -6:
		if (token == ") ")
			outfile << "\t" << "18" << "\t" << " " << endl;
		break;
	case -7:
		if (token == "< ")
			outfile << "\t" << "19" << "\t" << "1" << endl;
		break;
	case -8:
		if (token == "> ")
			outfile << "\t" << "19" << "\t" << "2" << endl;
		break;
	case -9:
		if (token == "= ")
			outfile << "\t" << "20" << "\t" << "2" << endl;
		break;
	case -50:
		eof = true;
		outfile << "-1"<<endl;
		break;
	case -100:
		error = true;
		outfile << "0"<<endl;
	    ERROR();
		
		break;
	}
	
}
void LOOKID(string token ,int &clas,int &value)
{
	bool found = false;

	for (int i = 0; i < symb_count; i++)
	{
		if (token == symtab[i][0]+" ")
		{
			found = true;
			clas = stoi(symtab[i][1]);
			value = stoi(symtab[i][2]);
		}
		else if (token == symtab[i][0] + "")
		{
			found = true;
			clas = stoi(symtab[i][1]);
			value = stoi(symtab[i][2]);
		}
	}
		if (!found)
		{
			symb_count += 1;
			symtab[symb_count][0] = token;
			(symtab[symb_count][1]) = "21";
			clas = stoi(symtab[symb_count][1]);
			value = symb_count;
				symtab[symb_count][2] = to_string(symb_count);
		}

	
}
/*********************************************************************/
//Function LOOKINT,parameter:integer value 
/**********************************************************************/
void LOOKINT(int num,int &clas,int &value)
{
	bool found = false;

	for (int i = 0; i <= int_count; i++)
	{
		if (num == inttab[i][1] )
		{
			found = true;
			clas = 22;
			int_index = inttab[i][0];
			value = int_index;
		}

	}
	if (!found)
	{
		int_count += 1;
		
		clas  = 22;
	  int_index=inttab[int_count][0] = int_count;
	  value = int_index;
	  inttab[int_count][1] = num;

	}
}
//********************************************************************
//Function NEXTLN,parameters :inputfile
//*****************************************************************
string NEXTN(ifstream& file)
{
	
	string card;
	if (!file.eof())
	{
    	getline(file, card);
		outfile<< card << endl;
	}
	return card;
}
/*************************************************************************/
//function NEXTCHAR,parameters :filename,character
/****************************************************************************/
void NEXTCHAR(ifstream& file, char &chr)
{
	if (length == 0) {
		line = NEXTLN(file);
		line += ' ';
		length = line.length();
		pos = 0;
	}
	if (length > 0) {
		chr = line[pos];
		pos++;
		length--;
	}
}
/**********************************************************************************/
//function initialize_Tables() ,parameters:nil
//function for loading symbol table with reserve words,int table with first two rows
//and scanstate table with data from scanstate file
/**********************************************************************************/
void initialize_Tables()
{
	int idx = 0, res;
	ifstream symb_file, ScanSt_file;
	string file1, file2;
	 file1 = "sy.txt";
	 file2 = "sc.txt";
	/* cout << "Enter symbolin file name:";
	 cin >> file1;
	 cout << "Enter Scan states file name";
	 cin >> file2;*/

	symb_file.open(file1);
	symb_file >> res;//
					 //symbol atable
	symb_count = res;

	while (idx<res)
	{
		symb_file >> symtab[idx][0]; symb_file >> symtab[idx][1];
		symtab[idx][2] = '0';
		idx += 1;
	}
	//Int table
	
	inttab[0][0] = 0;
	inttab[0][1] = 0;
	inttab[1][0] = 1;
	inttab[1][1] = 1;
	int_count = 1;
	//printsymtab(res);
	symb_file.close();
	//states table

	ScanSt_file.open(file2);
	//initalizing the array M with the scan statefile entries
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			ScanSt_file >> M[i][j];
			cout << M[i][j] << "\t";
		}
		cout << endl;
	}
	ScanSt_file.close();
}

/*********************************************************************/
//function scanTabindex,parameters :charecter
//function for converting char to int for referencing scan states table
/***********************************************************************/
int scanTabindex(char chr)
{
	int ch = int(chr);
	if (ch == 32)           //blank space
		return 0;
	else if (ch == 43 || ch == 45)// + or - 
		return 3;
	else if (ch == 42 || ch == 47)// * or /
		return 4;
	else if (ch == 40)//  (
		return 5;
	else if (ch == 41)   //   )
		return 6;
	else if (ch == 60)   //   <
		return 7;
	else if (ch == 62)   //   >
		return 8;
	else if (ch == 61)   //   =
		return 9;
	else if (ch == 58)   //   :
		return 10;
	else if (ch >= 48 && ch <= 57)//0-9
		return 2;
	else if (ch >= 45 && ch <= 90)//A-Z
		return 1;
	
	else
		return -100;// anything else
}
void printsymtab(int res)
{
	for (int i = 0; i < res; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << symtab[i][j];
			cout << "\t";
		}
		cout << endl;
	}
}
//*********************************************************
// function ERROR,parameters:nil
//*********************************************************
void ERROR()
{
	outfile << "ERROR!invalid character" << endl;
}