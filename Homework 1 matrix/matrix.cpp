#include <iostream>
#include <exception>
#include <iomanip>

void print_matrix(const int * const * matrix, size_t m, size_t n);
int** generate_transpose_matrix(const int * const * matrix, size_t m, size_t n);
int get_matrix_max_abs_element(const int * const * matrix, size_t m, size_t n);
unsigned get_matrix_max_num_length(const int * const * matrix, size_t m, size_t n);

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
            try {
                std::cout << "Write " << i+1 << " stroke digits: ";
                matrix[i] = new int[n];
                for (size_t j = 0; j < n; j++) {
                    std::cin >> matrix[i][j];
                    if (std::cin.fail()) {
                        std::cerr << "Inccorect digit" << std::endl;
                        for (size_t k = 0; k < i; k++) delete[] matrix[k];
                        delete[] matrix;
                        return 1;
                    }
                }
            } catch (const std::bad_alloc& e) {
                std::cerr << "Allocate error: " << e.what() << std::endl;
                delete[] matrix;
                return 2;
            }
            std::cout << std::endl;
        }

        std::cout << "Matrix: " << std::endl;
        print_matrix(matrix, m, n);
        std::cout << "Transpose matrix: " << std::endl;
        int** transpose_matrix = generate_transpose_matrix(matrix, m, n);
        print_matrix(transpose_matrix, n, m);

        delete[] transpose_matrix;
        delete[] matrix;
    } catch (const std::bad_alloc& e) {
        std::cerr << "Allocate error: " << e.what() << std::endl;
        return 2;
    }
    return 0;
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

int get_matrix_max_abs_element(const int * const * matrix, size_t m, size_t n)
{
    int abs_res = 0;
    int res = 0;
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            if (matrix[i][j] > abs_res || -matrix[i][j] > abs_res) {
                res = matrix[i][j];
                if (res < 0) {
                    abs_res = -res;
                } else {
                    abs_res = res;
                }
            }
        }
    }
    return res;
}

unsigned get_matrix_max_num_length(const int * const * matrix, size_t m, size_t n)
{
    unsigned res = 1;
    int max_abs_elem = get_matrix_max_abs_element(matrix, m, n);
    unsigned cur_num = 10;
    while ((max_abs_elem > 0 && cur_num <= max_abs_elem) || (max_abs_elem < 0 && cur_num <= -max_abs_elem)) {
        cur_num *= 10;
        res++;
    }
    if (max_abs_elem < 0) {
        res++;
    }
    return res;
}
