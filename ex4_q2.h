//Mazouz Raphael

//**********STRUCT OF THE ELEMENT
struct element
{
	double value;
	int indexRow;
	int indexCol;
	element *NextRow;
	element *NextCol;

};
class SMatrix 
{
	//*************PRIVATE FIELD
private:
	int _rows, _cols;
	element **p1, **p2;
	int numberofElements;

	//*************PUBLIC FUNCTION
public:
	// construct a 'rows X cols' matrix.
	SMatrix(int rows, int cols);

	// set the (i,j) element to be 'data'
	void setElement(int i, int j, double data);

	// return the (i,j) element
	double getElement(int i, int j);

	// add 'this' to 'other' and put the result in 'result' 
	void add(SMatrix& other, SMatrix& result);

	// multiply 'this' and 'other' and put the result in 'result' 
	void mul(SMatrix& other, SMatrix& result);

	// return the total number of bytes this matrix requires.
	int sizeInBytes();

	// print the contents of this matrix on the screen.
	void print();

	// print the row-indexes of the column linked lists. 
	void printColumnsIndexes();

	// print the column-indexes of the row linked lists. 
	void printRowsIndexes();

	// destroy this matrix.
	~SMatrix();


	//*************PRIVATE FUNCTION
private:
	// range the column with data!=0
	void columnDifZero(int i, int j, double data,element *theNew);

	//range the row with data !=0
	void rowDifZero(int i, int j, double data,element *theNew);

	//range the colum with data = 0
	void columnZero(int i, int j);

	//range the row with data = 0
	void rowZero(int i, int j);

};
