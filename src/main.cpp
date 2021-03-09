#include "Cubism/Grid/Cartesian.h"
#include "Cubism/Mesh/StructuredUniform.h"
#include <algorithm> 

#include <IC.h> 

using namespace Cubism; 

int main(void)
{
    // step 1 - pre-processing 
    ///////////////////////////////////////////////////////////////////////////

    // initialize 3D mesh 
    using Mesh = Mesh::StructuredUniform<double, 3>; 
    using MIndex = typename Mesh::MultiIndex; 
    // cell-centered scalar grid using integer data 
    using Grid = Grid::Cartesian<int, Mesh, EntityType::Cell, 0>; 
    // determine number of cells & blocks in the mesh (13'824 cells)
    const MIndex nblocks(3);        // 3*3*3 = 27 blocks in topology
    const MIndex block_cells(8);    // 8*8*8 = 512 cells per block
    // allocate grid in the domain [0,1] (memory not touched) 
    Grid grid(nblocks, block_cells); 

    // initialize block fields using ICs
    int i = 1; 
    for (auto bf : grid) {
        printf("Hello from block %d.\n", i); 
        ++i; 
    }
    
    return 0; 
}
