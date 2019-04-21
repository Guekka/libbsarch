#ifndef BSARCHIVEAUTO_H
#define BSARCHIVEAUTO_H

#include "BSArchive.h"
#include "BSArchiveEntries.h"
/*!
 * \brief A convenience class for BSArchive and BSArchiveEntries. Its performance is worse than using these two classes separately, but it removes the need to manually handle
 * the BSArchiveEntries.
 */
class BSArchiveAuto : public BSArchiveEntries, public BSArchive
{
public:
    /*!
     * \brief Constructor
     * \param rootDirectory The root directory of the BSA. This directory is the one containing folders such as textures and meshes.
     */
    BSArchiveAuto(const QString &rootDirectory);
    /*!
     * \brief Creates a BSA in memory
     * \param archiveName The BSA name
     * \param type The BSA type
     */
    void create(const QString& archiveName, const bsa_archive_type_e& type);
    /*!
     * \brief Adds a file from the disk to the BSA. Also adds it to the BSA entries.
     * \param rootDir The root directory of the file.
     * \param filename The complete path to the file.
     */
    void addFileFromDisk(const QString& filename);
    /*!
     * \brief Adds files from the disk to the BSA. Also adds them to the BSA entries.
     * \param rootDir The root directory of the file. This directory is the one containing folders such as textures and meshes.
     * \param files A list containing the complete paths to the files.
     */
    void addFileFromDisk(const QStringList& files);
    /*!
     * \brief Adds file: from the memory to the BSA. Also adds it to the BSA entries.
     * \param filename The name of the file. It connot be a full path, and has to be a relative path.
     * \param data The file bytes data.
     */
    void addFileFromMemory(const QString& filename, const QByteArray& data);
    /*!
     * \brief Extracts all files from the BSA to the destination.
     * \param destinationDirectory The directory where all files will be extracted.
     */
    void extractAll(const QString& destinationDirectory);
private:
    QStringList filesFromDisk;
    QMap<QString, QByteArray> filesfromMemory;
    QDir rootDirectory;

};

#endif // BSARCHIVEAUTO_H
