#include"matrix.h"

int main()
{
	srand(time(0));
	std::vector<My::Matrix<int>> M(rand() % 8);
	for (int i = 0; i < M.size(); i++)
	{
		My::Matrix<int> m;
		m.generate(i + 2, i + 2);
		M[i] = m;
		M[i].output();
		M[i].output(std::to_string(i) + ".txt");
		std::cout << std::endl << M[i].determinant() << std::endl;
	}


	return 0;
}