#include "Matrix.h"

#include <stdio.h>
#include <stdlib.h>
typedef struct Matrix {
    double** arr;
    int heigth;
    int width;
}Matrix;

/**
 * @brief Creates a new matrix of a given height an width,
 *  all values are initially zeroes.
 *
 * @param[out] matrix The address of a matrix pointer to receive
 *  the address of the created matrix.
 * @param[in] height Height of the matrix
 * @param[in] width Width of the matrix
 * @return ErrorCode
 */
ErrorCode matrix_create(PMatrix* matrix, uint32_t height, uint32_t width) {
    //allocating a new PMatrix
    PMatrix pm = (PMatrix)malloc(sizeof(Matrix));
    if(pm == NULL) {
        printf("%s",error_getErrorMessage(ERROR_ALLOCATION));
        return ERROR_ALLOCATION;
    }
    pm->width = width;
    pm->heigth = height;
    //allocating the pointer array
    pm->arr = (double**)malloc(sizeof(double*) * height);
    if(pm->arr == NULL) {
        printf("%s",error_getErrorMessage(ERROR_ALLOCATION));
        return ERROR_ALLOCATION;
    }
    int i;
    for (i=0;i<height;++i) {
        //allocating each array
        (pm->arr)[i] = (double*)calloc(sizeof(double),width);
        if((pm->arr)[i] == NULL) {
            printf("%s",error_getErrorMessage(ERROR_ALLOCATION));
            return ERROR_ALLOCATION;
        }
    }
    *matrix = pm;
    return ERROR_SUCCESS;
}

/**
 * @brief Creates a new matrix from an old matrix.
 *
 * @param[out] matrix The address of a matrix pointer to receive
 *  the address of the copied matrix.
 * @param[in] source The matrix to copy.
 * @return ErrorCode
 */
ErrorCode matrix_copy(PMatrix* result, CPMatrix source){
    if(source == NULL){
        printf("%s",error_getErrorMessage(ERROR_NULL_POINTER));
        return ERROR_NULL_POINTER;
    }
    PMatrix r;
    //creates a new matrix
    ErrorCode e = matrix_create(&r,source->heigth,source->width);
    if(!error_isSuccess(e)){
        printf("%s",error_getErrorMessage(e));
        return e;
    }
    int i,j;
    //copying the 2D array
    for (i=0;i<source->heigth;++i) {
        for (j=0;j<source->width;++j) {
            (r->arr)[i][j] = (source->arr)[i][j];
        }
    }
    *result = r;
    return ERROR_SUCCESS;
}

/**
 * @brief Destroys a matrix.
 *
 * @param matrix the matrix to destroy.
 */
void matrix_destroy(PMatrix matrix) {
    if(matrix != NULL) {
        int x;
        //deallocate all arrays
        for (x=0;x<matrix->heigth;++x){
            free(matrix->arr[x]);
        }
        //deallocates the array of pointers and the matrix
        free(matrix->arr);
        free(matrix);
    }
}

/**
 * @brief Returns the height of a give matrix.
 *
 * @param[in] matrix The matrix.
 * @param[out] result On output, contains the height of the matrix.
 * @return ErrorCode
 */
ErrorCode matrix_getHeight(CPMatrix matrix, uint32_t* result) {
    if(matrix == NULL) {
        printf("%s",error_getErrorMessage(ERROR_NULL_POINTER));
        return ERROR_NULL_POINTER;
    }
    *result = matrix->heigth;
    return ERROR_SUCCESS;
}

/**
 * @brief Returns the width of a give matrix.
 *
 * @param[in] matrix The matrix.
 * @param[out] result On output, contains the height of the matrix.
 * @return ErrorCode
 */
ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t* result) {
    if(matrix == NULL) {
        printf("%s",error_getErrorMessage(ERROR_NULL_POINTER));
        return ERROR_NULL_POINTER;
    }
    *result = matrix->width;
    return ERROR_SUCCESS;
}

/**
 * @brief Sets a value to the matrix.
 *
 * @param[in, out] matrix The matrix to operate on.
 * @param[in] rowIndex Row index of the value to set.
 * @param[in] colIndex Column index of the value to setF.
 * @param[in] value Value to set.
 * @return ErrorCode
 */
