#include "QLibbsarch.h"

wchar_t *QStringToWchar(const QString& Qstring)
{
    wchar_t *array = new wchar_t (sizeof (Qstring));
    Qstring.toWCharArray(array);
    return array;
}



BSArchiveEntries::BSArchiveEntries() : entries (bsa_entry_list_create()) {}

BSArchiveEntries::~BSArchiveEntries()
{
    bsa_entry_list_free(entries);
}


BSArchive::BSArchive(BSArchiveEntries entries) : archive (bsa_create()), entries (entries) {}

BSArchive::~BSArchive()
{
    bsa_free(archive);
    bsa_entry_list_free(archive);
    delete entries;

}

bsa_result_message_t BSArchive::openArchive(const QString &archivePath)
{
    return bsa_load_from_file(archive, QStringToWchar(archivePath));
}

bsa_result_message_t BSArchive::save()
{
    return bsa_save(archive);
}

bsa_result_message_t BSArchive::addFileFromDisk(const QString &rootDir, const QString &filename)
{
    return bsa_add_file_from_disk(archive, QStringToWchar(rootDir), QStringToWchar(filename));
}

