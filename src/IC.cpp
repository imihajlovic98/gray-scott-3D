#include "Cubism/Block/Field.h"
#include "Cubism/Common.h"
#include "Cubism/Compiler.h"
#include <math.h> 

using namespace Cubism; 

void IC(Block::DataLab<Block::Field<double, EntityType::Cell, 3>> &dlab_u, 
        Block::DataLab<Block::Field<double, EntityType::Cell, 3>> &dlab_v, 
        int N, double domain)
{
    // for now incorporate just some arbitrary ICs

    double h = domain/N;        // stepsize in all dimensions (dx, dy, dz)
    // loop over dimensions
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                // apply ICs w.r.t. sphere with radius 0.5
                if (h*(i*i + j*j + k*k) < 0.5*0.5) {
                    dlab_u(i,j,k) = 1.0; 
                    dlab_v(i,j,k) = 0.0; 
                }
                else {
                    dlab_u(i,j,k) = 0.5; 
                    dlab_v(i,j,k) = 0.5; 
                }
            }
        } 
    }
}
