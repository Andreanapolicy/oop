#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>

#define MATRIX_ROW 3
#define MATRIX_COLUMN 3

typedef double Matrix[MATRIX_ROW][MATRIX_COLUMN];

bool IsNumber(const double ch);
void GetMatrix(std::string& inputPath, Matrix& matrix);
void ReadMatrix(std::ifstream& inputFile, Matrix& matrix);
void OutputMatrix(Matrix& matrix);
void InvertMatrix(Matrix& matrix, Matrix& invertedMatrix);
double GetDeterminant(Matrix& matrix);
void TransposeMatrix(Matrix& matrix, Matrix& transposedMatrix);
void Get—omplementMatrix(Matrix& matrix, Matrix& complementMatrix);
void MultiplyMatrixAndNumber(Matrix& matrix, double number, Matrix& resultMatrix);

struct Args
{
	std::string inputPath;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		return std::nullopt;
	}

	return { { argv[1] } };
}

bool IsNumber(const double ch)
{
	return ch >= 0 && ch <= 9;
}

void GetMatrix(std::string& inputPath, Matrix& matrix)
{
	std::ifstream inputFile;
	inputFile.open(inputPath);

	if (!inputFile.is_open())
	{
		throw std::invalid_argument("Input file does not open");
	}

	ReadMatrix(inputFile, matrix);
}

void ReadMatrix(std::ifstream& inputFile, Matrix& matrix)
{
	double number;
	for (int matrixRow = 0; matrixRow < MATRIX_ROW; matrixRow++)
	{
		for (int matrixColumn = 0; matrixColumn < MATRIX_COLUMN; matrixColumn++)
		{
			if (!(inputFile >> number) && IsNumber(number))
			{
				throw std::invalid_argument("Wrong matrix");
			}

			matrix[matrixRow][matrixColumn] = number;
		}
	}
}

void OutputMatrix(Matrix& matrix)
{
	for (int matrixRow = 0; matrixRow < MATRIX_ROW; matrixRow++)
	{
		for (int matrixColumn = 0; matrixColumn < MATRIX_COLUMN; matrixColumn++)
		{
			std::cout << "    " << std::fixed << std::setprecision(3) << matrix[matrixRow][matrixColumn];
		}

		std::cout << std::endl;
	}
}

void InvertMatrix(Matrix& matrix, Matrix& invertedMatrix)
{
	double determinant = GetDeterminant(matrix);
	if (determinant == 0)
	{
		throw std::runtime_error("There is no inverse matrix. Determinant is 0");
	}

	Matrix complementMatrix;

	Get—omplementMatrix(matrix, complementMatrix);

	Matrix transposedMatrix;
	TransposeMatrix(complementMatrix, transposedMatrix);

	MultiplyMatrixAndNumber(transposedMatrix, 1 / (determinant), invertedMatrix);
}

double GetDeterminant(Matrix& matrix)
{
	return matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0] + matrix[0][2] * matrix[1][0] * matrix[2][1] - matrix[0][2] * matrix[1][1] * matrix[2][0] - matrix[0][1] * matrix[1][0] * matrix[2][2] - matrix[0][0] * matrix[1][2] * matrix[2][1];
}

void TransposeMatrix(Matrix& matrix, Matrix& transposedMatrix)
{
	for (int matrixRow = 0; matrixRow < MATRIX_ROW; matrixRow++)
	{
		for (int matrixColumn = 0; matrixColumn < MATRIX_COLUMN; matrixColumn++)
		{
			transposedMatrix[matrixRow][matrixColumn] = matrix[matrixColumn][matrixRow];
		}
	}
}

void Get—omplementMatrix(Matrix& matrix, Matrix& complementMatrix)
{
	double minor;
	for (int matrixRow = 0; matrixRow < MATRIX_ROW; matrixRow++)
	{
		for (int matrixColumn = 0; matrixColumn < MATRIX_COLUMN; matrixColumn++)
		{
			minor = matrix[matrixRow][matrixColumn] * matrix[(matrixRow + 1) % 3][(matrixColumn + 1) % 3] - matrix[matrixRow][(matrixColumn + 1) % 3] * matrix[(matrixRow + 1) % 3][matrixColumn];
			complementMatrix[(matrixRow + 2) % 3][(matrixColumn + 2) % 3] = minor;
		}
	}
}

void MultiplyMatrixAndNumber(Matrix& matrix, double number, Matrix& resultMatrix)
{
	for (int matrixRow = 0; matrixRow < MATRIX_ROW; matrixRow++)
	{
		for (int matrixColumn = 0; matrixColumn < MATRIX_COLUMN; matrixColumn++)
		{
			resultMatrix[matrixRow][matrixColumn] = matrix[matrixRow][matrixColumn] * number;
		}
	}
}

int main(int argc, char* argv[])
{
	std::optional<Args> args;

	args = ParseArgs(argc, argv);
	if (!args.has_value())
	{
		std::cout << "Wrond input. Params should be: radix.exe <matrix file>" << std::endl;
		return 1;
	}

	try
	{
		Matrix matrix;
		Matrix invertedMatrix;

		GetMatrix(args->inputPath, matrix);
		InvertMatrix(matrix, invertedMatrix);
		OutputMatrix(invertedMatrix);
	}
	catch (const std::exception& error)
	{
		std::cout << error.what() << std::endl;
		return 1;
	}

	return 0;
}
