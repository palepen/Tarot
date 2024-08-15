#ifndef TYPE_H
#define TYPE_H
#include <string>

struct Type
{
    enum class Kind
    {
        Void,
        Number,
        Custom
    };
    Kind kind;
    std::string name;
    static Type builtInVoid() { return {Kind::Void, "void"}; };
    static Type builtInNumber() { return {Kind::Number, "number"}; };
    static Type builtInCustom(const std::string &name) { return {Kind::Custom, name}; };

private:
    Type(Kind kind, std::string name) : kind(kind), name(name){};
};
#endif