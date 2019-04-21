#include "BSArchive.h"

BSArchive::BSArchive() : m_archive (bsa_create()) {}

BSArchive::~BSArchive()
{
    bsa_free(m_archive);
}

void BSArchive::open(const QString &archivePath) //Untested
{
    const wchar_t *path = QStringToWchar( QDir::toNativeSeparators(archivePath) );
    auto result = bsa_load_from_file(m_archive, path);

    if(result.code == BSA_RESULT_EXCEPTION)
        throw std::runtime_error(wcharToString(result.text));
}

void BSArchive::close()
{
    bsa_close(m_archive);
}

void BSArchive::create(const QString &archiveName, const bsa_archive_type_e& type, const BSArchiveEntries& entries)
{
    const wchar_t *path = QStringToWchar( QDir::toNativeSeparators(archiveName) );
    bsa_create_archive(m_archive, path, type, entries.getEntries());
}


void BSArchive::save()
{
    auto result = bsa_save(m_archive);

    if(result.code == BSA_RESULT_EXCEPTION)
        throw std::runtime_error(wcharToString(result.text));
}

void BSArchive::addFileFromDisk(const QString &rootDir, const QString &filename)
{
    const wchar_t *rootPath = QStringToWchar( QDir::toNativeSeparators( rootDir));
    const wchar_t *path = QStringToWchar( QDir::toNativeSeparators(filename) );
    auto result = bsa_add_file_from_disk(m_archive, rootPath, path);

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
    auto result = bsa_add_file_from_memory(m_archive, path, size, buffer);

    if(result.code == BSA_RESULT_EXCEPTION)
        throw std::runtime_error(wcharToString(result.text));
}

void BSArchive::setCompressed(bool value)
{
    bsa_compress_set(m_archive, value);
}

void BSArchive::setShareData(bool value)
{
    bsa_share_data_set(m_archive, value);
}

bsa_file_record_t BSArchive::findFileRecord(const QString &filename)
{
    const wchar_t *path = QStringToWchar( QDir::toNativeSeparators(filename) );
    return bsa_find_file_record(m_archive, path);
}

bsa_result_message_buffer_t BSArchive::extractFileDataByRecord(bsa_file_record_t record)
{
    return bsa_extract_file_data_by_record(m_archive, record);
}

bsa_result_message_buffer_t BSArchive::extractFileDataByFilename(const QString &filename)
{
    const wchar_t *path = QStringToWchar( QDir::toNativeSeparators(filename) );
    return bsa_extract_file_data_by_filename(m_archive, path);
}

void BSArchive::extract(const QString &filename, const QString &saveAs) //FIXME
{
    const wchar_t *path = QStringToWchar( QDir::toNativeSeparators(filename) );
    const wchar_t *extractedPath = QStringToWchar( QDir::toNativeSeparators(saveAs) );

    auto result = bsa_extract_file(m_archive, path, extractedPath);

    if(result.code == BSA_RESULT_EXCEPTION)
        throw std::runtime_error(wcharToString(result.text));
}

QStringList BSArchive::listFiles(const QString &folder)
{
    bsa_entry_list_t list = bsa_entry_list_create();
    const wchar_t *folderPath = QStringToWchar( QDir::toNativeSeparators(folder) );
    auto result = bsa_get_resource_list(m_archive, list, folderPath);

    if(result.code == BSA_RESULT_EXCEPTION)
        throw std::runtime_error(wcharToString(result.text));

    return BSArchiveEntries(list).list();
}

bsa_archive_t BSArchive::getArchive() const
{
    return m_archive;
}
