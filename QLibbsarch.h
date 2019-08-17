#pragma once

#include "libbsarch.h"
#include <string>
#include <QDebug>
#include <QDir>
#include <QStringList>

namespace QLibBsarch
{
    constexpr bool enableDebugLog = true;
} // namespace QLibBsarch

#define LOG_LIBBSARCH \
    if constexpr (QLibBsarch::enableDebugLog) \
    qDebug() << "[QLIBBSARCH] "

#define PREPARE_PATH_LIBBSARCH(qstring) reinterpret_cast<const wchar_t *>(QDir::toNativeSeparators(qstring).utf16())

inline const std::string wcharToString(const wchar_t *text)
{
    return QString::fromWCharArray(text).toStdString();
}
