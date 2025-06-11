#pragma once

#include "metric.hpp"
#include "typed_metric.hpp"
#include <memory>
#include <vector>
#include <fstream>
#include <iomanip>


class MetricsCollector {
public:
    MetricsCollector(const std::string &filename);
    ~MetricsCollector();
    
    template<typename T>
    TypedMetric<T>& registerMetric(const std::string &name) {
        auto metric = std::make_unique<TypedMetric<T>>(name);
        auto &ref = *metric;
        metrics_.emplace_back(std::move(metric));
        return ref;
    }
    
    void writeMetrics();

private:
    std::string getCurrentTimestamp() const;
    
    std::vector<std::unique_ptr<Metric>> metrics_;
    std::ofstream output_file_;
    std::mutex file_mutex_;
};
