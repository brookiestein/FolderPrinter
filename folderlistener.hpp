#ifndef FOLDERLISTENER_HPP
#define FOLDERLISTENER_HPP

#include <QFileSystemWatcher>
#include <QObject>
#include <QSettings>
#include <QTimer>

class FolderListener : public QObject
{
    Q_OBJECT
    QString m_configFile;
    QString m_listenPath;
    QSettings *m_settings;
    QFileSystemWatcher m_watcher;

    void setListenPath();
private slots:
    void directoryChanged(const QString &path);
public:
    explicit FolderListener(QObject *parent = nullptr);
    ~FolderListener();
};

#endif // FOLDERLISTENER_HPP
