#include "Cubism/Block/DataLab.h"
#include "Cubism/Block/Field.h"
#include "Cubism/Grid/Cartesian.h"
#include "Cubism/Common.h"
#include "Cubism/Compiler.h"
#include <algorithm> 
#include <iostream> 

#include <IC.h> 

using namespace Cubism; 

int main(void)
{
    // step 1 - pre-processing 
    ///////////////////////////////////////////////////////////////////////////

    // initialize Gray-Scott simulation variables to be used throughout
    double time = 5000;         // simulation duration [s]
    double domain = 1.0;        // computational domain in each dimension [m]
    int N = 25;                 // grid points on domain in each direction []
    double F = 0.04;            // feed-rate (permeability to U) [m^2]
    double kappa = 0.06;        // feed-reate minus permeability to V [m^2]
    double D_u = 0.00002;       // diffusivity of U species [m^2/s]
    double D_v = 0.00001;       // diffusivity of V species [m^2/s] 
    int dump_freq = 10;         // frequency of solution dump to file []

    // identifiers to be used for creating & managing 3D concentration fields
    using Field = Block::Field<double, EntityType::Cell, 3>; 
    using IRange = typename Field::IndexRangeType; 
    using MIndex = typename IRange::MultiIndex; 
    using DataLab = Block::DataLab<Field>; 
    using Stencil = typename DataLab::StencilType; 

    // create 3D concentration fields to be used
    MIndex elements(N);                 // N*N*N = N^3 nodes
    IRange element_domain(elements);    // generate element domain
    Field u(element_domain);            // concentration field for species U
    Field v(element_domain);            // concentration field for species V
    Field u_temp(element_domain);       // temp solution field for species U
    Field v_temp(element_domain);       // temp solution field for species V

    // define functions which will return u or v concentration fields
    auto field_u = [&](const MIndex &) -> Field & { return u; };
    auto field_v = [&](const MIndex &) -> Field & { return v; }; 

    // generate DataLab objects for easy & efficient ghost cell treatment
    DataLab dlab_u;
    DataLab dlab_v;  
    const Stencil s(-1, 2);                 // stencil for 2nd-order CDS
    dlab_u.allocate(s, u.getIndexRange());  // allocate memory 
    dlab_v.allocate(s, v.getIndexRange());  
    dlab_u.loadData(MIndex(0), field_u);    // load DataLab w/ periodic BCs
    dlab_v.loadData(MIndex(0), field_v); 

    // initialize dlab concentration fields using arbitrary ICs 
    // call IC function

    // step 2 - run the simulation 
    ///////////////////////////////////////////////////////////////////////////


    return 0; 
}
