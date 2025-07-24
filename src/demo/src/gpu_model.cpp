#include "include/gpu_model.h"
#include <sstream>

GpuModel::GpuModel(
    int n_sm,
    int n_cores_per_sm,
    int n_registers_per_sm,
    int global_memory_mb,
    int l2_cache_kb
):
    _n_sm(n_sm),
    _n_cores_per_sm(n_cores_per_sm),
    _n_registers_per_sm(n_registers_per_sm),
    _global_memory_mb(global_memory_mb),
    _l2_cache_kb(l2_cache_kb)
{}

int GpuModel::n_sm() const { return _n_sm; }
int GpuModel::n_cores_per_sm() const { return _n_cores_per_sm; }
int GpuModel::n_registers_per_sm() const { return _n_registers_per_sm; }
int GpuModel::global_memory_mb() const { return _global_memory_mb; }
int GpuModel::l2_cache_kb() const { return _l2_cache_kb; }

std::string GpuModel::to_string() const {
    std::stringstream ss;
    ss << "GpuModel("
        << "n_sm=" << _n_sm << ","
        << "n_cores_per_sm=" << _n_cores_per_sm << ","
        << "n_registers_per_sm=" << _n_registers_per_sm << ","
        << "global_memory_mb=" << _global_memory_mb << ","
        << "l2_cache_kb=" << _l2_cache_kb << ","
       << ")";
    return ss.str();
}

std::ostream& operator<<(std::ostream& out, const GpuModel& gpu_model) {
    return out << gpu_model.to_string();
}

int GpuModel::n_cores() const {return _n_sm * _n_cores_per_sm;}

GpuModelBuilder::GpuModelBuilder():
    _n_sm(0),
    _n_cores_per_sm(0),
    _n_registers_per_sm(0),
    _global_memory_mb(0),
    _l2_cache_kb(0)
{}

GpuModel GpuModelBuilder::build() const {
    return GpuModel {
        _n_sm,
        _n_cores_per_sm,
        _n_registers_per_sm,
        _global_memory_mb,
        _l2_cache_kb
    };
}

GpuModelBuilder& GpuModelBuilder::with_n_sm(int n_sm) { _n_sm = n_sm; return *this;}
GpuModelBuilder& GpuModelBuilder::with_n_cores_per_sm(int n_cores_per_sm) { _n_cores_per_sm = n_cores_per_sm; return *this;}
GpuModelBuilder& GpuModelBuilder::with_n_registers_per_sm(int n_registers_per_sm) { _n_registers_per_sm = n_registers_per_sm; return *this;}
GpuModelBuilder& GpuModelBuilder::with_global_memory_mb(int global_memory_mb) { _global_memory_mb = global_memory_mb; return *this;}
GpuModelBuilder& GpuModelBuilder::with_l2_cache_kb(int l2_cache_kb) { _l2_cache_kb = l2_cache_kb; return *this;}
