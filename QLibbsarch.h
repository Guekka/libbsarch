#ifndef QLIBBSARCH_H
#define QLIBBSARCH_H

#include "libbsarch.h"
#include <QString>

static wchar_t *QStringToWchar(const QString& Qstring);

class BSArchiveEntries
{
public:
    BSArchiveEntries();
    ~BSArchiveEntries();

private:
    bsa_entry_list_t entries;
};

class BSArchive
{
public:
    BSArchive(BSArchiveEntries entries);
    ~BSArchive();

    bsa_result_message_t openArchive(const QString& archivePath);
    bsa_result_message_t create(const QString& archiveName, bsa_archive_type_e type);
    bsa_result_message_t save();
    bsa_result_message_t addFileFromDisk(const QString& rootDir, const QString& filename);
    //bsa_archive_t archive, const wchar_t *root_dir, const wchar_t *filename


private:
    bsa_archive_t archive;
    BSArchiveEntries entries;

};

#endif // QLIBBSARCH_H


