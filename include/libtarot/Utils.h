#ifndef INDENT_H
#define INDENT_H
#include "TokenType.h"
#include <string>

std::string indent(size_t level);
std::string_view getOpStr(TokenType op);
#endif

