/**
 * MaxFile name: HiddenLayerPredictionKernel
 * Based on Vectors example from simulation IDE
*/
h
package hiddenLayerPrediction;

import com.maxeler.maxcompiler.v2.kernelcompiler.Kernel;
import com.maxeler.maxcompiler.v2.kernelcompiler.KernelParameters;
import com.maxeler.maxcompiler.v2.kernelcompiler.types.base.DFEVar;
import com.maxeler.maxcompiler.v2.kernelcompiler.types.base.DFEType;
import com.maxeler.maxcompiler.v2.kernelcompiler.types.composite.DFEVector;
import com.maxeler.maxcompiler.v2.kernelcompiler.types.composite.DFEVectorType;

class HiddenLayerPredictionKernel extends Kernel {

	HiddenLayerPredictionKernel(KernelParameters parameters, int vectorSize, float weights[]) {
		super(parameters);
		
		DFEType type = dfeFloat(8,24);
		
		int outputSize = weights.length / vectorSize;

		DFEVectorType<DFEVar> inputVectorType =
			new DFEVectorType<DFEVar>(type, vectorSize);
			
	    DFEVectorType<DFEVar> outputVectorType = 
	        new DFEVectorType<DFEVar>(type, outputSize);

		// Input
		DFEVector<DFEVar> inVector = io.input("inVector", inputVectorType);
            
        // Setting up output
        DFEVector<DFEVar> outVector = outputVectorType.newInstance(this); 

        // Main loop matrix multiplication
        for (int i = 0; i< outputSize; i++){
            DFEVar count = constant.var(type, 0);
            for (int j = 0; j < vectorSize; j++){
                count = count + weights[i * vectorSize + j] * inVector[j];
            }
            
            //Relu Activation
            outVector[i] <== count > 0 ? count : 0;
        }
        
		//Output
		io.output("outVector", outVector, outputVectorType);
	}

}
