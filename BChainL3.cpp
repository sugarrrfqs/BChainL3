#include <iostream>
#include <omp.h>
//#pragma omp single 

int det (int m[3][3])
{
    return (m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] + m[0][2] * m[1][0] * m[2][1]) 
         - (m[0][2] * m[1][1] * m[2][0] + m[0][0] * m[1][2] * m[2][1] + m[0][1] * m[1][0] * m[2][2]);
}
int main()
{
    /*
        2x - 2y +  z = -3
         x + 3y - 2z =  1
        3x -  y -  z =  2
    */
    int m[3][4] = {{2, -2, 1, -3}, {1, 3, -2, 1}, {3, -1, -1, 2}};
    int md[4][3][3];
    int d[4];
    double x[3];

    int i, j;

	#pragma omp parallel shared (m, md)
	{
		#pragma omp for
		for (int i = 0; i <= 2; i++)
		{
			for (int j = 0; j <= 2; j++)
			{
				md[0][i][j] = m[i][j];
			}
		}

		#pragma omp for 
		for (int i = 0; i <= 2; i++)
		{
			for (int j = 0; j <= 2; j++)
			{
				if (j != 0) md[1][i][j] = m[i][j];
				else md[1][i][j] = m[i][3];
			}
		}

		#pragma omp for 
		for (int i = 0; i <= 2; i++)
		{
			for (int j = 0; j <= 2; j++)
			{
				if (j != 1) md[2][i][j] = m[i][j];
				else md[2][i][j] = m[i][3];
			}
		}

		#pragma omp for 
		for (int i = 0; i <= 2; i++)
		{
			for (int j = 0; j <= 2; j++)
			{
				if (j != 2) md[3][i][j] = m[i][j];
				else md[3][i][j] = m[i][3];
			}
		}
	}
	#pragma omp for
	for (int i = 0; i <= 3; i++) d[i] = det(md[i]);

	#pragma omp for
	for (int i = 0; i <= 2; i++) x[i] = (double)d[i + 1] / (double)d[0];



    for (int i = 0; i < 4; i++)
    {
        std::cout << "d" << i << " = " << d[i] << "\n";
    }
    std::cout << "\n";
    for (int i = 0; i < 3; i++)
    {
        std::cout << "X" << i + 1 << " = " << x[i] << "\n";
    }
}
