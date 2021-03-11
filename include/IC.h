#ifndef IC_HPP
#define IC_HPP

#include "Cubism/Block/Field.h"
#include "Cubism/Common.h"
#include "Cubism/Compiler.h"

using namespace Cubism; 

// definition: collection of possible initial conditions for Gray-Scott
void IC(Block::DataLab<Block::Field<double, EntityType::Cell, 3>> &dlab_u, 
        Block::DataLab<Block::Field<double, EntityType::Cell, 3>> &dlab_v, 
        int N, double h); 

#endif // IC_HPP
