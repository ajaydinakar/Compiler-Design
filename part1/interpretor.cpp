//********************************************************************************************
//                             Ajay Dinakar Kandavalli, Assignment 1      
//                             cmps5223- Language Translators and Interpreters
//                      Program to implement an intrepreter for MINI-MACHINE Language
//********************************************************************************************
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
//function declerations
int EXCT(int , int , int , int );
int INTRPR();
//Global variables
int* MEM;                           //declaring array pointer
int BR,LC;                          //base register and Load counter 
vector<int>readinput;               //Vector for storing read input variable values from file
void LOAD();
ifstream inputfile;
ofstream outputfile;
int main()
{
	inputfile.open("input1.txt");   //open the input file for reading
	if (!inputfile)
	{
		cout << "cant open inputfile";
		exit(1);
	}
	outputfile.open("output1.txt");//open file in write mode
	cout << "Ajay Dinakar Kandavalli\n\n" ;
	outputfile << "Ajay Dinakar Kandavalli\n\n";
	int filedata = 0;
	inputfile.seekg(0, ios_base::end);  //move cursor from start to the end of file
	filedata = inputfile.tellg();       //counts number of moves by cursor ,indicatig data 
	inputfile.seekg(0);
	if (filedata == 0)//check if file is empty 
	{
		cout << "ERROR!\ninput file is empty\n";
		outputfile << "ERROR!\ninput file is empty\n";
		exit(1);
	}
	LOAD();                           //calling load function
	INTRPR();                       //Calling interpreter function
	delete MEM;
	outputfile.close();
	system("PAUSE");
}
void LOAD()
{
	MEM = new int[400];             //Declaring dynamic array with size 400
	inputfile >> BR;               //Reading first number to Base register
	cout << "BASE REGISTER=" << BR << endl;
	outputfile << "BASE REGISTER=" << BR << endl;
	int i = 0, j = 0;
	while (j<BR + 1)                 //Reading first (BR number )values to Memory(array MEM)
	{
		inputfile >> i;        //store each number from file in to i
		MEM[j] = i;            //store the number in i to MEM with index j
		i++;
		j++;
	}
	while (inputfile >> i)        //Reading the input variables from file and Storing 
								  //them in vector "readinput"
	{
		readinput.push_back(i);
	}
	cout << "Program Quads  and constants\n\n" << endl;
	outputfile << "\nProgram Quads  and constants\n" << endl;
	int k = 1;
	for (int i = 0; i <= BR; i++)  //loop to print quads line by line
	{
		cout << MEM[i] << "\t";
		outputfile << MEM[i] << "\t";
		if ((k % 4) == 0)
		{
			cout << "\n";
			outputfile << "\n";
		}
		k++;
	}
	cout << " \n\n";
	outputfile << "\n";
	cout << "\nBEGIN EXECUTION\n\n";
	outputfile << "\n\nBEGIN EXECUTION\n\n";
	
	                    //Calling interpreter function
	

}
/************************************************************************************/
//function EXCT,parameters opr(operator)and op1,op2,op3(operands)
/************************************************************************************/
int EXCT(int opr, int op1, int op2, int op3)
{
	ofstream outputfile;
	switch (opr)
	{
	case 0:                        //Addition Operation
		MEM[op1 + BR] = MEM[op2 + BR] + MEM[op3 + BR];
		break;
	case 1:                        //subtraction Operation
		MEM[op1 + BR] = MEM[op2 + BR] -MEM[op3 + BR];
			break;
	case 2:                        //Multiplication Operation
		MEM[op1 + BR] = MEM[op2 + BR] * MEM[op3 + BR];
			break;
	case 3:                        //Division operation
		MEM[op1 + BR] = MEM[op2 + BR] / MEM[op3 + BR];
			break;
	case 4:                        //copy data
		MEM[op1 + BR] = MEM[op2 + BR];
		break;
	case 5:                        //update LC 
		LC=op1 ;
		break;
	case 6:                        //conditional jump
		if (MEM[op2 + BR] == 0)
			LC = op1;
		break;
	case 7:                       //conditional jump
		if (MEM[op2 + BR] > 0)
			LC = op1;
		break;
	case 8:                       //read input to memory
		if (readinput.size() == 0)//if no constants more to read
		{
			outputfile.open("output1.txt", ios::app);//open file in append mode
			cout << "\n\nERROR!No input to read";
			outputfile << "\n\nERROR!No input to read";
			LC = -1;//halt the execution as the is an error
			outputfile.close();
		}
		else
		{
			MEM[op1 + BR] = readinput.front();
			readinput.erase(readinput.begin() + 0);
		}
		break;
	case 9:                       //write from memory
		outputfile.open("output1.txt",ios::app);//open file in append mode
		cout << MEM[op1 + BR]<<"\t";
		outputfile << MEM[op1 + BR] << "\t";
		outputfile.close();
		break;
	case 10:
		LC = -1;          //halt the execution in this case
		outputfile.open("output1.txt", ios::app);//open file in append mode
		cout << "\n\nEND EXECUTION\n";
		outputfile << "\n\nEND EXECUTION\n";
		outputfile.close();
		break;
	default:
		/*outputfile.open("output1.txt",ios::app);
		cout << "\nyou entered a instruction with opcode not in the language ";
		outputfile << "\nyou entered a instruction with opcode not in the language ";
		outputfile.close();*/
		return 0;
	}
	return 0;
}
/***************************************************************************************/
// function INTRPR ,Takes no parameters
/***************************************************************************************/
int INTRPR()
{
	ofstream outputfile;     //declaring file object for output redirection
	outputfile.open("output1.txt", ios::app);//open file in append mode
	int opr,op1,op2,op3;
    LC = 0;
	while( LC<BR && LC!=-1)  //stop the loop if LC=-1
	{	                     //or LC>BR
		  
			opr = MEM[LC];
			op1 = MEM[LC + 1];
			op2 = MEM[LC + 2];
			op3 = MEM[LC + 3];
			LC += 4;         //LC points to next instruction in memory
			if (opr > 10)     //if operation code not in language do this
			{
			
			cout << "\nERROR!\n found an instruction with operation code not in the language\n ";
			outputfile << "\nERROR!\nfound an instruction with operation code not in the language\n ";
			
			exit(1);
			}
			EXCT(opr, op1, op2, op3);	//calling execution function	
	}
	if (LC >= BR)
	{
		cout << "\nWARNING!End of instructions , MISSING HALT\n";
		outputfile << "\nWARNING!End of instructions , MISSING HALT\n";
	}
	outputfile.close();
	return 0;
}
