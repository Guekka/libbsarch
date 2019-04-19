#include "BSArchiveAuto.h"
#include "QLibbsarch.h"

BSArchiveAuto::BSArchiveAuto() : archive(BSArchive()), entries (BSArchiveEntries()) {}


void BSArchiveAuto::create(const QString &archiveName, bsa_archive_type_e type)
{
    archive.create(archiveName, type, entries);
}


void BSArchiveAuto::addFileFromDisk(const QString &rootDir, const QString &filename)
{
    QDir rootDirectory (rootDir);
    entries.add(rootDirectory.relativeFilePath(filename));
    archive.addFileFromDisk(rootDir, filename);
}


void BSArchiveAuto::addFileFromDisk(const QString &rootDir, const QStringList& files)
{
    for (auto file : files)
    {
        addFileFromDisk(rootDir, file);
    }
}

void BSArchiveAuto::addFileFromMemory(const QString &filename, const QByteArray &data)
{
    entries.add(filename);
    archive.addFileFromMemory(filename, data);
}