ErrorCode matrix_setValue(PMatrix matrix, uint32_t rowIndex, uint32_t colIndex, double value) {
    if(matrix == NULL || matrix->arr == NULL) {
        printf("%s",error_getErrorMessage(ERROR_NULL_POINTER));
        return ERROR_NULL_POINTER;
    }
    //if the index's doesn't fit the bounds of the matrix
    if(rowIndex >= matrix->heigth || colIndex >= matrix->width) {
        printf("%s",error_getErrorMessage(ERROR_INDEX_OUT_OF_BOUND));
        return ERROR_INDEX_OUT_OF_BOUND;
    }
    matrix->arr[rowIndex][colIndex] = value;
    return ERROR_SUCCESS;
}

/**
 * @brief Sets a value to the matrix.
 *
 * @param[in] matrix The matrix to operate on.
 * @param[in] rowIndex Row index of the value to get.
 * @param[in] colIndex Column index of the value to get.
 * @param[out] value The address of a double variable to receive
 *  the value from the matrix.
 * @return ErrorCode
 */
ErrorCode matrix_getValue(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex, double* value) {
    if(matrix == NULL || matrix->arr == NULL) {
        printf("%s",error_getErrorMessage(ERROR_NULL_POINTER));
        return ERROR_NULL_POINTER;
    }
    //if the index's doesn't fit the bounds of the matrix
    if(rowIndex >= matrix->heigth || colIndex >= matrix->width) {
        printf("%s",error_getErrorMessage(ERROR_INDEX_OUT_OF_BOUND));
        return ERROR_INDEX_OUT_OF_BOUND;
    }
    *value = matrix->arr[rowIndex][colIndex];
    return ERROR_SUCCESS;
}

/**
 * @brief Computes the addition of two matrices.
 *
 * @param[out] result The address of a matrix pointer to receive
 *  the address of the resulting matrix.
 * @param[in] lhs The left hand side of the addition operation.
 * @param[in] rhs The right hand side of the addition operation.
 * @return ErrorCode
 */
ErrorCode matrix_add(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
    PMatrix res;
    if(lhs->heigth != rhs->heigth || lhs->width != rhs->width) {
        printf("%s",error_getErrorMessage(ERROR_MATRIX_SIZE_INCOMPATIBLE));
        return ERROR_MATRIX_SIZE_INCOMPATIBLE;
    }
    matrix_create(&res,lhs->heigth,lhs->width);    
    int i,j;
    for (i=0;i<lhs->heigth;++i) {
        for (j=0;j<lhs->width;++j) {
            (res->arr)[i][j] = (lhs->arr)[i][j] + (rhs->arr)[i][j];
        }
    }
    *result = res;
    return ERROR_SUCCESS;
}

/**
 * @brief Computes the multiplication of two matrices.
 *
 * @param[out] result The address of a matrix pointer to receive
 *  the address of the resulting matrix.
 * @param[in] lhs The left hand side of the multiplication operation.
 * @param[in] rhs The right hand side of the multiplication operation.
 * @return ErrorCode
 */
ErrorCode matrix_multiplyMatrices(PMatrix* result, CPMatrix lhs, CPMatrix rhs){
    PMatrix res;
    if(lhs->width != rhs->heigth){
        printf("%s",error_getErrorMessage(ERROR_MATRIX_SIZE_INCOMPATIBLE));
        return ERROR_MATRIX_SIZE_INCOMPATIBLE;
    }
    if(result == NULL){
        matrix_create(result,lhs->heigth,lhs->width);
    }
    matrix_create(&res,lhs->heigth,rhs->width);
    int i,j,k;
    for (i=0;i<lhs->heigth;++i) {
        for (j=0;j<rhs->width;++j) {
            //matrix multiplication definition
            for(k=0;k<lhs->width;++k) {
                (res->arr)[i][j] += (lhs->arr)[i][k] * (rhs->arr)[k][j];
            }
        }
    }
    *result = res;
    return ERROR_SUCCESS;
}

/**
 * @brief Multiplies a matrix with a scalar and stores the result in
 *  the given matrix.
 *
 * @param[in, out] matrix On input, the matrix to multiply with a scalar.
 *  On output, the result of the multiplication operation.
 * @param[in] scalar The scalar to multiply with.
 * @return ErrorCode
 */
ErrorCode matrix_multiplyWithScalar(PMatrix matrix, double scalar){
    if(matrix == NULL || matrix->arr == NULL){
        printf("%s",error_getErrorMessage(ERROR_NULL_POINTER));
        return ERROR_NULL_POINTER;
    }
    int i,j;
    for (i=0;i<matrix->heigth;++i) {
        for (j=0;j<matrix->width;++j) {
            (matrix->arr)[i][j] = (matrix->arr)[i][j] * scalar;
        }
    }
    return ERROR_SUCCESS;
}