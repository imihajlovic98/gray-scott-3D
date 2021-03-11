#ifndef LAPLACIAN_HPP
#define LAPLACIAN_HPP

#include "Cubism/Block/Field.h"
#include "Cubism/Common.h"
#include "Cubism/Compiler.h"

using namespace Cubism; 

// definition: apply Laplacian discretization (factor multi. done in main)
double Laplacian(
        Block::DataLab<Block::Field<double, EntityType::Cell, 3>> &dlab,
        int i, int j, int k);

#endif // LAPLACIAN_HPP
