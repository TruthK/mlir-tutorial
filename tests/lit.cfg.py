import os
from pathlib import Path

from lit.formats import ShTest

# oddly, the `config` variable is defined in the context of the lit runner that
# runs this module.

config.name = "mlir_tutorial"
config.test_format = ShTest()
config.suffixes = [".mlir"]

runfiles_dir = Path(os.environ.get("RUNFILES_DIR", "."))
tool_relpaths = [
    "llvm-project/mlir",
    "llvm-project/llvm",
    "mlir_tutorial/tools",
]

config.environment["PATH"] = (
    ":".join(str(runfiles_dir.joinpath(Path(path))) for path in tool_relpaths)
    + ":"
    + os.environ["PATH"]
)

substitutions = {
    "%project_source_dir": str(runfiles_dir.joinpath(Path('mlir_tutorial'))),
}
config.substitutions.extend(substitutions.items())
