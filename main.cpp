// For example

#include "metrics_collector.hpp"
#include "metrics_collector.hpp"

#include <thread>
#include <chrono>
#include <random>

int main() {
    MetricsCollector collector("metrics.log");
    
    auto &cpu_metric = collector.registerMetric<double>("CPU");
    auto &http_metric = collector.registerMetric<int>("HTTP requests RPS");
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> cpu_dist(0.1, 3.5);
    std::uniform_int_distribution<int> http_dist(5, 150);
    
    for (int i = 0; i <= 20; ++i) {
        cpu_metric.addValue(cpu_dist(gen));
        http_metric.addValue(http_dist(gen));
        
        if (i % 5 == 0) {
            collector.writeMetrics();
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
