#ifndef EXPLORER_H
#define EXPLORER_H
#include <QDir>
#include <QModelIndex>

class QViewExplorer: public QAbstractListModel
{
public:
    QViewExplorer(QObject *parent=nullptr);
    int rowCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;

    void getFolderList(QString folderPath, QFileInfoList *dirList);

private:
    QFileInfoList *aDirList;

};
#endif // EXPLORER_H
