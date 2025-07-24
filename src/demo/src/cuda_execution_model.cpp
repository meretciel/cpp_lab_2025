
#include <string>
#include <iostream>
#include <sstream>
#include "include/gpu_model.h"


int main() {
    constexpr int WARP_SIZE = 32;
    constexpr int GB_IN_MB = 1024;
    constexpr int K = 1024;

    const auto fermi_model = GpuModelBuilder()
        .with_n_sm(16)
        .with_n_cores_per_sm(32)
        .with_n_registers_per_sm(32 * K)
        .with_global_memory_mb(6 * GB_IN_MB)
        .with_l2_cache_kb(768)
        .build();

    std::cout << "Fermi Model: " << fermi_model << "\n";
}