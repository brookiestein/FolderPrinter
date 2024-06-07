#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <QObject>
#include <QStringList>

class Printer : public QObject
{
    Q_OBJECT
    QStringList m_files;
public:
    explicit Printer(const QStringList &files = QStringList(), QObject *parent = nullptr);
    void setFiles(const QStringList &files);
    void print();
    void remove();
};

#endif // PRINTER_HPP
