#ifndef QMLFILEWATCHER_H
#define QMLFILEWATCHER_H

#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtCore/QFileSystemWatcher>
#include <QtDeclarative/QDeclarativeView>


class QmlFileWatcher : public QObject
{
    /**
    *  @brief QmlFileWatcher is a utility class meant to be used along with a QDeclarativeView.
    *         It automatically updates this view when a watched QML files is modified.
    */
    Q_OBJECT

public:

    /**
    *  @brief QmlFileWatcher constructor.
    *
    *  @param attachedView : the declarative view using this QmlFileWatcher
    *  @note if attachedView has already a source, it will be automatically added to the watched file list
    *
    */
    QmlFileWatcher( QDeclarativeView *attachedView, const bool addSourceContainingFolder = false, const bool watch = true );
    ~QmlFileWatcher();

    /**
     * @brief add a qml file to the watching list. Attached view will be reloaded if this file is modified
     *
     */
    void addFile( const std::string& filename, const bool addContainingFolder = false );
    void addFile( const QString& filename, const bool addContainingFolder = false );
    void addFile( const QUrl& fileUrl, const bool addContainingFolder = false );

    /**
     * @brief add all qml files from folder and its subfolders (recursive) to the watching list.
     *        Attached view will be reloaded if any of this file is modified.
     */
    void addFolder( const std::string& folderPath );
    void addFolder( const QString& folderPath );
    void addFolder( const QUrl &foldername );

    void removeFile( const std::string& filename );
    void removeFile( const QString& filename );
    void removeFile( const QUrl& fileUrl );

    void setWatching(const bool watching);
    const bool isWatching() const { return m_isWatching; }

    const QStringList& watchedFiles() const { return m_watchedFiles; }

    /**
     * @brief set the delay (ms) after which the attached view will be reloaded (100 by default).
     *        Useful to get over slow saving software.
     *
     */
    void setReloadDelay(const unsigned int delay);
    const float reloadDelay() const { return m_reloadDelay; }

    void printWatchedFiles();

Q_SIGNALS:
    void viewReloaded();

private Q_SLOTS:
    /**
     * @brief: handles attached declarative view reloading
     */
    void onQmlFileChanged( const QString &file );
    void updateAttachedView();

private:
    void enableWatch();
    void disableWatch();


private:
    QFileSystemWatcher m_qmlFileWatcher;
    QDeclarativeView* m_attachedView;
    QStringList m_watchedFiles;
    QString m_modifiedFile;
    bool m_isWatching;
    unsigned int m_reloadDelay;
};


#endif // QMLFILEWATCHER_H
