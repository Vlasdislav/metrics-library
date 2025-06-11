#pragma once

#include <string>
#include <mutex>

class Metric {
public:
    Metric(const std::string &name);
    virtual ~Metric() = default;
    
    std::string getName() const;
    virtual std::string getValueAsString() const = 0;
    virtual void reset() = 0;

protected:
    std::string name_;
    mutable std::mutex mutex_;
};
