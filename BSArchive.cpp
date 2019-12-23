#include "BSArchive.h"

namespace Qlibbsarch {
BSArchive::BSArchive()
    : _archive(bsa_create())
{
}

BSArchive::~BSArchive()
{
    if (_openedArchive)
        close();
    free();
}

void BSArchive::free()
{
    LOG_LIBBSARCH << "Freeing archive: " << _archive;

    const auto &result = bsa_free(_archive);
    _openedArchive = false;

    Qlibbsarch::checkResult(result);
}

void BSArchive::open(const QString &archivePath)
{
    LOG_LIBBSARCH << "Opening archive: " << archivePath;

    const auto &result = bsa_load_from_file(_archive, PREPARE_PATH_LIBBSARCH(archivePath));
    _openedArchive = true;

    Qlibbsarch::checkResult(result);
}

void BSArchive::close()
{
    LOG_LIBBSARCH << "Closing archive: " << _archive;

    bsa_close(_archive);
    _openedArchive = false;
}

void BSArchive::create(const QString &archiveName, const bsa_archive_type_e &type, const BSArchiveEntries &entries)
{
    LOG_LIBBSARCH << "Creating archive. Archive name: " << archiveName << endl
                  << "type: " << type << endl
                  << "entries: " << entries.getEntries();

    bsa_create_archive(_archive, PREPARE_PATH_LIBBSARCH(archiveName), type, entries.getEntries());

    _openedArchive = true;
}

void BSArchive::save() const
{
    LOG_LIBBSARCH << "Saving archive: " << _archive;

    const auto &result = bsa_save(_archive);

    Qlibbsarch::checkResult(result);
}

void BSArchive::addFileFromDiskRoot(const QString &rootDir, const QString &filename)
{
    LOG_LIBBSARCH << "Adding file from disk root. Root directory: " << rootDir << endl
                  << "Filename: " << filename << endl
                  << "Archive: " << _archive;

    const auto &result = bsa_add_file_from_disk_root(_archive,
                                                     PREPARE_PATH_LIBBSARCH(rootDir),
                                                     PREPARE_PATH_LIBBSARCH(filename));

    Qlibbsarch::checkResult(result);
}

void BSArchive::addFileFromDiskRoot(const QString &rootDir, const QStringList &files)
{
    for (const auto &file : files)
        addFileFromDiskRoot(rootDir, file);
}

void BSArchive::addFileFromDisk(const QString &pathInArchive, const QString &filePath)
{
    LOG_LIBBSARCH << "Adding file from disk root. Path in archive: " << pathInArchive << endl
                  << "Filepath: " << filePath << endl
                  << "Archive: " << _archive;

    const auto &result = bsa_add_file_from_disk_root(_archive,
                                                     PREPARE_PATH_LIBBSARCH(pathInArchive),
                                                     PREPARE_PATH_LIBBSARCH(filePath));

    Qlibbsarch::checkResult(result);
}

void BSArchive::addFileFromMemory(const QString &filename, const QByteArray &data) //NOTE UNTESTED
{
    LOG_LIBBSARCH << "Adding file from memory. Filename: " << filename << endl << "Data size: " << data.size();

    uint32_t size = static_cast<uint32_t>(data.size());
    bsa_buffer_t buffer = const_cast<char *>(data.data());
    const auto &result = bsa_add_file_from_memory(_archive, PREPARE_PATH_LIBBSARCH(filename), size, buffer);

    Qlibbsarch::checkResult(result);
}
void BSArchive::setCompressed(bool value)
{
    LOG_LIBBSARCH << "Setting compressed flag to " << value;
    bsa_compress_set(_archive, value);
}

void BSArchive::setShareData(bool value)
{
    LOG_LIBBSARCH << "Setting share data flag to " << value;
    bsa_share_data_set(_archive, value);
}

bsa_file_record_t BSArchive::findFileRecord(const QString &filename)
{
    LOG_LIBBSARCH << "Finding file record of: " << filename;
    const auto &result = bsa_find_file_record(_archive, PREPARE_PATH_LIBBSARCH(filename));
    return result;
}

QByteArray BSArchive::extractFileDataByRecord(bsa_file_record_t record)
{
    const auto &result = bsa_extract_file_data_by_record(_archive, record);

    Qlibbsarch::checkResult(result);

    char *buffer = static_cast<char *>(result.buffer.data);
    int size = static_cast<int>(result.buffer.size);

    QByteArray byte_array(buffer, size);
    return byte_array;
}

QByteArray BSArchive::extractFileDataByFilename(const QString &filename)
{
    const auto &result = bsa_extract_file_data_by_filename(_archive, PREPARE_PATH_LIBBSARCH(filename));

    Qlibbsarch::checkResult(result);

    char *buffer = static_cast<char *>(result.buffer.data);
    int size = static_cast<int>(result.buffer.size);

    QByteArray byte_array(buffer, size);
    return byte_array;
}

void BSArchive::extract(const QString &filename, const QString &saveAs) const
{
    qDebug() << "Extracting: " << filename << " saved as " << saveAs;
    const auto &result = bsa_extract_file(_archive, PREPARE_PATH_LIBBSARCH(filename), PREPARE_PATH_LIBBSARCH(saveAs));

    Qlibbsarch::checkResult(result);
}

QStringList BSArchive::listFiles() const
{
    bsa_entry_list_t list = bsa_entry_list_create();
    const auto &result = bsa_get_resource_list(_archive, list, L"");

    Qlibbsarch::checkResult(result);

    return BSArchiveEntries(list).list();
}

bsa_archive_t BSArchive::getArchive() const
{
    return _archive;
}

void BSArchive::reset()
{
    free();
    _archive = bsa_create();
}

void BSArchive::setDDSCallback(bsa_file_dds_info_proc_t file_dds_info_proc, void *context)
{
    LOG_LIBBSARCH << "Setting DDS callback for archive: " << _archive << "\nCallback adress: " << &file_dds_info_proc;
    bsa_file_dds_info_callback_set(_archive, file_dds_info_proc, context);
}
} // namespace Qlibbsarch
