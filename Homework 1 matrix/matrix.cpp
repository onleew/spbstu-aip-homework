#include <iostream>
#include <exception>
#include <iomanip>
#include <limits>

const int int_max = std::numeric_limits<int>::max();
const int exit_code_incorrect_input = 1;
const int exit_code_allocate_error = 2;
const int exit_code_good = 0;

void print_matrix(const int * const * matrix, size_t m, size_t n);
int** generate_transpose_matrix(const int * const * matrix, size_t m, size_t n);
unsigned get_matrix_max_num_length(const int * const * matrix, size_t m, size_t n);

int main()
{
    try {
        size_t m = 0, n = 0;
        std::cout << "Write strokes and columns count: ";
        std::cin >> m >> n;
        std::cout << std::endl;
        if (std::cin.fail() || m == 0 || n == 0) {
            std::cerr << "Inccorect input m&n" << std::endl;
            return exit_code_incorrect_input;
        }
        int** matrix = new int*[m];
        for (size_t i = 0; i < m; i++) {
            try {
                std::cout << "Write " << i+1 << " stroke digits: ";
                matrix[i] = new int[n];
                for (size_t j = 0; j < n; j++) {
                    std::cin >> matrix[i][j];
                    if (std::cin.fail()) {
                        std::cerr << "Inccorect digits" << std::endl;
                        for (size_t k = 0; k < i; k++) delete[] matrix[k];
                        delete[] matrix;
                        return exit_code_incorrect_input;
                    }
                }
            } catch (const std::bad_alloc& e) {
                std::cerr << "Allocate error: " << e.what() << std::endl;
                delete[] matrix;
                return exit_code_allocate_error;
            }
            std::cout << std::endl;
        }

        std::cout << "Matrix: " << std::endl;
        print_matrix(matrix, m, n);
        std::cout << "Transpose matrix: " << std::endl;
        int** transpose_matrix = generate_transpose_matrix(matrix, m, n);
        print_matrix(transpose_matrix, n, m);

        for (size_t i = 0; i < m; i++) delete[] matrix[i];
        delete[] matrix;
        for (size_t i = 0; i < n; i++) delete[] transpose_matrix[i];
        delete[] transpose_matrix;
    } catch (const std::bad_alloc& e) {
        std::cerr << "Allocate error: " << e.what() << std::endl;
        return exit_code_allocate_error;
    }
    return exit_code_good;
}

void print_matrix(const int * const * matrix, size_t m, size_t n)
{
    unsigned max_num_leght = get_matrix_max_num_length(matrix, m, n);
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            std::cout << std::setw(max_num_leght) << std::left << matrix[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

int** generate_transpose_matrix(const int * const * matrix, size_t m, size_t n)
{
    int** transpose_matrix = new int*[n];
    for (size_t i = 0; i < n; i++) {
        try {
            transpose_matrix[i] = new int[m];
            for (size_t j = 0; j < m; j++) {
                transpose_matrix[i][j] = matrix[j][i];
            }
        } catch (const std::bad_alloc& e) {
            for (size_t k = 0; k < i; k++) delete[] transpose_matrix[k];
            delete[] transpose_matrix;
            throw;
        }
    }
    return transpose_matrix;
}

unsigned get_matrix_max_num_length(const int * const * matrix, size_t m, size_t n)
{
    unsigned res = 1;
    int max_10_pow_k = 10;
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            int cur_num = matrix[i][j];
            if (cur_num < 0) {
                cur_num *= -10;
            }
            while (cur_num >= max_10_pow_k) {
                if (max_10_pow_k > int_max / 10) {
                    return res+1;
                }
                max_10_pow_k *= 10;
                res++;
            }
        }
    }
    return res;
}
