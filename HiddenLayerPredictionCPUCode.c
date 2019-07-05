/**
 * MaxFile name: HiddenLayerPredictionCPUCode
 * Based on Vectors example from simulation IDE
*/

#include <stdio.h>
#include <stdlib.h>
#include "Maxfiles.h"
#include <MaxSLiCInterface.h>



int check(float * outVector, float * expectedVector)
{
	int status = 0;
	for (int i = 0; i < HiddenLayerPrediction_streamSize * HiddenLayerPrediction_outputSize; i++) {
	    fprintf(stderr, "outVector[%f] || expectedVector[%f]\n",
				    outVector[i], expectedVector[i]);
	    if (outVector[i] != expectedVector[i]){
		    fprintf(stderr, "Error: Output and Expected value do not match!");
			status = 1;
	    }
	}
	return status;
}

void HiddenLayerPredictionCPU(float weights[HiddenLayerPrediction_outputSize * HiddenLayerPrediction_vectorSize], float inVector[HiddenLayerPrediction_streamSize * HiddenLayerPrediction_vectorSize], float outVector[HiddenLayerPrediction_streamSize * HiddenLayerPrediction_outputSize])
{
    for (int i = 0; i < HiddenLayerPrediction_streamSize * HiddenLayerPrediction_outputSize; i++){
        outVector[i] = 0;
    }
    
    for (int k = 0; k < HiddenLayerPrediction_streamSize; k++){
        for (int i = 0; i < HiddenLayerPrediction_outputSize; i++) {
    	    for (int j = 0; j < HiddenLayerPrediction_vectorSize; j++){
    	        outVector[k * HiddenLayerPrediction_outputSize + i] = outVector[k * HiddenLayerPrediction_outputSize + i] + weights[i * HiddenLayerPrediction_vectorSize + j] * inVector[k * HiddenLayerPrediction_vectorSize + j];
    	    }
	    
    	    //Relu activation
    	    if (outVector[k * HiddenLayerPrediction_outputSize + i] < 0){
    	        outVector[k * HiddenLayerPrediction_outputSize + i] = (float) 0;
    	    }
	    }
    }

}

int main()
{
	const int vectorSize = HiddenLayerPrediction_vectorSize;
	const int numberOutputs = HiddenLayerPrediction_outputSize;
	
	float inVector[HiddenLayerPrediction_streamSize * vectorSize];
	
	float outVector[HiddenLayerPrediction_streamSize * HiddenLayerPrediction_outputSize];
	float expectedVector[HiddenLayerPrediction_streamSize * HiddenLayerPrediction_outputSize];
	
	float weights[HiddenLayerPrediction_outputSize * HiddenLayerPrediction_vectorSize];
	

	for (int i = 0; i < HiddenLayerPrediction_streamSize; i++) {
	    for (int j = 0; j < vectorSize; j++){
	        inVector[i * vectorSize + j] = (i * vectorSize + j) /100.0;
	    }
	}
	
	for (int i = 0; i < numberOutputs; i++){
	    for (int j = 0; j < vectorSize; j++){
	        weights[i * vectorSize + j] = 1;
	    }
	}

	HiddenLayerPredictionCPU(weights, inVector, outVector);

	printf("Running DFE.\n");
	HiddenLayerPrediction(HiddenLayerPrediction_streamSize, inVector, expectedVector, weights);

	int status = check(outVector, expectedVector);
	if (status)
		printf("Test failed.\n");
	else
		printf("Test passed OK!\n");

	return status;
}
