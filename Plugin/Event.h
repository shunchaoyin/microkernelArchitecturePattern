#pragma once

#include <string>
#include <memory>

class AEvent
{
public:
    virtual ~AEvent() = default;

    virtual std::string getType() const = 0;
    virtual std::string getData() const = 0;
};

class SimpleEvent : public AEvent
{
public:
    SimpleEvent(const std::string& type, const std::string& data)
        : _type(type), _data(data) {
    }

    std::string getType() const override { return _type; }
    std::string getData() const override { return _data; }

private:
    std::string _type;
    std::string _data;
};
