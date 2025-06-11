#pragma once

#include "metric.hpp"
#include <sstream>

template<typename T>
concept AppropriateType =
    requires(T a, T b) {
        { a += b } -> std::convertible_to<bool>;
        { a / int{} } -> std::convertible_to<bool>;
    };

template<typename T>
requires AppropriateType<T>
class TypedMetric : public Metric {
public:
    TypedMetric(const std::string &name)
        : Metric(name), value_{} {}
    
    void addValue(const T &value) {
        std::lock_guard<std::mutex> lock(mutex_);
        value_ += value;
        ++count_;
    }
    
    std::string getValueAsString() const override {
        std::lock_guard<std::mutex> lock(mutex_);
        if (count_ == 0) {
            return "0";
        }
        T avg = value_ / count_;
        std::ostringstream oss;
        oss << avg;
        return oss.str();
    }
    
    void reset() override {
        std::lock_guard<std::mutex> lock(mutex_);
        value_ = T{};
        count_ = 0;
    }

private:
    T value_;
    int count_ = 0;
};
