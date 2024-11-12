#pragma once


#include "lib/Dialect/Poly/PolyDialect.h"
#include "lib/Dialect/Poly/PolyTypes.h"
#include "lib/Dialect/Poly/PolyTraits.h"
// #include ""
#include "mlir/IR/BuiltinOps.h"

#include "mlir/Interfaces/InferTypeOpInterface.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"

#define GET_OP_CLASSES
#include "lib/Dialect/Poly/PolyOps.h.inc"