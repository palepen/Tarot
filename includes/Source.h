#ifndef SOURCE_H
#define SOURCE_H
#include <string>
#include <string_view>
struct SourceLocation
{
    std::string_view filepath;
    int line;
    int col;
};

struct SourceFile
{
    std::string_view path;
    std::string buffer;
    SourceFile(const std::string_view path, const std::string buffer) : path(path), buffer(buffer) {}
};

#endif