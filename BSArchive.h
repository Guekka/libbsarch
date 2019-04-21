#ifndef BSARCHIVE_H
#define BSARCHIVE_H

#include "QLibbsarch.h"
#include "BSArchiveEntries.h"

class BSArchive
{
public:
    BSArchive();
    virtual ~BSArchive();

    void open(const QString& archivePath);
    void close();
    virtual void create(const QString& archiveName, const bsa_archive_type_e &type, const BSArchiveEntries &entries);
    void save();
    void addFileFromDisk(const QString& rootDir, const QString& filename);
    void addFileFromDisk(const QString& rootDir, const QStringList& files);
    void addFileFromMemory(const QString& filename, const QByteArray& data);
    void setCompressed(bool value);
    void setShareData(bool value);
    bsa_file_record_t findFileRecord (const QString& filename);
    bsa_result_message_buffer_t extractFileDataByRecord(bsa_file_record_t record);
    bsa_result_message_buffer_t extractFileDataByFilename(const QString& filename);
    void extract(const QString& filename, const QString& saveAs);
    QStringList listFiles(const QString& folder);


    bsa_archive_t getArchive() const;

private:
    bsa_archive_t m_archive;

};

#endif // BSARCHIVE_H
