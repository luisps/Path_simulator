//
//  simulate_all.cpp
//  Path_simulator
//
//  Created by Luis Paulo Santos on 03/11/2023.
//

#include "simulate_all.hpp"
#include <math.h>
#include "complex.h"
#include "layer.hpp"


void simulate_all_paths (TCircuit *circuit,
                         int init_state, int final_state,
                         float& aR, float& aI) {
    
    int ndxs[4];
    const int L = circuit->size->num_layers;
    const int N = (int)(powf(2.f, (float)circuit->size->num_qubits));
    
    float sumR=0.f, sumI=0.f;
    
    for (ndxs[0]=0 ; ndxs[0]<N ; ndxs[0]++) {  // Isto tem que passar para while
        
        for (ndxs[1]=0 ; ndxs[1]<N ; ndxs[1]++) {
            for (ndxs[2]=0 ; ndxs[2]<N ; ndxs[2]++) {
                for (ndxs[3]=0 ; ndxs[3]<N ; ndxs[3]++) {
                    
                    float pathR=1.f, pathI=0.f;
                    
                    // path bem definido: init_state-> ndxs[0] -> ..... -> ndxs[L-2] -> final_state
                    
                    int current_state = init_state;
                    int next_state, l;
                    
                    for (l=0 ; l<L ; l++) {
                        float lR=1.f, lI=0.f;
                        
                        next_state = (l< L-1 ? ndxs[l] : final_state);
                        
                        // processar o layer (lR, lI)
                        // get gate layer l
                        TCircuitLayer *layer = &circuit->layers[l];
                        
                        // get the amplitude of this layer for the given current and next states
                        // Wer are reevaluating all layers even though a single ndxs[] changes: INNEFICIENT
                        layer_w (layer, l, current_state, next_state, lR, lI);
                        
                        if (complex_abs_square(lR, lI) <= 0.) {
                            ///// TERMINATE PATH
                            pathR = pathI = 0.f;
                            continue;
                        }

                        
                        complex_multiply (pathR, pathI, lR, lI, pathR, pathI);
                        
                        current_state = next_state;
                        
                    }
                    
                    sumR += pathR;
                    sumI += pathI;
                    
                }
            }
        }
    }
    aR = sumR;
    aI = sumI;
    
}
