#include "Cubism/Block/DataLab.h"
#include "Cubism/Block/Field.h"
#include "Cubism/Grid/Cartesian.h"
#include "Cubism/Common.h"
#include "Cubism/Compiler.h"
#include <algorithm> 

#include <IC.h>
#include <Laplacian.h> 

using namespace Cubism; 

int main(void)
{
    // step 1 - pre-processing 
    ///////////////////////////////////////////////////////////////////////////

    // initialize Gray-Scott simulation variables to be used throughout
    double time = 5000.0;       // simulation duration [s]
    double domain = 1.0;        // computational domain in each dimension [m]
    int N = 25;                 // grid points on domain in each direction []
    double F = 0.04;            // feed-rate (permeability to U) [m^2]
    double kappa = 0.06;        // feed-reate minus permeability to V [m^2]
    double D_u = 0.00002;       // diffusivity of U species [m^2/s]
    double D_v = 0.00001;       // diffusivity of V species [m^2/s] 
    int dump_freq = 10;         // frequency of solution dump to file []
    double h = domain/N;        // stepsize in all directions (dx,dy,dz) [m]

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

    // define functions which will return created concentration fields
    auto field_u = [&](const MIndex &) -> Field & { return u; };
    auto field_v = [&](const MIndex &) -> Field & { return v; };
    auto field_u_temp = [&](const MIndex &) -> Field & { return u_temp; }; 
    auto field_v_temp = [&](const MIndex &) -> Field & { return v_temp; };  

    // generate DataLab objects for easy & efficient ghost cell treatment
    DataLab dlab_u;
    DataLab dlab_v;  
    const Stencil s(-1, 2);                 // stencil for 2nd-order CDS
    dlab_u.allocate(s, u.getIndexRange());  // allocate memory 
    dlab_v.allocate(s, v.getIndexRange());  
    dlab_u.loadData(MIndex(0), field_u);    // load DataLab w/ periodic BCs
    dlab_v.loadData(MIndex(0), field_v);
    // generate dummy Datalab objects for temporary solution storage 
    DataLab dlab_u_temp; 
    DataLab dlab_v_temp; 
    const Stencil s_dummy(0, 0);                            // 1-point stencil
    dlab_u_temp.allocate(s_dummy, u_temp.getIndexRange());  // allocate memory
    dlab_v_temp.allocate(s_dummy, v_temp.getIndexRange()); 
    dlab_u_temp.loadData(MIndex(0), field_u_temp);          // periodic BCs
    dlab_v_temp.loadData(MIndex(0), field_v_temp); 

    // initialize dlab concentration fields using arbitrary ICs 
    IC(dlab_u, dlab_v, N, h);  



    // step 2 - run the simulation 
    ///////////////////////////////////////////////////////////////////////////
    
    // timestep based on 2nd-order CDS stability conditions - use largest D
    double dt = h*h / (2*D_u);
    // pre-compute & initialize variables to be used within loops
    double fac_u = D_u*dt / (h*h);  // Laplacian multiplication factor for U
    double fac_v = D_v*dt / (h*h);  // Laplacian mutliplication factor for V
    double result_u;                // Laplacian discretization for U
    double result_v;                // Laplacian discretization for V
    double reac;                    // local reaction (law of mass attraction)

    // loop through time
    for (double t = 0.0; t < time; t+=dt) {
        // loop through space 
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    // compute Laplacian discretizations
                    result_u = Laplacian(dlab_u, i, j, k);
                    result_v = Laplacian(dlab_v, i, j, k);
                    // compute local reaction term 
                    reac = dlab_u(i,j,k)*dlab_v(i,j,k)*dlab_v(i,j,k); 
                    // compute updated value for species U
                    dlab_u_temp(i,j,k) = dlab_u(i,j,k) + fac_u*result_u 
                                + dt*( F*(1-dlab_u(i,j,k)) - reac );
                    // compute updated value for species V
                    dlab_v_temp(i,j,k) = dlab_v(i,j,k) + fac_v*result_v 
                                + dt*( reac - dlab_v(i,j,k)*(F+kappa) ); 
                } 
            }
        }  
        // advance solution by exchanging dlab_temp (new) and dlab (old)
        // hello 
    } 

    return 0; 
}
