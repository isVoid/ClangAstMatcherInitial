# Fast bootstrap project to develop with ASTMatcher and GTest

## Environment Setup Via Conda

Setting up the environment by running:

```bash
conda env create --file environment.yaml
```

Activate environment.

```bash
conda activate bootast
```

## Build the code

Make build folder and configure project:
```bash
mkdir build && cd build && cmake ..
```

Build the software:
```bash
cmake --build .
```

Run and verify:
```bash
./myTool
```