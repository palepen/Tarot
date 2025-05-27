#include "libtarot/Utils.h"
#include "libtarot/TokenType.h"

#include <llvm/Support/ErrorHandling.h>

std::string indent(size_t level) { return std::string(level * 2, ' '); }


std::string_view getOpStr(TokenType op)
{
    switch (op)
    {
    case TokenType::PLUS:
        return "+";
    case TokenType::ASTERISK:
        return "*";
    case TokenType::MINUS:
        return "-";
    case TokenType::SLASH:
        return "/";
    default:
        break;
    }

    llvm_unreachable("unexpected operator");
}
