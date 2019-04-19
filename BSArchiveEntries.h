#ifndef BSARCHIVEENTRIES_H
#define BSARCHIVEENTRIES_H

#include <QStringList>
#include <QDir>
#include "libbsarch.h"

class BSArchiveEntries
{
public:
    BSArchiveEntries();
    BSArchiveEntries(const QStringList& QSLEntries);
    ~BSArchiveEntries();

    void add(const QString& filepath);
    uint32_t count() const;
    QStringList list() const;

    bsa_entry_list_t getEntries() const;

private:
    bsa_entry_list_t entries;
};
#endif // BSARCHIVEENTRIES_H
