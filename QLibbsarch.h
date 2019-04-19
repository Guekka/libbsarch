#ifndef QLIBBSARCH_H
#define QLIBBSARCH_H

#include "libbsarch.h"
#include <QStringList>
#include <string>

const wchar_t *QStringToWchar(const QString& Qstring);
const std::string wcharToString(const wchar_t *text);


#endif // QLIBBSARCH_H


