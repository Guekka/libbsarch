#ifndef BSARCHIVEENTRIES_H
#define BSARCHIVEENTRIES_H

#include "QLibbsarch.h"

class BSArchiveEntries
{
public:
    BSArchiveEntries();
    BSArchiveEntries(const QStringList& QSLEntries);
    BSArchiveEntries(const bsa_entry_list_t& entries);
    ~BSArchiveEntries();

    void add(const QString& filepath);
    uint32_t count() ;
    QStringList list();

    bsa_entry_list_t getEntries() const;

private:
    bsa_entry_list_t m_entries;
};
#endif // BSARCHIVEENTRIES_H
