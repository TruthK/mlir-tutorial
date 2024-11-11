#ifndef LIB_TRANSFORM_AFFINE_PASSES_H_
#define LIB_TRANSFORM_AFFINE_PASSES_H_
#include <memory>
#include "mlir/Pass/Pass.h"

namespace mlir::tutorial::affine {
#define GEN_PASS_DECL
#include "lib/Transform/Affine/Passes.h.inc"

#define GEN_PASS_REGISTRATION
#include "lib/Transform/Affine/Passes.h.inc"

} // namespace mlir::tutorial::affine
#endif