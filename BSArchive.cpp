#include "BSArchive.h"
#include "QLibbsarch.h"

BSArchive::BSArchive() : archive (bsa_create()) {}

BSArchive::~BSArchive()
{
    bsa_free(archive);
}

void BSArchive::open(const QString &archivePath) //Untested
{
    const wchar_t *path = QStringToWchar( QDir::toNativeSeparators(archivePath) );
    auto result = bsa_load_from_file(archive, path);

    if(result.code == BSA_RESULT_EXCEPTION)
        throw std::runtime_error(wcharToString(result.text));
}

void BSArchive::close() const
{
    bsa_close(archive);
}

void BSArchive::create(const QString &archiveName, bsa_archive_type_e type, BSArchiveEntries entries)
{
    const wchar_t *path = QStringToWchar( QDir::toNativeSeparators(archiveName) );
    bsa_create_archive(archive, path, type, entries.getEntries());
}


void BSArchive::save() const
{
    auto result = bsa_save(archive);

    if(result.code == BSA_RESULT_EXCEPTION)
        throw std::runtime_error(wcharToString(result.text));
}

void BSArchive::addFileFromDisk(const QString &rootDir, const QString &filename)
{
    const wchar_t *path = QStringToWchar( QDir::toNativeSeparators(filename) );
    auto result = bsa_add_file_from_disk(archive, QStringToWchar(rootDir), path);

    if(result.code == BSA_RESULT_EXCEPTION)
        throw std::runtime_error(wcharToString(result.text));
}


void BSArchive::addFileFromDisk(const QString &rootDir, const QStringList& files)
{
    for (auto file : files)
    {
        addFileFromDisk(rootDir, file);
    }
}

void BSArchive::addFileFromMemory(const QString &filename, const QByteArray &data) //Untested
{
    uint32_t size = static_cast<uint32_t>(data.size());
    bsa_buffer_t buffer = const_cast<char*>(data.data());
    const wchar_t *path = QStringToWchar( QDir::toNativeSeparators(filename) );
    auto result = bsa_add_file_from_memory(archive, path, size, buffer);

    if(result.code == BSA_RESULT_EXCEPTION)
        throw std::runtime_error(wcharToString(result.text));
}

void BSArchive::setCompressed(bool value)
{
    bsa_compress_set(archive, value);
}

