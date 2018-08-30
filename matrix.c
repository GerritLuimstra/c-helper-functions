/*
    Simple implementation of a matrix
    includes:
        - Matrix addition
        - Matrix subtraction
*/

#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
#define boolean int

typedef struct Matrix {
    int rows;
    int cols;
    double* elements;
} Matrix;

// Creates a matrix with a given set of rows and columns
Matrix* m_init (int rows, int cols, double value) {
    Matrix* new = malloc(sizeof(Matrix));
    new->rows = rows;
    new->cols = cols;
    new->elements = calloc(sizeof(double), rows * cols);

    if ( value != 0.0 ) {
        for (int r = 0; r < rows; r++){
            for (int c = 0; c < cols; c++) new->elements[rows * r + c] = value;
        }
    }

    return new;
}


// Determines whether the two given matrices have the same dimensions
boolean m_same_dim (Matrix* A, Matrix* B){
    return ( A->rows == B->rows && A->cols == B->cols );
}

// Matrix addition (Add B to A)
// NOTE: Matrices must have the same number of rows and columns
// NOTE: Does not alter A or B
Matrix* m_add( Matrix* A, Matrix* B ){

    // Test whether the dimensions are the same
    if (!m_same_dim(A, B)) {
        printf("Matrix Addition Failure: Dimensions are not the same!\n");
        return NULL;
    }

    int rows = A->rows;
    int cols = A->cols;

    // Create a new matrix, that will contain the values after addition
    Matrix* C = m_init(rows, cols, 0.0);

    for (int r = 0; r < rows; r++){
        for (int c = 0; c < cols; c++) {
            int curr = rows * r + c;
            double elemA = A->elements[curr];
            double elemB = B->elements[curr];
            C->elements[curr] =  elemA + elemB;
        }
    }

    return C;
}

// Matrix addition (Subtract B from A)
// NOTE: Matrices must have the same number of rows and columns
// NOTE: Does not alter A or B
Matrix* m_sub( Matrix* A, Matrix* B ){

    // Test whether the dimensions are the same
    if (!m_same_dim(A, B)) {
        printf("Matrix Subtraction Failure: Dimensions are not the same!\n");
        return NULL;
    }

    int rows = A->rows;
    int cols = A->cols;

    // Create a new matrix, that will contain the values after addition
    Matrix* C = m_init(rows, cols, 0.0);

    for (int r = 0; r < rows; r++){
        for (int c = 0; c < cols; c++) {
            int curr = rows * r + c;
            double elemA = A->elements[curr];
            double elemB = B->elements[curr];
            C->elements[curr] =  elemA - elemB;
        }
    }

    return C;
}

// Pretty prints the matrices
void m_display ( Matrix* m ) {
    int rows = m->rows;
    int cols = m->cols;

    printf("Displaying matrix at: %p\n", m->elements);
    printf("Rows: %d\n", rows);
    printf("Columns: %d\n", cols);

    for(int i = 0; i < cols; i++) printf("------------");
    printf("\n");

    for (int r = 0; r < rows; r++){
        for (int c = 0; c < cols; c++){
            double value = m->elements[rows * r + c];
            printf("|  %.4f  |", value);
        }
        printf("\n");
    }

    for(int i = 0; i < cols; i++) printf("------------");
    printf("\n\n");
}

// Attempts to destroy the matrix
// (frees up the memory)
void m_destroy ( Matrix* m ) {
    free(m->elements);
    free(m);
}

int main(){
    // Create some simple matrices
    Matrix* A = m_init(2, 3, 5.4);
    Matrix* B = m_init(2, 3, 0.2);

    // Display the matrices
    m_display(A);
    m_display(B);

    // Simple addition
    Matrix* C = m_add(A, B);
    m_display(C);
    m_destroy(C);

    // Simple Subtraction
    C = m_sub(A, B);
    m_display(C);
    m_destroy(C);

    // destroy the matrix, before it does any harm
    m_destroy(A);
    m_destroy(B);
}
