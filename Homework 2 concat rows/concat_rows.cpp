#include <iostream>
#include <exception>

const int exit_code_invalid_argument = 1;
const int exit_code_allocate_error = 2;
const int exit_code_good = 0;

int** input_matrix(size_t* n, size_t* m);
void print_matrix(const int * const * matrix, size_t n, size_t m);
void better_print_matrix(const int * const * matrix, size_t n1, size_t m1, size_t n2, size_t m2);
int* concat_arrays(const int * arr1, size_t s1, const int * arr2, size_t s2);
int* copy_array(const int * arr, size_t s);
int min(int n1, int n2);
int min(int n1, int out1, int n2, int out2);
int max(int n1, int n2);
int max(int n1, int out1, int n2, int out2);
int** concat_rows(const int * const * lhs, size_t n1, size_t m1, 
    const int * const * rhs, size_t n2, size_t m2);

int main()
{
    try {
        size_t n1 = 0, m1 = 0;
        int** matrix_a = input_matrix(&n1, &m1);
        size_t n2 = 0, m2 = 0;
        int** matrix_b = input_matrix(&n2, &m2);

        int** concated_matrix = concat_rows(matrix_a, n1, m1, matrix_b, n2, m2);
        better_print_matrix(concated_matrix, min(n1, n2), m1+m2, max(n1, n2), max(n1, m1, n2, m2));
        for (size_t i = 0; i < max(n1, n2); i++) delete[] concated_matrix[i];
        delete[] concated_matrix;
        
        for (size_t i = 0; i < n1; i++) delete[] matrix_a[i];
        delete[] matrix_a;
        for (size_t i = 0; i < n2; i++) delete[] matrix_b[i];
        delete[] matrix_b;
    } catch (const std::bad_alloc& e) {
        std::cerr << "Allocate error: " << e.what() << std::endl;
        return exit_code_allocate_error;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        return exit_code_invalid_argument;
    }
    return exit_code_good;
}

int** input_matrix(size_t* n, size_t* m)
{
    std::cout << "Write rows and columns count: ";
    std::cin >> *n >> *m;
    std::cout << std::endl;
    if (std::cin.fail() || *m == 0 || *n == 0) {
        throw std::invalid_argument("incorrect m&n");
    }
    int** matrix = new int*[*n];
    for (size_t i = 0; i < *n; i++) {
        try {
            std::cout << "Write " << i+1 << " stroke digits: ";
            matrix[i] = new int[*m];
            for (size_t j = 0; j < *m; j++) {
                std::cin >> matrix[i][j];
                if (std::cin.fail()) {
                    for (size_t k = 0; k < i; k++) delete[] matrix[k];
                    delete[] matrix;
                    throw std::invalid_argument("incorrect digits");
                }
            }
        } catch (const std::bad_alloc& e) {
            for (size_t k = 0; k < i; k++) delete[] matrix[k];
            delete[] matrix;
            throw;
        }
        std::cout << std::endl;
    }
    return matrix;
}

void print_matrix(const int * const * matrix, size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            std::cout << matrix[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

void better_print_matrix(const int * const * matrix, size_t n1, size_t m1, size_t n2, size_t m2)
{
    for (size_t i = 0; i < n1; i++) {
        for (size_t j = 0; j < m1; j++) {
            std::cout << matrix[i][j] << "  ";
        }
        std::cout << std::endl;
    }
    for (size_t i = n1; i < n2; i++) {
        for (size_t j = 0; j < m2; j++) {
            std::cout << matrix[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

int* concat_arrays(const int * arr1, size_t s1, const int * arr2, size_t s2)
{
    int* res = new int[s1+s2];
    for (size_t i = 0; i < s1; i++) {
        res[i] = arr1[i];
    }
    for (size_t i = 0; i < s2; i++) {
        res[s1+i] = arr2[i];
    }
    return res;
}

int* copy_array(const int * arr, size_t s)
{
    int* res = new int[s];
    for (size_t i = 0; i < s; i++) {
        res[i] = arr[i];
    }
    return res;
}

int min(int n1, int n2)
{
    if (n1 < n2) {
        return n1;
    }
    return n2;
}

int min(int n1, int out1, int n2, int out2)
{
    if (n1 < n2) {
        return out1;
    }
    return out2;
}

int max(int n1, int n2)
{
    if (n1 < n2) {
        return n2;
    }
    return n1;
}

int max(int n1, int out1, int n2, int out2)
{
    if (n1 < n2) {
        return out2;
    }
    return out1;
}

int** concat_rows(const int * const * lhs, size_t n1, size_t m1, 
    const int * const * rhs, size_t n2, size_t m2)
{
    size_t max_n = max(n1,n2), min_n = min(n1,n2);
    int** res = new int*[max_n];
    for (size_t i = 0; i < min_n; i++) {
        try {
            res[i] = concat_arrays(lhs[i], m1, rhs[i], m2);
        } catch (const std::bad_alloc& e) {
            for (size_t k = 0; k < i; k++) delete[] res[k];
            delete[] res;
            throw;
        }
    }
    for (size_t i = min_n; i < max_n; i++) {
        try {
            if (min_n == n1) {
                res[i] = copy_array(rhs[i], m2); 
            } else {
                res[i] = copy_array(lhs[i], m1);
            }
        } catch (const std::bad_alloc& e) {
            for (size_t k = 0; k < i; i++) delete[] res[k];
            delete[] res;
            throw;
        }
    }
    return res;
}