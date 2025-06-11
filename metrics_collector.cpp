#include "metrics_collector.hpp"

Metric::Metric(const std::string &name)
    : name_(name) {}

std::string Metric::getName() const {
    return name_;
}

MetricsCollector::MetricsCollector(const std::string &filename) {
    output_file_.open(filename, std::ios::out | std::ios::app);
    if (!output_file_.is_open()) {
        throw std::runtime_error("Failed to open metrics file");
    }
}

MetricsCollector::~MetricsCollector() {
    if (output_file_.is_open()) {
        output_file_.close();
    }
}

std::string MetricsCollector::getCurrentTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto now_time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;
    
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S")
        << "." << std::setfill('0') << std::setw(3) << ms.count();
    return oss.str();
}

void MetricsCollector::writeMetrics() {
    std::lock_guard<std::mutex> file_lock(file_mutex_);
    
    output_file_ << getCurrentTimestamp();
    
    for (const auto &metric : metrics_) {
        output_file_ << " \"" << metric->getName() << "\" "
                    << metric->getValueAsString();
        metric->reset();
    }
    
    output_file_ << std::endl;
}
