#include "QmlFileWatcher.h"

#include <iostream>
#include <stdlib.h>
#include <boost/filesystem.hpp>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtCore/QTimer>


namespace fs = boost::filesystem;

QmlFileWatcher::QmlFileWatcher( QDeclarativeView *attachedView, const bool addSourceContainingFolder, const bool watch )
: QObject(), m_attachedView(attachedView), m_isWatching(false)
    //, m_reloadDelay(0.0f)
{
    this->setWatching(watch);

    // If the declarative view has already a source file
    if( m_attachedView->status() != QDeclarativeView::Null )
    {
        this->addFile( m_attachedView->source(), addSourceContainingFolder );
    }
}

QmlFileWatcher::~QmlFileWatcher()
{

}

void QmlFileWatcher::onQmlFileChanged(const QString &file)
{
    // Clear QMLEngine cache
    m_attachedView->engine()->clearComponentCache();

    // We remove temporarily the file from watching list
    // to prevent the case in which the editor suppress the file
    // when saving it and create a new one. This causes the
    // fileWatcher to stop listening to the file.
    this->removeFile(file);
    m_modifiedFile = file;

    updateAttachedView();

    // NO NEED : Perform the view reloading after the reload delay
    //QTimer::singleShot(m_reloadDelay, this, SLOT(updateAttachedView()));
}

void QmlFileWatcher::printWatchedFiles()
{
    for(int i = 0; i < m_watchedFiles.count(); ++i)
    {
        std::cout << m_watchedFiles.at(i).toStdString() << std::endl;
    }
}

void QmlFileWatcher::updateAttachedView()
{
    QUrl sourceUrl = m_attachedView->source();
    m_attachedView->setSource( sourceUrl );
    this->addFile(m_modifiedFile);
    m_attachedView->update();
    m_attachedView->repaint();

    Q_EMIT viewReloaded();
}

void QmlFileWatcher::addFile(const QString &filename, const bool addContainingFolder)
{
    //Get absolute filename
    fs::path absFilename( filename.toStdString());
    absFilename = fs::absolute( absFilename );

    if( ! addContainingFolder )
    {
        m_watchedFiles.push_back( QString::fromStdString( absFilename.string() ) ) ;
        if( m_isWatching )
        {
            m_qmlFileWatcher.addPath( QString::fromStdString( absFilename.string() ) );
        }
        return;
    }
    else
    {
        fs::path folder = absFilename.parent_path();
        this->addFolder( folder.string() );
    }
}

void QmlFileWatcher::addFile(const std::string &filename, const bool addContainingFolder)
{
    this->addFile( QString::fromStdString( filename ), addContainingFolder );
}

void QmlFileWatcher::addFile( const QUrl& fileUrl, const bool addContainingFolder )
{
    this->addFile( fileUrl.path(), addContainingFolder );
}

void QmlFileWatcher::addFolder(const QString &foldername)
{
    //Get absolute foldername
    fs::path absFoldername( foldername.toStdString() );
    absFoldername = fs::absolute( absFoldername );

    fs::recursive_directory_iterator end_iter;

    if ( fs::exists(absFoldername) && fs::is_directory(absFoldername))
    {
        for( fs::recursive_directory_iterator dir_iter(absFoldername) ; dir_iter != end_iter ; ++dir_iter)
        {
            if( fs::is_regular_file(dir_iter->status()) && fs::extension(dir_iter->path()) == ".qml" )
            {
                this->addFile( dir_iter->path().string() );
            }
        }
    }
}

void QmlFileWatcher::addFolder(const std::string &foldername)
{
    this->addFolder( QString::fromStdString( foldername ) );
}

void QmlFileWatcher::addFolder(const QUrl &foldername)
{
    this->addFolder( foldername.path() );
}


void QmlFileWatcher::removeFile(const QString &filename)
{
    fs::path absFilename( filename.toStdString() );
    absFilename = fs::absolute( absFilename );
    QString absname = QString::fromStdString( absFilename.string() );

    bool result = m_watchedFiles.removeOne( absname );

    // If the file is indeed watched and if watching is enabled
    if(result && m_isWatching)
    {
        m_qmlFileWatcher.removePath( absname );
    }
}

void QmlFileWatcher::removeFile(const std::string &filename)
{
    this->removeFile( QString::fromStdString( filename ) );
}

void QmlFileWatcher::removeFile(const QUrl &fileUrl)
{
    this->removeFile( fileUrl.path() );
}

void QmlFileWatcher::enableWatch()
{
    if( !m_watchedFiles.empty() )
    {
        m_qmlFileWatcher.addPaths( m_watchedFiles );
    }
    connect( &m_qmlFileWatcher, SIGNAL( fileChanged( const QString & ) ), this, SLOT( onQmlFileChanged( const QString & ) ) );
}

void QmlFileWatcher::disableWatch()
{
    m_qmlFileWatcher.removePaths( m_watchedFiles );
    disconnect( &m_qmlFileWatcher, SIGNAL( fileChanged( const QString & ) ), this, SLOT( onQmlFileChanged( const QString & ) ) );
}

void QmlFileWatcher::setWatching(const bool watching)
{
    if(watching == m_isWatching)
    {
        return;
    }
    m_isWatching = watching;
    if( m_isWatching )
    {
        enableWatch();
    }
    else
    {
        disableWatch();
    }
}

