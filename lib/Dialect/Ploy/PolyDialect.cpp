#pragma once
#include "PolyDialect.h"

#include "PolyTypes.h"
#include "lib/Dialect/Ploy/PolyDialect.cpp.inc"
#define GET_TYPEDEF_CLASSES
#include "lib/Dialect/Ploy/PolyTypes.cpp.inc"

namespace mlir::tutorial::poly {
    void PolyDialect::initialize(){
        addTypes<
        # define GET_TYPEDEF_LIST
        #include "lib/Dialect/Ploy/PolyTypes.cpp.inc"
        >();
    }
}
