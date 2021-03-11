#include "Cubism/Block/Field.h"
#include "Cubism/Common.h"
#include "Cubism/Compiler.h"

using namespace Cubism; 

double Laplacian(
        Block::DataLab<Block::Field<double, EntityType::Cell, 3>> &dlab, 
        int i, int j, int k)
{
    // for now naively implement only 2nd-order CDS
    // TODO: generalize Laplacian function
    // TODO: think of more intelligent implementation 
    
    double result = dlab(i+1,j,k) + dlab(i-1,j,k) + dlab(i,j+1,k) 
                    + dlab(i,j-1,k) + dlab(i,j,k+1) + dlab(i,j,k-1) 
                    - 6*dlab(i,j,k);  

    return result; 
}
