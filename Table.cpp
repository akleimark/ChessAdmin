#include "Table.h"
#include <QHeaderView>

Table::Table(const QStringList &columnNames, QWidget *parent):
    QTableWidget(0, columnNames.size(), parent)
{
    setColumnCount(columnNames.size());
    setHorizontalHeaderLabels(columnNames);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    //setFocusPolicy(Qt::NoFocus);


    //QPalette palette = this->palette();
    //palette.setBrush(QPalette::Highlight,QBrush(Qt::white));
    //palette.setBrush(QPalette::HighlightedText,QBrush(Qt::black));
    //this->setPalette(palette);
}
