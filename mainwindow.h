#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QGraphicsView>
#include <QPushButton>
#include <QStackedWidget>
#include <QSet>
#include "csvmodel.h"
#include "addrowdialog.h"
#include "aboutwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void showArtistInfo(const QModelIndex &index);
    void showAlbumInfo(const QString &albumName);
    void toggleFavorite(const QString &link);
    void albumClicked(const QModelIndex &index);
    void filterTable(const QString &text);
    void resetTable();
    void showFavorites();
    void openAddRowDialog();

private:
    CsvModel *csvModel;
    QTableView *tableView;
    QSortFilterProxyModel *proxyModel;
    QLineEdit *searchBar;
    QComboBox *categoryBox;
    QGraphicsView *logoView;
    QLabel *artistInfoLabel;
    QPushButton *backButton;
    QWidget *artistInfoWidget;
    QStackedWidget *stackedWidget;
    QModelIndex currentArtistIndex;
    QSet<QString> favoriteArtists;
    QSet<QString> favoriteAlbums;
    AddRowDialog *addRowDialog;

    QString encodeAlbumName(QString albumName);
    QString decodeAlbumName(QString encodedAlbumName);
    QString encodeArtistName(QString artistName);
    QString decodeArtistName(QString encodedArtistName);
    bool isAlbumByArtist(const QString &album, const QString &artist);

    QString monthText(int month);

    AboutWindow *aboutWindow;

};



#endif // MAINWINDOW_H
