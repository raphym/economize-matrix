//Mazouz Raphael

#include "ex4_q2.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


SMatrix::SMatrix(int rows, int cols)//Constructor
{
	if (rows > 0 && cols > 0)
	{
		p1 = new element*[cols];
		p2 = new element*[rows];
		_rows = rows;
		_cols = cols;
		int i;
		for (i = 0; i < cols; i++)
			p1[i] = NULL;
		for (i = 0; i < rows; i++)
			p2[i] = NULL;
	}
	else
	{
		//if the input is not in the range
		cout << "Incorrect parameter of the matrix" << endl;
		cin.get();
		exit(-1);
	}
}

double SMatrix::getElement(int i, int j)//Function which return the element
{
	if (((i >= 0) && (i < _rows)) && ((j >= 0) && (j < _cols)))
	{
		element *pRow = 0;//pointer on the Row
		pRow = p2[i];
			
		if (p2[i] == NULL)//if in the begin the element is null
			return 0; //the number is 0;

		else //the list of the row is not empty
			{
				for(pRow=p2[i] ; pRow!=NULL ; pRow=pRow->NextCol)
				{
					if(pRow->indexCol==j)//if the index found 
					return pRow->value;//return the value
				}
			}	
	}
	else
	{
		cout << "ERROR ==> The index doesn't exist in your matrix" << endl;
		cin.get();
		exit(-1);
	}
	return 0;
}

void SMatrix::setElement(int i, int j, double data)
{
	
	if (((i >= 0) && (i < _rows)) && ((j >= 0) && (j < _cols)))
	{
		if (data !=0) //If the number to add is different of 0
		{
			element *theNew = new element();//create the new element
			theNew->value = data;//data
			theNew->indexCol = j;//index column
			theNew->indexRow = i;//index row
			theNew->NextCol = NULL;//Next column of the New
			theNew->NextRow = NULL;//Next row of the new

			columnDifZero(i,j,data,theNew);//Go to arrange the column
			rowDifZero(i, j, data,theNew);//Go to arrange the row
		}
		else//if the number to add is  0 (data=0)
		{
			columnZero(i, j);//Go to arrange the column
			rowZero(i, j);//Go to arrange the row
		}
	}
	else //If the input of index is not in the range 
	{
		cout << 
		"ERROR ==>The size of your matrix does not allow to enter these values"
		<< endl;
		cin.get();
		exit(-1);
	}
}



void SMatrix::columnDifZero(int i, int j, double data,element *theNew)
{
	//The function is arranging the column , the data !=0;

	//********************************If the list is empty
	if (p1[j]== NULL)//if the column is empty
	{
		p1[j]=theNew;
		theNew->NextRow = NULL;
		numberofElements++;
			return;
	}
	//********************************If there is one element 
	else if (p1[j]->NextRow == NULL)
	{
		if (p1[j]->indexRow > i)
		{
			//if the index of the only element bigger than the new
			theNew->NextRow = p1[j];
			p1[j] = theNew;
			numberofElements++;
			return;
		}
		if (p1[j]->indexRow == i)
		{
			//if the index of the only element equal to the new
			p1[j]->value = data;
			return;
		}
		if (p1[j]->indexRow < i)
		{
			//if the new have to be the last
			p1[j]->NextRow = theNew;
			numberofElements++;
			return;
		}
	}
	//******************************** If there are many elements
	else
	{
		element *pCol = p1[j]; //pointer on the loop
		for (pCol=p1[j] ;pCol != NULL; pCol = pCol->NextRow)
		{
			if (pCol->NextRow == NULL)
			{
				//if the new have to be the last
				pCol->NextRow = theNew;
				theNew->NextRow = NULL;
				numberofElements++;
				return;
			}
			if (p1[j]->indexRow > i)
			{
				//if the new have to be the first
				theNew->NextRow = pCol;
				p1[j] = theNew;
				numberofElements++;
				return;
			}
			if (pCol->NextRow->indexRow == i)
			{
				//if the index of the next is equal to the new
				pCol->NextRow->value = data;
				return;
			}
			else if (pCol->NextRow->indexRow > i)
			{
				//if the index of the next is bigger than the new
				theNew->NextRow = pCol->NextRow;
				pCol->NextRow = theNew;
				numberofElements++;
				return;
			}
		}
	}
}



