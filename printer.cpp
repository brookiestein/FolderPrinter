#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QMimeDatabase>
#include <QMimeType>
#include <QPainter>
#include <QPrinter>
#include <QPrinterInfo>
#include <QScopedPointer>
#include <poppler-qt6.h>

#include "printer.hpp"

Printer::Printer(const QStringList &files, QObject *parent)
    : QObject{parent}
    , m_files(files)
{
}

/* I don't think I'll use this function, but just for completeness... */
void Printer::setFiles(const QStringList &files)
{
    m_files = files;
}

void Printer::print()
{
    QPrinter printer(QPrinterInfo::defaultPrinter(), QPrinter::HighResolution);
    QPainter painter;

    printer.setPageOrientation(QPageLayout::Portrait);
    auto pageLayout = printer.pageLayout();
    pageLayout.setPageSize(QPageSize::Letter);
    printer.setPageLayout(pageLayout);

    /* Linux and Windows seem to treat a little bit different the concept of DPI.
     * Linux requires a higher value than what I've seen is "more popular".
     */
#ifdef Q_OS_WIN
    const auto DPI = 580.0;
#else
    const auto DPI = 1'150.0;
#endif
    for (const auto &file : m_files) {
        QMimeDatabase mimeDatabase;
        QMimeType type = mimeDatabase.mimeTypeForFile(file);

        if (type.name() != "application/pdf") {
            qCritical().noquote() << "File:" << file << "is not a PDF file.";
            continue;
        }

        auto document = Poppler::Document::load(file);

        /* Print from last page to first page.
         * IMO, and the printers I work with give me reasons to think that,
         * it's better to print this way because when done, I pick all
         * pages from the beginning to the end, i.e. my natural way of reading a document.
         */
        for (int i = document->numPages() - 1; i >= 0; --i) {
            painter.begin(&printer);
            auto page = document->page(i);
            /* Render to a QImage and the draw it to the printer.
             * I had troubles rendering to the printer directly on Windows.
             * On Linux that problem doesn't exist.
             * So according to Qt Documentation: _Rendering to a QImage gives
             * a platform-independent render._
             */
            QImage image = page->renderToImage(DPI, DPI);
            painter.drawImage(QPoint(0, 0), image);
            painter.end();
        }
    }
}

void Printer::remove()
{
    for (const auto &file : m_files) {
        QFile::remove(file);
    }
}
