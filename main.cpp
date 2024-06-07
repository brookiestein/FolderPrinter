#include <QApplication>

#include "folderlistener.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto listener = FolderListener();
    Q_UNUSED(listener);
    return a.exec();
}
