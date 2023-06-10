#ifndef CSVMODEL_H
#define CSVMODEL_H

#include <QAbstractTableModel>
#include <QStringList>

class CsvModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    CsvModel(QObject *parent = nullptr);

    void loadCsv(const QString &filename);
    bool saveCsv(const QString &filePath);
    void addRow(const QStringList& rowData);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    static QString monthNumberToText(int monthNumber);

private:
    QStringList m_header;
    QList<QStringList> m_data;

    QMap<int, QString> m_monthMap;

};

#endif // CSVMODEL_H
