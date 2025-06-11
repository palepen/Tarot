#ifndef CONTAINER_H
#define CONTAINER_H
#include <optional>

template <typename Ty>
class ConstantValueContainer
{
    std::optional<Ty> Value = std::nullopt;
public:
    void setConstantValue(std::optional<Ty> val)
    {
        Value = std::move(val);   
    }
    std::optional<Ty> getConstantValue() const
    {
        return Value;
    }
};

#endif