#ifndef BSARCHIVE_H
#define BSARCHIVE_H

#include <QDir>
#include <QStringList>
#include "libbsarch.h"
#include "BSArchiveEntries.h"

class BSArchive
{
public:
    BSArchive();
    ~BSArchive();

    void open(const QString& archivePath);
    void close() const;
    void create(const QString& archiveName, bsa_archive_type_e type, BSArchiveEntries entries);
    void save() const;
    void addFileFromDisk(const QString& rootDir, const QString& filename);
    void addFileFromDisk(const QString& rootDir, const QStringList& files);
    void addFileFromMemory(const QString& filename, const QByteArray& data);
    void setCompressed(bool value);



private:
    bsa_archive_t archive;

};

#endif // BSARCHIVE_H
