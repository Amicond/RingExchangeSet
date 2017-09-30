#include "stdafx.h"
#include "matrixNodes.h"

matrixNodes::matrixNodes()
{
}

matrixNodes::~matrixNodes()
{
	for (int i = 0; i < size; i++)
		delete [] matrix[i];
	delete [] matrix;
}

void matrixNodes::fillMatrix(int curOrder)
{
	//init
	size = 2 * curOrder + 1;
	matrix = new int*[size];
	for (int i = 0; i < size; i++)
		matrix[i] = new int[size];

	//fill
	int s = size / 2;
	int dir = 0;
	int cx, cy, ct, cb, cl, cr;
	dir = 0;//0- направо, 1-вверх, 2- налево, 3- вниз
	ct = cb = cl = cr = cx = cy = s;
	for (int curn = 0; curn < size*size; curn++)
	{
		matrix[cy][cx] = curn;
		switch (dir)
		{
		case 0:
			if (cx == cr)
			{
				cr++;
				cl--;
				cx++;
				dir = 1;
			}
			else
			{
				cx++;
			}
			break;
		case 1:
			if (cy == ct)
			{
				ct--;
				cb++;
				cy--;
				dir = 2;
			}
			else
			{
				cy--;
			}
			break;
		case 2:
		{
			cx--;
			if (cx == cl)
			{
				dir = 3;
			}
		}
		break;
		case 3:
		{
			cy++;
			if (cy == cb)
			{
				dir = 0;
			}
		}
		break;
		}
	}
}

void matrixNodes::printMatrix()
{
	//!------------Matrix output--------------------
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			std::cout << std::setw(3) << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
	//!-----------Output end

}

void matrixNodes::printMatrixToFile(std::string fname)
{
	std::ofstream out(fname, std::ios::out);

	out << "{";
	for (int i = 0; i<size; i++)
	{
		out << "{";
		for (int j = 0; j<size; j++)
		{
			if (j == size - 1)
				out << matrix[i][j] << "}";
			else
				out << matrix[i][j] << ",";
		}
		if (i<size - 1)
			out << ",";
	}
	out << "}";
	out.close();
}

int matrixNodes::getElem(int i, int j)
{
	if (i >= 0 && i < size&&j >= 0 && j < size)
		return matrix[i][j];
	else
		return -1;
}

int matrixNodes::getSize()
{
	return size;
}

int ** matrixNodes::getMatrix() 
{
	return matrix;
}