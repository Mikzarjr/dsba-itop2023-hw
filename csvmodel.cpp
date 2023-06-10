#include "csvmodel.h"
#include <QFile>
#include <QTextStream>

CsvModel::CsvModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void CsvModel::loadCsv(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()){
        QString line = in.readLine();
        QStringList fields;
        int start = 0;
        bool inQuotes = false;
        for (int i = 0; i < line.length(); i++){
            if (line[i] == '"')
                inQuotes = !inQuotes;
            else if (line[i] == ',' && !inQuotes) {
                fields.append(line.mid(start, i - start).remove('"'));
                start = i + 1;
            }
        }

        fields.append(line.mid(start).remove('"'));

        if (m_header.isEmpty())
            m_header = fields;
        else
            m_data.append(fields);
    }

    file.close();

    beginResetModel();
    endResetModel();
}

bool CsvModel::saveCsv(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }

    QTextStream out(&file);

    out << m_header.join(",") << "\n";

    for (const QStringList &rowData : m_data)
    {
        out << rowData.join(",") << "\n";
    }

    file.close();

    return true;
}

void CsvModel::addRow(const QStringList& rowData)
{
    beginInsertRows(QModelIndex(), 0, 0);
    m_data.prepend(rowData);
    endInsertRows();
}

int CsvModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

int CsvModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_header.count();
}

QVariant CsvModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
        return m_data.at(index.row()).at(index.column());
    return QVariant();
}

QVariant CsvModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        return m_header.at(section);
    return QVariant();
}
