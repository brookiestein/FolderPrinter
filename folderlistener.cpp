#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QFileDialog>
#include <QStandardPaths>

#include "folderlistener.hpp"
#include "printer.hpp"

void signalHandler(int signal);

FolderListener::FolderListener(QObject *parent)
    : QObject{parent}
    , m_watcher(parent)
{
    m_configFile = QString("%1%2%3%4%5")
                       .arg(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation),
                            QDir::separator(),
                            PROGRAM_NAME,
                            QDir::separator(),
                            PROGRAM_NAME".ini"
                            );

    m_settings = new QSettings(m_configFile, QSettings::IniFormat, this);
    m_settings->beginGroup("Listen");
    setListenPath();

    m_watcher.addPath(m_listenPath);

    connect(&m_watcher, &QFileSystemWatcher::directoryChanged, this, &FolderListener::directoryChanged);
}

FolderListener::~FolderListener()
{
    m_settings->endGroup();
}

void FolderListener::setListenPath()
{
    auto d = QDir();
    if (m_settings->allKeys().isEmpty()) {
        auto desktop = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        auto path = QFileDialog::getExistingDirectory(nullptr,
                                                      tr("Elige la carpeta desde donde imprimir"),
                                                      desktop,
                                                      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

        if (path.isEmpty()) {
            path = QString("%1%2%3").arg(desktop, QDir::separator(), PROGRAM_NAME);
            if (not d.mkpath(path)) {
                qFatal("No se pudo crear la carpeta de trabajo. Saliendo.");
            }
        }

        m_listenPath = path;
        m_settings->setValue("Path", m_listenPath);
    } else {
        m_listenPath = m_settings->value("Path").toString();
    }
}

void FolderListener::directoryChanged(const QString &path)
{
    auto d = QDir(path);
    auto entries = d.entryList(QDir::Filter::Files);

    if (entries.empty()) {
        return;
    }

    QStringList files;

    for (auto file : entries) {
        files << QString("%1%2%3").arg(path, QDir::separator(), file);
    }

    auto p = Printer(files);
    p.print();
    p.remove();
}