void SMatrix::rowDifZero(int i, int j, double data,element *theNew)
{
	//The function is arranging the row , the data !=0;
	//***************************************if the row is empty
	if (p2[i] == NULL)
	{
		p2[i] = theNew;
		theNew->NextCol = NULL;
		return;
	}
	//****************************************If there is one element
	else if (p2[i]->NextCol == NULL)
	{
		if (p2[i]->indexCol > j)
		{
			//if the index of the only element bigger than the new
			theNew->NextCol = p2[i];
			p2[i] = theNew;
			return;
		}
		if (p2[i]->indexCol == j)
		{
			//if the index of the only element equal to the new
			p2[i]->value = data;
			delete(theNew);
			return;
		}
		if (p2[i]->indexCol < j)//if the new have to be the last
		{
			p2[i]->NextCol = theNew;
			return;
		}
	}
	//*****************************************If there are many elements
	else
	{
		element *pRow = p2[i];//pointer on the loop
		for (pRow=p2[i]; pRow != NULL; pRow = pRow->NextCol)
		{
			if (pRow->NextCol == NULL)
			{
				//if the new have to be the end
				pRow->NextCol = theNew;
				theNew->NextCol = NULL;
				return;
			}
			if (p2[i]->indexCol > j)
			{
				//if the new have to be the first
				theNew->NextCol= pRow;
				p2[i] = theNew;
				return;
			}
			if (pRow->NextCol->indexCol == j)
			{
				//if the index of the next is equal to the new
				pRow->NextCol->value = data;
				delete(theNew);
				return;
			}
			else if (pRow->NextCol->indexCol > j)
			{
				//if the index of the next is bigger than the new
				theNew->NextCol = pRow->NextCol;
				pRow->NextCol = theNew;
				return;
			}
		}
	}
}

void SMatrix::columnZero(int i, int j)
{
	//****************************If the list is empty
	if (p1[j] == NULL)
		return;
	//****************************If there is one element 
	else if (p1[j]->NextRow == NULL) 
	{
		if (p1[j]->indexRow == i)
		{
			//If the  index of the element is the same
			p1[j] = NULL;
			return;
		}
		
	}
	else
		//*****************************If there are many elements
	{
		element *pCol = p1[j];
		element *pErase = 0;
		for (pCol=p1[j]; pCol->NextRow !=NULL; pCol = pCol->NextRow)
		{
			if (pCol->NextRow->indexRow == i)
			{
				//If the next is the element to erase
				pErase = pCol->NextRow;
				pCol->NextRow = pErase->NextRow;
				return;
			}
			if (p1[j]->indexRow == i)
			{
				//If its the first to erase in the column
				p1[j] = p1[j]->NextRow;
				return;
			}
		}
	}
}


void SMatrix::rowZero(int i, int j)
{
	//*********************************If the list is empty
	if (p2[i] == NULL)
		return;
	//*********************************If there is one element
	if (p2[i]->NextCol==NULL)
	{
		if (p2[i]->indexCol == j)
		{
			//If the index of the element is the same
			element *pErase = p2[i];
			p2[i] = NULL;
			delete(pErase);
			numberofElements--;
			return;
		}
	}
	//******************************If there are many elements
	else
	{
		element *pRow = p2[i];
		element *pErase = 0;
		for (pRow=p2[i]; pRow->NextCol != NULL; pRow = pRow->NextCol)
		{
			if (pRow->NextCol->indexCol ==j)
			{
				//If the next is the element to erase
				pErase = pRow->NextCol;
				pRow->NextCol = pErase->NextCol;
				delete(pErase);
				numberofElements--;
				return;
			}
			if (p2[i]->indexCol == j)
			{
				//If its the first to erase in the row
				pErase = p2[i];
				p2[i] = p2[i]->NextCol;
				delete(pErase);
				numberofElements--;
				return;
			}
		}
	}
}



