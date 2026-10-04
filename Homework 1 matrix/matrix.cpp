#include <iostream>
#include <exception>

void print_matrix(int** matrix, size_t m, size_t n);
void print_transpose_matrix(int** matrix, size_t m, size_t n);

int main() 
{
    try {
        size_t m = 0, n = 0;
        std::cout << "Write strokes and columns count: ";
        std::cin >> m >> n;
        std::cout << std::endl;
        if (std::cin.fail()) {
            std::cerr << "Inccorect input m&n" << std::endl;
            return 1;
        }
        int** matrix = new int*[m];
        for (size_t i = 0; i < m; i++) {
            std::cout << "Write " << i+1 << " stroke digits: ";
            matrix[i] = new int[n];
            for (size_t j = 0; j < n; j++) {
                std::cin >> matrix[i][j];
                if (std::cin.fail()) {
                    std::cerr << "Inccorect digit" << std::endl;
                    return 1;
                }
            }
            std::cout << std::endl;
        }

        std::cout << "Matrix: " << std::endl;
        print_matrix(matrix, m, n);
        std::cout << "Transpose matrix: " << std::endl;
        print_transpose_matrix(matrix, m, n);

        delete[] matrix;
    } catch (const std::bad_alloc& e) {
        std::cerr << "Allocate error: " << e.what() << std::endl;
    }
    return 0;
}

void print_matrix(int** matrix, size_t m, size_t n)
{
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            std::cout << matrix[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

void print_transpose_matrix(int** matrix, size_t m, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            std::cout << matrix[j][i] << "  ";
        }
        std::cout << std::endl;
    }
}