#include "BSArchiveAuto.h"
#include "QLibbsarch.h"

BSArchiveAuto::BSArchiveAuto(const QString& rootDirectory) : archive(BSArchive()), entries (BSArchiveEntries()), rootDirectory(rootDirectory) {}


void BSArchiveAuto::create(const QString &archiveName, bsa_archive_type_e type)
{
    archive.create(archiveName, type, entries);

    for (int i = 0 ; i < filesfromMemoryData.size() ; ++i)
    {
        archive.addFileFromMemory(filesFromMemoryFilename.at(i), filesfromMemoryData.at(i));
    }

    for (auto file : filesFromDisk)
    {
        archive.addFileFromDisk(rootDirectory.path(), file);
    }
}


void BSArchiveAuto::addFileFromDisk(const QString &filename)
{
    entries.add(rootDirectory.relativeFilePath(filename));
    filesFromDisk << filename;
}


void BSArchiveAuto::addFileFromDisk(const QStringList& files)
{
    for (auto file : files)
    {
        addFileFromDisk(file);
    }
}

void BSArchiveAuto::addFileFromMemory(const QString &filename, const QByteArray &data)
{
    entries.add(filename);
    filesfromMemoryData << data;
    filesFromMemoryFilename << filename;
}

void BSArchiveAuto::extractAll(const QString& destinationDirectory)
{
    for (auto file : entries.list())
    {
        archive.extract(file, destinationDirectory + "/" + file);
    }
}

