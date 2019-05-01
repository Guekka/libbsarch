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

void BSArchiveAuto::extractAll(const QString& destinationDirectory, const bool &overwriteExistingFiles)
{
    for (auto file : BSArchive::listFiles())
    {
        QFile currentFile(destinationDirectory + "/" + file);
        rootDirectory.mkpath(destinationDirectory + "/" + QFileInfo(file).path());
        if(currentFile.exists() && overwriteExistingFiles)
        {
            currentFile.remove();
            BSArchive::extract(file, currentFile.fileName());
        }
        else if (!currentFile.exists())
            BSArchive::extract(file, currentFile.fileName());
    }
}

void BSArchiveAuto::reset()
{
    BSArchive::reset();
    BSArchiveEntries::reset();

}
