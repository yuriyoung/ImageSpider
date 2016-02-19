#include "DownloadView.h"
#include <QDebug>

DownloadView::DownloadView(QWidget *parent) :
    QTreeWidget(parent)
{
    QStringList headers;
    headers << tr("#") << tr("Title") << tr("Progress")
            << tr("Rate") << tr("Size") << tr("Status") << tr("MD5");

    this->setHeaderLabels(headers);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setAlternatingRowColors(true);
    this->setRootIsDecorated(false);
//    this->setSortingEnabled(true);
//    this->sortByColumn(0, Qt::AscendingOrder);

    // Set header resize modes and initial section sizes
    QFontMetrics fm = fontMetrics();
    QHeaderView *header = this->header();
    header->resizeSection(0, 30);
    header->resizeSection(1, fm.width(headers.at(0) + "heaer-for-a-file-name.jpg"));
    header->resizeSection(2, fm.width(headers.at(1) + "==================="));
    header->resizeSection(3, qMax(fm.width(headers.at(2)), fm.width(" 1234.0 KB/s ")));
    header->resizeSection(4, qMax(fm.width(headers.at(3)), fm.width(" 1234.0 KB ")));
    header->resizeSection(5, qMax(fm.width(headers.at(4) + "---"), fm.width(tr("Downloading") + "------")));
    header->resizeSection(6, 20);

//    for(int i = 0; i < 20; ++i)
//    {
//        QTreeWidgetItem *item = new QTreeWidgetItem(this);
//        item->setText(0, QString("%1").arg(i));
//        item->setText(1, QString("Unknow Name %1").arg(i));
//        item->setText(2, QString("%1.0 KB/s").arg(i));
//        item->setText(3, QString("%1.0 KB").arg(i));
//        item->setText(4, tr("000KB"));
//        item->setText(5, tr("Downloading"));
//    }
}


