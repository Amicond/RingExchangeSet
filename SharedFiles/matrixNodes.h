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

	void matrixNodes::fillMatrix(int maxPlaquetDistance);
	void matrixNodes::printMatrix();
	void matrixNodes::printMatrixToFile(std::string fname);
	int getElem(int i, int j);
	int getSize();
	int  ** getMatrix();
};

#endif // !MATRIXNODES_H 