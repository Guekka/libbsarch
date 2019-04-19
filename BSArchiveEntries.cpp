#include "BSArchiveEntries.h"
#include "QLibbsarch.h"

BSArchiveEntries::BSArchiveEntries() : entries (bsa_entry_list_create()) {}

BSArchiveEntries::BSArchiveEntries(const QStringList& QSLEntries) : entries (bsa_entry_list_create())
{
    for(auto entry : QSLEntries)
    {
        add (entry);
    }
}

BSArchiveEntries::~BSArchiveEntries()
{
    bsa_entry_list_free(entries);
}

void BSArchiveEntries::add(const QString &filepath)
{
    const wchar_t *path = QStringToWchar( QDir::toNativeSeparators(filepath) );

    auto result = bsa_entry_list_add(entries, path);
    if(result.code == BSA_RESULT_EXCEPTION)
        throw std::runtime_error(wcharToString(result.text));
}

uint32_t BSArchiveEntries::count() const
{
    return bsa_entry_list_count(entries);
}

QStringList BSArchiveEntries::list() const
{
    QStringList list;
    for(uint32_t i = 0 ; i < count() ; ++i)
    {
        wchar_t *buffer;
        bsa_entry_list_get(entries, i, 1024, buffer);
        list << QString::fromWCharArray(buffer);
    }
    return list;
}

bsa_entry_list_t BSArchiveEntries::getEntries() const
{
    return entries;
}

