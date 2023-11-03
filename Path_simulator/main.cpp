//
//  main.cpp
//  Path_simulator
//
//  Created by Luis Paulo Santos on 03/11/2023.
//

#include <iostream>
#include <stdlib.h>

#include "circuit.h"
#include "simulate_all.hpp"

bool process_command_line (int argc, const char * argv[], char * filename, int& init_state, int& final_state);


int main(int argc, const char * argv[]) {
    
    char filename[1024];
    int init_state, final_state;
    
    if (!process_command_line (argc, argv, filename, init_state, final_state)) {
        fprintf (stderr, "Wrong command line!\n");
        exit (1);
    }
    
    TCircuit *circuit;
    circuit = read_circuit(filename);
    if (circuit==NULL) {
        fprintf (stderr, "read_circuit() failed!\n");
        return 1;
    }
    else fprintf (stdout, "read_circuit() OK!\n");

    print_circuit_stats(circuit);
    //print_circuit (circuit);
    
    
    // Simulate: < final_state | circuit | init_state >
    
    float aR, aI;
    simulate_all_paths (circuit, init_state, final_state, aR, aI);
    
    printf ("< %d | U | %d > = %.6f + i %.6f\n", final_state, init_state, aR, aI);
    
    std::cout << "Hello, World!\n";
    return 0;
}

bool process_command_line (int argc, const char * argv[], char * filename, int& init_state, int& final_state) {
    
    if (argc!=4) return false;
    
    strcpy(filename, argv[1]);
    init_state = atoi (argv[2]);
    final_state = atoi (argv[3]);
    
    return true;
}
