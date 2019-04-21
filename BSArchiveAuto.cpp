#include "BSArchiveAuto.h"
#include "QLibbsarch.h"

BSArchiveAuto::BSArchiveAuto(const QString& rootDirectory) : rootDirectory(QDir::toNativeSeparators(QDir::cleanPath(rootDirectory))) {}


void BSArchiveAuto::create(const QString &archiveName, const bsa_archive_type_e &type)
{
    const wchar_t *path = QStringToWchar( QDir::toNativeSeparators(archiveName) );
    bsa_create_archive(getArchive(), path, type, getEntries());

    QMapIterator<QString, QByteArray> mapIt(filesfromMemory);

    while(mapIt.hasNext())
    {
        BSArchive::addFileFromMemory(mapIt.key(), mapIt.value());
    }

    for (auto file : filesFromDisk)
    {
        BSArchive::addFileFromDisk(rootDirectory.path(), file);
    }
}


void BSArchiveAuto::addFileFromDisk(const QString &filename)
{
    add(rootDirectory.relativeFilePath(filename));
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
    add(filename);
    filesfromMemory.insert(filename, data);
}

void BSArchiveAuto::extractAll(const QString& destinationDirectory)
{
    qDebug() << BSArchive::listFiles("");
    for (auto file : BSArchive::listFiles(""))
    {
        BSArchive::extract(file, destinationDirectory + "/" + file);
    }
}

