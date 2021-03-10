#include "Cubism/Block/DataLab.h"
#include "Cubism/Block/Field.h"
#include "Cubism/Common.h"
#include "Cubism/Compiler.h"
#include <algorithm> 

#include <IC.h> 

using namespace Cubism; 

int main(void)
{
    // step 1 - pre-processing 
    ///////////////////////////////////////////////////////////////////////////

    // identifiers to be used for creating & managing 3D concentration fields
    using Field = Block::Field<double, EntityType::Node, 3>; 
    using IRange = typename Field::IndexRangeType; 
    using MIndex = typename IRange::MultiIndex; 
    using DataLab = Block::DataLab<Field>; 
    using Stencil = typename DataLab::StencilType; 

    // define 3D fields to be used (memory not touched)
    MIndex elements(16);                // 16*16*16 = 4'096 cells
    IRange element_domain(elements);    // generate element domain
    Field u(element_domain);            // concentration field for species U
    Field v(element_domain);            // concentration field for species V

    double k = 0; 
    for (auto &n : u) {
        n = k; 
        k += 1; 
        printf("field value:\t%f.\n", (double)n); 
    }

    auto fields = [&](const MIndex &)->Field & { return u; };

    DataLab dlab; 
    const Stencil s(-1, 2); 
    dlab.allocate(s, u.getIndexRange()); 
    dlab.loadData(MIndex(0), fields); 

    // attempt to compile and run for now

    return 0; 
}
