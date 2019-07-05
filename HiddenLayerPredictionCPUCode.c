/**
 * Document: MaxCompiler Tutorial (maxcompiler-tutorial.pdf)
 * Chapter: 6      Example: 3      Name: Vectors
 * MaxFile name: Vectors
 * Summary:
 *    Streams a vector of integers to the dataflow engine and confirms that the
 *    returned stream contains the integers values doubled.
 */

#include <stdio.h>
#include <stdlib.h>
#include "Maxfiles.h"
#include <MaxSLiCInterface.h>



int check(float * outVector, float * expectedVector)
{
	int status = 1;
	for (int i = 0; i < Vectors_streamSize * Vectors_outputSize; i++) {
	    //Check outputs
	    if (outVector[i] - expectedVector[i] > 0.0000001 || outVector[i] - expectedVector[i] < 0.0000001)
		    fprintf(stderr, "outVector[%f] != expectedVector[%f]\n",
				    outVector[i], expectedVector[i]);
			status = 0;
	}
	return status;
}

void VectorsCPU(float weights[Vectors_outputSize * Vectors_vectorSize], float inVector[Vectors_streamSize * Vectors_vectorSize], float outVector[Vectors_streamSize * Vectors_outputSize])
{
    for (int i = 0; i < Vectors_streamSize * Vectors_outputSize; i++){
        outVector[i] = 0;
    }
    
    for (int k = 0; k < Vectors_streamSize; k++){
        for (int i = 0; i < Vectors_outputSize; i++) {
    	    for (int j = 0; j < Vectors_vectorSize; j++){
    	        outVector[k * Vectors_outputSize + i] = outVector[k * Vectors_outputSize + i] + weights[i * Vectors_vectorSize + j] * inVector[k * Vectors_vectorSize + j];
    	    }
	    
    	    //Relu activation
    	    if (outVector[k * Vectors_outputSize + i] < 0){
    	        outVector[k * Vectors_outputSize + i] = (float) 0;
    	    }
	    }
    }

}

// float * getWeights(int outputSize, int vectorSize)
// {
//     float weights[outputSize][vectorSize];
//     for (int i = 0; i< outputSize; i++){
//         for (int j = 0; j< vectorSize; j++){
//             weights[i][j] = (float) 0;
//         }
//     }
//     return weights;
// }

int main()
{
	const int vectorSize = Vectors_vectorSize;
	const int numberOutputs = Vectors_outputSize;
	
	float inVector[Vectors_streamSize * vectorSize];
	
	float outVector[Vectors_streamSize * Vectors_outputSize];
	float expectedVector[Vectors_streamSize * Vectors_outputSize];
	
	float weights[Vectors_outputSize * Vectors_vectorSize];
	

	for (int i = 0; i < Vectors_streamSize; i++) {
	    for (int j = 0; j < vectorSize; j++){
	        inVector[i * vectorSize + j] = (i * vectorSize + j) /100.0;
	    }
	}
	
	for (int i = 0; i < numberOutputs; i++){
	    for (int j = 0; j < vectorSize; j++){
	        weights[i * vectorSize + j] = 1;
	    }
	}

	VectorsCPU(weights, inVector, outVector);

	printf("Running DFE.\n");
	Vectors(Vectors_streamSize, inVector, expectedVector, weights);

	int status = check(outVector, expectedVector);
	if (status)
		printf("Test failed.\n");
	else
		printf("Test passed OK!\n");

	return status;
}
