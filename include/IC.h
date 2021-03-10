#ifndef IC_HPP
#define IC_HPP

#include "Cubism/Block/Field.h"
#include "Cubism/Common.h"
#include "Cubism/Compiler.h"

using namespace Cubism; 

// definition: collection of possible initial conditions for Gray-Scott
void IC(Block::Field<double, EntityType::Cell, 3> &u, 
        Block::Field<double, EntityType::Cell, 3> &v, 
        int N, double domain); 

#endif // IC_HPP
