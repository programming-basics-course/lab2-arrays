// Laboratory Work #2 (2nd semester) (NOT IMPROVED)

/*

	Author:		Novokhatnii Vlas
	Group:		PZ-18-1 (2nd subgroup)

	Problem:	Shift element of a matrix, to the left, right, down or up,
				by some positive number.

*/


#include <iostream>
#include <string>


enum STR2_ERROR { SUCCESS, OVERFLOW_, UNDERFLOW_, INCONVERTIBLE };
STR2_ERROR str2int(int& i, char const* s, int base);

void elements_shift_pp(double** matrix, int rows, int cols, char direction, int shift);
void elements_shift_p(double* arr, int rows, int cols, char direction, int shift);

int main(void)
{
	// Enter information the size of a matrix and array and shifting

	char str_input[20];

	int rows;
	do
	{
		std::cout << "Enter a number of rows in the matrix: ";
		std::cin >> str_input;
	} while (str2int(rows, str_input, 0) != SUCCESS || rows <= 0);

	int cols;
	do
	{
		std::cout << "Enter a number of colomns in the matrix: ";
		std::cin >> str_input;
	} while (str2int(cols, str_input, 0) != SUCCESS || cols <= 0);

	char direction;
	do
	{
		std::cout << "Enter a direcion of a shift (u, d, l, r for up, down, left and right):";
		std::cin.clear();
		std::cin.ignore(1024, '\n');
		std::cin >> direction;
	} while (std::cin.fail() || (direction != 'u' && direction != 'd' && direction != 'l' && direction != 'r'));

	int shift;
	do
	{
		std::cout << "Enter the shift: ";
		std::cin >> str_input;
	} while (str2int(shift, str_input, 0) != SUCCESS || shift <= 0);



	/*
		For a matrix
	*/

	double** matrix = new double* [rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new double[cols];
	}

	// prompt user for the matrix values
	std::cout << "Enter the matrix values:\n";
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			std::cin >> matrix[i][j];
			// parsing check
		}
	}
	std::cout << "\n\n";

	// call of the shifting function
	elements_shift_pp(matrix, rows, cols, direction, shift);

	// print the changed matrix out
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "\n\n";




	/*
		For an 1D array
	*/
	//(with the same parameters as in the matrix case)

	int arr_size = rows * cols;
	double* arr = new double[arr_size];

	// prompt user for the array's values
	std::cout << "Enter the array's values:\n";
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			std::cin >> arr[i * rows + j];
			// parsing check
		}
	}
	std::cout << "\n\n";

	// call of the shifting function
	elements_shift_p(arr, rows, cols, direction, shift);

	// print out the array
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			std::cout << arr[i * rows + j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "\n\n";




	// free memory
	delete[] arr;

	for (int i = 0; i < rows; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;

	system("pause");
	return 0;
}

STR2_ERROR str2int(int& i, char const* s, int base = 0)
{
	char* end;
	long  l;
	errno = 0;
	l = strtol(s, &end, base);
	if ((errno == ERANGE && l == LONG_MAX) || l > INT_MAX) {
		return OVERFLOW_;
	}
	if ((errno == ERANGE && l == LONG_MIN) || l < INT_MIN) {
		return UNDERFLOW_;
	}
	if (*s == '\0' || *end != '\0') {
		return INCONVERTIBLE;
	}
	i = l;
	return SUCCESS;
}


// shifting functions
void elements_shift_pp(double** matrix, int rows, int cols, char direction, int shift)
{

	if (direction == 'r' || direction == 'l')
	{

		shift = shift % cols;

		if (shift == 0)
			return;

		if (direction == 'l')
			shift = cols - shift;


		double* buffer = new double[shift];

		for (int i = 0; i < rows; i++)
		{
			// save "fallen out" elements
			for (int j = 0; j < shift; j++)
				buffer[j] = matrix[i][cols - shift + j];

			// shifting elements 
			for (int j = 0; (cols - 1 - j - shift) >= 0; j++)
				matrix[i][cols - 1 - j] = matrix[i][cols - 1 - j - shift];

			// add elements that have "fallen out"
			for (int j = 0; j < shift; j++)
				matrix[i][j] = buffer[j];
		}

		delete[] buffer;
	}
	else
	{
		shift = shift % rows;

		if (shift == 0)
			return;

		if (direction == 'u')
			shift = rows - shift;

		double** pbuffer = new double* [shift];

		// save pointers to "fallen out" elements
		for (int i = 0; i < shift; i++)
			pbuffer[i] = matrix[rows - shift + i];

		// rearrange pointers 
		for (int i = 0; (rows - 1 - i - shift) >= 0; i++)
			matrix[rows - 1 - i] = matrix[rows - 1 - i - shift];

		// use the buffer
		for (int i = 0; i < shift; i++)
			matrix[i] = pbuffer[i];

		delete[] pbuffer;
	}


}
void elements_shift_p(double* arr, int rows, int cols, char direction, int shift)
{
	if (direction == 'r' || direction == 'l')
	{

		shift = shift % cols;

		if (shift == 0)
			return;

		if (direction == 'l')
			shift = cols - shift;


		double* buffer = new double[shift];

		for (int i = 0; i < rows; i++)
		{
			// save "fallen out" elements
			for (int j = 0; j < shift; j++)
				buffer[j] = arr[i * rows + (cols - shift + j)];

			// shifting elements 
			for (int j = 0; ((int)cols - 1 - (int)j - shift) >= 0; j++)
				arr[i * rows + (cols - 1 - j)] = arr[i * rows + (cols - 1 - j - shift)];

			// add elements that have "fallen out"
			for (int j = 0; j < shift; j++)
				arr[i * rows + j] = buffer[j];
		}

		delete[] buffer;
	}
	else
	{

		shift = shift % rows;

		if (shift == 0)
			return;

		if (direction == 'u')
			shift = cols - shift;


		double* buffer = new double[shift];

		for (int i = 0; i < cols; i++)
		{
			// save "fallen out" elements
			for (int j = 0; j < shift; j++)
				buffer[j] = arr[(rows - shift + j) * rows + i];

			// shifting elements 
			for (int j = 0; ((int)rows - 1 - (int)j - shift) >= 0; j++)
				arr[(rows - 1 - j) * rows + i] = arr[(rows - 1 - j - shift) * rows + i];

			// add elements that have "fallen out"
			for (int j = 0; j < shift; j++)
				arr[j * rows + i] = buffer[j];
		}

		delete[] buffer;

	}


}
