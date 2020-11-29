#include "ErrorCode.h"

#include <stdio.h>

/**
 * @brief Checks if a given error code indicates a success or not.
 *
 * @param[in] code the error code.
 * @return whether the error code indicates a success or not.
 */
bool error_isSuccess(ErrorCode code){
    return code == ERROR_SUCCESS;
}

/**
 * @brief gets a textual error message for a given error code.
 *
 * @param[in] code the error code.
 * @return const char* the textual representation of the error code.
 */
const char* error_getErrorMessage(ErrorCode code){
    switch (code)
    {
    case ERROR_SUCCESS:
        return "Success!";
    case ERROR_ALLOCATION:
        return "Error in memory allocation"; 
    case ERROR_INDEX_OUT_OF_BOUND:
        return "Error, Given index isn't legal";
    case ERROR_MATRIX_SIZE_INCOMPATIBLE:
        return "Error, Incompatible matrix' sizes";
    case ERROR_NULL_POINTER:
        return "Error, Given pointer is null";
    default:
        return "Undefined Error";
    }
}