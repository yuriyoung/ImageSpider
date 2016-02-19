#ifndef DOWNLOADVIEW_H
#define DOWNLOADVIEW_H

#include "MainWindow.h"
#include <QWidget>
#include <QTreeWidget>
#include <QItemDelegate>
#include <QApplication>
#include <QHeaderView>

class DownloadView : public QTreeWidget
{
    Q_OBJECT
public:
    DownloadView(QWidget *parent = 0);

};

class DownloadingViewDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    inline DownloadingViewDelegate(MainWindow *mainWidnow)
        : QItemDelegate(mainWidnow)
    {

    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index ) const Q_DECL_OVERRIDE
    {
        if (index.column() != 2)
        {
            QItemDelegate::paint(painter, option, index);
            return;
        }

        // Set up a QStyleOptionProgressBar to precisely mimic the
        // environment of a progress bar.
        QStyleOptionProgressBarV2 progressBarOption;
        progressBarOption.state = QStyle::State_Enabled;
        progressBarOption.direction = QApplication::layoutDirection();
        progressBarOption.rect = option.rect;
        progressBarOption.fontMetrics = QApplication::fontMetrics();
        progressBarOption.minimum = 0;
        progressBarOption.maximum = 100;
        progressBarOption.textAlignment = Qt::AlignCenter;
        progressBarOption.textVisible = true;

        // Set the progress and text values of the style option.
        QString md5 = index.data(Qt::UserRole+1).toString();
        int progress = qobject_cast<MainWindow *>(parent())->imageForMd5(md5)->progress;
        progressBarOption.progress = progress < 0 ? 0 : progress;
        progressBarOption.text = QString::asprintf("%d%%", progressBarOption.progress);

        // Draw the progress bar onto the view.
        QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter);
    }
};

class DownloadedViewDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    inline DownloadedViewDelegate(MainWindow *mainWidnow)
        : QItemDelegate(mainWidnow)
    {

    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index ) const Q_DECL_OVERRIDE
    {
        if (index.column() != 2)
        {
            QItemDelegate::paint(painter, option, index);
            return;
        }

        // Set up a QStyleOptionProgressBar to precisely mimic the
        // environment of a progress bar.
        QStyleOptionProgressBarV2 progressBarOption;
        progressBarOption.state = QStyle::State_Enabled;
        progressBarOption.direction = QApplication::layoutDirection();
        progressBarOption.rect = option.rect;
        progressBarOption.fontMetrics = QApplication::fontMetrics();
        progressBarOption.minimum = 0;
        progressBarOption.maximum = 100;
        progressBarOption.textAlignment = Qt::AlignCenter;
        progressBarOption.textVisible = true;
        progressBarOption.progress = 100;
        progressBarOption.text = QString::asprintf("%d%%", progressBarOption.progress);

        // Draw the progress bar onto the view.
        QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter);
    }
};

#endif // DOWNLOADVIEW_H
