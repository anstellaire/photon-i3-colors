# config -----------------------------------------------------------------------

HDR = mat_mult.cuh mat_mult_tiled.cuh
SRC = mat_mult_test.cu
EXE = exec

CMPFLAGS = --std=c++11 -O2 $(CXXFLAGS)
LNKFLAGS =

CLANG_CMPFLAGS = --cuda-gpu-arch=sm_80 $(CMPFLAGS)
CLANG_LNKFLAGS = -L$(CUDA_PATH)/lib64 -lcudart_static -ldl -lrt -pthread $(LNKFLAGS)

CUDA_CMPFLAGS = $(CMPFLAGS)
CUDA_LNKFLAGS = $(LNKFLAGS)

# rules ------------------------------------------------------------------------

.PHONY: run profile build_for_clang clean

run: $(EXE)
	./$(EXE)

profile: $(EXE)
	nvprof ./$(EXE)

$(EXE): $(HDR) $(SRC)
	nvcc $(CUDA_CMPFLAGS) -o $(EXE) $(SRC) $(CUDA_LNKFLAGS)

build_for_clang: $(HDR) $(SRC)
	clang++ $(CLANG_CMPFLAGS) -o $(EXE) $(SRC) $(CLANG_LNKFLAGS)

clean:
	rm -f $(EXE)
