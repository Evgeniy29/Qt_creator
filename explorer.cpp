#include "explorer.h"
#include <QPixmap>

QViewExplorer::QViewExplorer(QObject *parent)
    :QAbstractListModel(parent)
{

}

void QViewExplorer::getFolderList(QString folderPath, QFileInfoList *dirList)
{
    QDir dir = QDir(folderPath);

    *dirList = dir.entryInfoList(QDir::NoDot | QDir::Files | QDir::Dirs, QDir::DirsFirst);

    this->beginResetModel();
        this->aDirList = dirList;
    this->endResetModel();
}

int QViewExplorer::rowCount(const QModelIndex &) const
{
    return this->aDirList->count();
}

QVariant QViewExplorer::data( const QModelIndex &index, int role ) const
{

    QVariant value;

        switch ( role )
        {
            case Qt::DisplayRole:
            {
                value = this->aDirList->at(index.row()).fileName();
            }
            break;

            case Qt::DecorationRole:
            {
                if (this->aDirList->at(index.row()).isDir()) {
                    QPixmap icon = QPixmap(":/file_folder.png");
                    QPixmap tmp = icon.scaled(30, 30, Qt::KeepAspectRatio);
                    value = tmp;
                    break;
                }

                if (this->aDirList->at(index.row()).isFile()) {
                    QString fileExt = this->aDirList->at(index.row()).completeSuffix();


                    QPixmap icon = QPixmap(":/file_file.png");
                    QPixmap tmp = icon.scaled(25, 25, Qt::KeepAspectRatio);
                    value = tmp;
                    break;
                }

                value = this->aDirList->at(index.row()).fileName();
            }
            break;

            case Qt::UserRole:
            {
                value = this->aDirList->at(index.row()).fileName();
            }
            break;

            default:
                break;
        }

    return value;
}
