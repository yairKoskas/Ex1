#include "Matrix.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct Matrix {
    uint32_t heigth;
    uint32_t width;
    double* arr[];
}Matrix;

ErrorCode matrix_create(PMatrix* matrix, uint32_t height, uint32_t width) {
    //allocating a new PMatrix
    PMatrix pm = (PMatrix)malloc(sizeof(Matrix));
    if(pm == NULL) {
        return ERROR_ALLOCATION;
    }
    pm->width = width;
    pm->heigth = height;
    for (uint32_t i = 0; i < height; ++i ) {
        //allocating each array
        (pm->arr)[i] = (double*)calloc(sizeof(double),width);
        if((pm->arr)[i] == NULL) {
            return ERROR_ALLOCATION;
        }
    }
    *matrix = pm;
    return ERROR_SUCCESS;
}

ErrorCode matrix_copy(PMatrix* result, CPMatrix source){
    if(source == NULL){
        return ERROR_NULL_POINTER;
    }
    PMatrix r;
    ErrorCode e = matrix_create(&r,source->heigth,source->width);
    if(!error_isSuccess(e)){
        return e;
    }
    //copying the 2D array
    for (int i = 0 ;i < source->heigth ; ++i ) {
        for (int j = 0 ;j < source->width ; ++j ) {
            (r->arr)[i][j] = (source->arr)[i][j];
        }
    }
    *result = r;
    return ERROR_SUCCESS;
}

void matrix_destroy(PMatrix matrix) {
    if(matrix != NULL) {
        //deallocate all arrays
        for (int x = 0 ; x < matrix->heigth ; ++x){
            free(matrix->arr[x]);
        }
        //deallocates the array of pointers and the matrix
        free(matrix->arr);
        free(matrix);
    }
}

ErrorCode matrix_getHeight(CPMatrix matrix, uint32_t* result) {
    if(matrix == NULL) {
        return ERROR_NULL_POINTER;
    }
    *result = matrix->heigth;
    return ERROR_SUCCESS;
}

ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t* result) {
    if(matrix == NULL) {
        return ERROR_NULL_POINTER;
    }
    *result = matrix->width;
    return ERROR_SUCCESS;
}

ErrorCode matrix_setValue(PMatrix matrix, uint32_t rowIndex, uint32_t colIndex, double value) {
    if(matrix == NULL) {
        return ERROR_NULL_POINTER;
    }
    //if the index's doesn't fit the bounds of the matrix
    if(rowIndex >= matrix->heigth || colIndex >= matrix->width) {
        return ERROR_INDEX_OUT_OF_BOUND;
    }
    matrix->arr[rowIndex][colIndex] = value;
    return ERROR_SUCCESS;
}

ErrorCode matrix_getValue(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex, double* value) {
    if(matrix == NULL) {
        return ERROR_NULL_POINTER;
    }
    //if the index's doesn't fit the bounds of the matrix
    if(rowIndex >= matrix->heigth || colIndex >= matrix->width) {
        return ERROR_INDEX_OUT_OF_BOUND;
    }
    *value = matrix->arr[rowIndex][colIndex];
    return ERROR_SUCCESS;
}

ErrorCode matrix_add(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
    PMatrix res;
    if( lhs->heigth != rhs->heigth || lhs->width != rhs->width) {
        return ERROR_MATRIX_SIZE_INCOMPATIBLE;
    }
    ErrorCode e = matrix_create(&res,lhs->heigth,lhs->width);    
    if ( !error_isSuccess(e) ) {
        return e;
    }
    for (int i = 0 ; i < lhs->heigth ; ++i ) {
        for (int j = 0 ; j < lhs->width ; ++j ) {
            (res->arr)[i][j] = (lhs->arr)[i][j] + (rhs->arr)[i][j];
        }
    }
    *result = res;
    return ERROR_SUCCESS;
}

ErrorCode matrix_multiplyMatrices(PMatrix* result, CPMatrix lhs, CPMatrix rhs){
    PMatrix res;
    if(lhs->width != rhs->heigth){
        return ERROR_MATRIX_SIZE_INCOMPATIBLE;
    }
    if(result == NULL){
        matrix_create(result,lhs->heigth,lhs->width);
    }
    ErrorCode e = matrix_create(&res,lhs->heigth,rhs->width);    
    if ( !error_isSuccess(e) ) {
        return e;
    }
    for (int i = 0 ; i < lhs->heigth ; ++i ) {
        for (int j = 0 ; j < rhs->width ; ++j ) {
            //matrix multiplication definition
            for(int  k = 0 ; k < lhs->width ; ++k ) {
                (res->arr)[i][j] += (lhs->arr)[i][k] * (rhs->arr)[k][j];
            }
        }
    }
    *result = res;
    return ERROR_SUCCESS;
}

ErrorCode matrix_multiplyWithScalar(PMatrix matrix, double scalar){
    if(matrix == NULL){
        return ERROR_NULL_POINTER;
    }
    for (int i = 0 ; i < matrix->heigth ; ++i) {
        for (int j = 0 ; j < matrix->width ; ++j ) {
            (matrix->arr)[i][j] = (matrix->arr)[i][j] * scalar;
        }
    }
    return ERROR_SUCCESS;
}