#ifndef HANDY_HEADERS_H
#define HANDY_HEADERS_H

#include <stdio.h> // Includes NULL
#include <stdlib.h> // Includes malloc, realloc, free..
#include <string.h> // Includes memset

// Obtain the number of elements in the given C array
#define GET_ARRAY_LEN(arrayName) (sizeof(arrayName) / sizeof((arrayName)[0]))

/**
 * @brief Delete pointer safely
 * @details Will ensure that a pointer is not deleted twice and sets it
 * to null.
 */
#define SAFE_DELETE(ptr) if(ptr) delete ptr; ptr = nullptr;

// Return the min of two numbers
#define MIN(n1, n2) ((n1) > (n2) ? (n2) : (n1))

// Return max of two numbers
#define MAX(n1, n2) ((n1) > (n2) ? (n1) : (n2))

// Aligns the supplied size to the specified PowerOfTwo
#define ALIGN_SIZE(sizeToAlign, PowerOfTwo) \
    (((sizeToAlign) + (PowerOfTwo) - 1) & ~((PowerOfTwo) - 1))

// Checks whether the supplied size is aligned to the specified power of two
#define IS_SIZE_ALIGNED(sizeToTest, PowerOfTwo) \
    (((sizeToTest) & ((PowerOfTwo) - 1)) == 0)

/////////////////////////////////////////////////////////////
// Struct related MACROS

// Obtain the offset of a field in a struct
#define GET_FIELD_OFFSET(StructName, FieldName) \
    ((short)(long)(&(StructName *)NULL)->FieldName)

// Obtain the struct element of specified offset given the struct ptr
#define GET_FIELD_PTR( pStruct, nOffset) \
    ((void*)(((char*)pStruct) + (nOffSet)))

/**
 * Allocates a structure given the structure name and returns a pointer
 * to that allocated structure
 *
 * The main benefit is there is no need to cast the returned pointer,
 * to the structure type.
 *
 * @param StructName the name of the structure
 * @return pointer to allocated structure is successful, else NULL
 * @see INIT_STRUCT
 *
 */

#define ALLOC_STRUCT(StructName) ((StructName*)malloc(sizeof(StructName)))

/**
 *
 * Initializes the given structure to zeroes using memset()
 *
 * @param pStruct the pointer to the structure that has to be initialized
 * @see ALLOC_STRUCT
 *
 */

#define INIT_STRUCT(pStruct) (memset(pStruct, '\0', sizeof(*(pStruct))))

// Determine whether the given signed or unsigned integer is odd.
#define IS_ODD(num) ((num) & 1)

#define IS_EVEN(num) (!IS_ODD(num))

/**
 * Determine whether the given number is between the other two numbers
 */

#define IS_BETWEEN(numToTest, numLow, numHigh) \
    ((unsigned char)((numToTest) >= (numLow) && (numToTest) <= (numHigh)))

/**
 * Use this macro for unused parameters right in the beggining of a function
 * body to suppress compiler warnings about unused parameters
 *
 * This is mainly meant for function parameters and not for unused local 
 * variables
 *
 */

#define UNUSED(ParamName) \
    ((void)(0 ? ((ParamName) = (ParamName)) : (ParamName)))

/**
 * To open a "C/C++" block without using any construct such as "if", "for",
 * "while", etc.
 *
 * The main purpose is to improve readability and to make the intentions
 * clear in the code
 *
 * This is useful if some local variables are required only for few lines.
 * In such cases putting such local variables in a block causes the local
 * variables to go out of scope and hence reclaim their memory once the end 
 * of block is reached
 *
 */

#define BEGIN_BLOCK {

/**
 * Closes a "C/C++" block opened using BEGIN_BLOCK
 */

#define END_BLOCK }

#endif // HANDY_HEADERS_H
