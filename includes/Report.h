#ifndef REPORT_H
#define REPORT_H
#include "Source.h"

std::nullptr_t report(SourceLocation location, std::string_view message, bool isWarning = false);


#endif