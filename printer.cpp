#include <QDebug>
#include <QFile>
#include <QPainter>
#include <QPageLayout>
#include <QPrinter>
#include <QPrinterInfo>
#include <QScopedPointer>
#include <poppler/qt5/poppler-qt5.h>

#include "printer.hpp"

Printer::Printer(const QStringList &files, QObject *parent)
    : QObject{parent}
    , m_files(files)
{

}

void Printer::setFiles(const QStringList &files)
{
    m_files = files;
}

void Printer::print()
{
    QPrinter printer(QPrinterInfo::defaultPrinter(), QPrinter::HighResolution);
    printer.setPageOrientation(QPageLayout::Portrait);
    printer.pageLayout().setPageSize(QPageSize::Letter);
    QPainter painter(&printer);

    const auto DPI = 1'150.0;
    const int x = 10;
    const int y = 10;
    for (const auto &file : m_files) {
        QScopedPointer<Poppler::Document> document(Poppler::Document::load(file));
        document->setRenderHint(Poppler::Document::TextAntialiasing);
        document->setRenderBackend(Poppler::Document::QPainterBackend);

        for (int i {}; i < document->numPages(); ++i) {
            QScopedPointer<Poppler::Page> page(document->page(i));
            auto size = page->pageSize();
            auto width = size.width() / 72.0 * 96.0;
            auto height = size.height() / 72.0 * 96.0;
            page->renderToPainter(&painter, DPI, DPI, x, y, width, height);
        }
    }
}

void Printer::remove()
{
    for (const auto &file : m_files) {
        QFile::remove(file);
    }
}
