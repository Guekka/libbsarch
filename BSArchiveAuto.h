#ifndef BSARCHIVEAUTO_H
#define BSARCHIVEAUTO_H

#include "BSArchive.h"
#include "BSArchiveEntries.h"


/*!
 * \brief A convenience class for BSArchive and BSArchive Entries
 */
class BSArchiveAuto : protected BSArchiveEntries, public BSArchive
{
public:
    BSArchiveAuto();

    void create(const QString& archiveName, bsa_archive_type_e type);
    void addFileFromDisk(const QString& rootDir, const QString& filename);
    void addFileFromDisk(const QString& rootDir, const QStringList& files);
    void addFileFromMemory(const QString& filename, const QByteArray& data);

private:
    BSArchive archive;
    BSArchiveEntries entries;
};

#endif // BSARCHIVEAUTO_H
