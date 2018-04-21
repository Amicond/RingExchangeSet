#ifndef MATRIXNODES_H 
#define MATRIXNODES_H 
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
class matrixNodes
{
	int **matrix;
	int size;
public:
	matrixNodes();
	~matrixNodes();

	void fillMatrix(int maxPlaquetDistance);
	void printMatrix();
	void printMatrixToFile(std::string fname);
	int getElem(int i, int j);
	int getSize();
	int  ** getMatrix();
};

#endif // !MATRIXNODES_H 