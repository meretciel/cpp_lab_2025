//
// Created by ryan on 4/13/25.
//

#ifndef GPU_MODEL_H
#define GPU_MODEL_H

#include<string>

class GpuModel {
private:
    int _n_sm;
    int _n_cores_per_sm;
    int _n_registers_per_sm;
    int _global_memory_mb;
    int _l2_cache_kb;

public:
    GpuModel(
        int n_sm,
        int n_cores_per_sm,
        int n_registers_per_sm,
        int global_memory_mb,
        int l2_cache_kb
    );
    int n_sm() const;
    int n_cores_per_sm() const;
    int n_registers_per_sm() const;
    int global_memory_mb() const;
    int l2_cache_kb() const;
    std::string to_string() const;

    int n_cores() const;
};

std::ostream& operator<<(std::ostream& out, const GpuModel& gpu_model);

class GpuModelBuilder {
private:
    int _n_sm;
    int _n_cores_per_sm;
    int _n_registers_per_sm;
    int _global_memory_mb;
    int _l2_cache_kb;

public:
    GpuModelBuilder();
    GpuModel build() const;
    GpuModelBuilder& with_n_sm(int n_sm);
    GpuModelBuilder& with_n_cores_per_sm(int n_cores_per_sm);
    GpuModelBuilder& with_n_registers_per_sm(int n_registers_per_sm);
    GpuModelBuilder& with_global_memory_mb(int global_memory_mb);
    GpuModelBuilder& with_l2_cache_kb(int l2_cache_kb);
};

#endif //GPU_MODEL_H