void SMatrix::add(SMatrix& other, SMatrix& result)
{
//Function which add the SMatrix and the Other matrix into the result matrix
	if (_cols != result._cols || _rows != result._rows)
	{
		cout << 
			"ERROR ==> Wrong numbers of columns or rows in the Matrix result";
		cin.get();
		cin.get();
		exit(-1);
	}
	else if (_cols != other._cols || _rows != other._rows)
	{
		cout <<
		"ERROR ==> Wrong numbers of columns or rows in the second Matrix to add";
		cin.get();
		cin.get();
		exit(-1);
	}
	else
	{
		for (int i = 0; i < _rows; i++)
		{
			for (int j = 0; j < _cols; j++)
			{
				result.setElement(i, j, getElement(i,j) +
											other.getElement(i, j));
			}
		}

	}
}

void SMatrix::mul(SMatrix& other, SMatrix& result)
{
//Function which multiply the SMatrix
//and the Other matrix into the result matrix
	double sum = 0;
	if (_rows != result._rows || other._cols != result._cols)
	{
		cout << 
			"ERROR ==> Wrong numbers of columns or rows in the Matrix result";
		cin.get();
		cin.get();
		exit(-1);
	}
	else if (_cols != other._rows)
	{
		cout <<
		"ERROR ==>Wrong numbers of column or row in the second Matrix to Mult";
		cin.get();
		cin.get();
		exit(-1);
	}

	else
	{
		for (int j = 0; j < other._cols; j++)
		{
			for (int i = 0; i < _rows; i++)
			{
				sum = 0;
				for (int k = 0; k < other._rows; k++)
				{
					sum = sum + (getElement(i, k)*other.getElement(k, j));
				}
				result.setElement(i, j, sum);
			}
		}
	}
}



void SMatrix::printColumnsIndexes()
{
	// print the row-indexes of the column linked lists.	
	element *pCol = 0;//Pointer on column
	for (int i = 0; i < _cols; i++)
	{
		cout << i << ": ";
			for (pCol=p1[i]; pCol != NULL ; pCol = pCol->NextRow)
			{
				cout <<pCol->indexRow<< "->";
			}
			cout << endl;
	}
}

void SMatrix::printRowsIndexes()
{
	// print the column-indexes of the row linked lists.
	element *pRow = 0;//Pointer on column
	for (int i = 0; i < _rows; i++)
	{
		cout << i << ": ";
		for (pRow = p2[i]; pRow != NULL; pRow = pRow->NextCol)
		{
			cout << pRow->indexCol << "->";
		}
		cout << endl;
	}
}

void SMatrix::print()
{
	//This function print the entire SMatrix
	for (int i = 0; i < _rows; i++)//loop on the rows
	{
		int j=0;
		for (j=0; j< _cols-1; j++)//loop on the columns
		{
			cout << getElement(i, j) << ",";
		}
		cout << getElement(i, j);//print the last element of the row without","
		cout << endl;//to go down row for the screen
	}
}



int SMatrix::sizeInBytes()
{
	//Function wich return the total number of bytes this matrix requires.
	int total = 0;
	total =(3 * sizeof(int)) + sizeof(p1) + sizeof(p2) + (sizeof(element) *
			numberofElements + sizeof(*p1)*_cols + sizeof(*p2)*_rows );
	return total;
}

SMatrix::~SMatrix()//Function to free all the memory
{
	element *pErase = 0;
	for (int i = 0; i < _cols; i++)
	{
		if (p1[i] == NULL)
		{
			//do nothing
		}
		else
		{
			element *p = p1[i];
			while (p->NextRow != NULL)
			{
				pErase = p;
				p = p->NextRow;
				delete(pErase);
			}
			delete(p);
		}
	}
	delete(p1);
	delete(p2);	
}

