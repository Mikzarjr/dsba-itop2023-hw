#include "aboutwindow.h"
#include "mainwindow.h"
#include "csvmodel.h"
#include <QHeaderView>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QApplication>
#include <QScreen>
#include <QPushButton>
#include <QMessageBox>
#include <QStackedWidget>
#include <QDate>
#include <QSet>
#include <QMessageBox>
#include <QModelIndexList>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), addRowDialog(nullptr)
{
    csvModel = new CsvModel(this);
    csvModel->loadCsv("/Users/mikzar/Desktop/BigHW/album_ratings.csv");

    tableView = new QTableView(this);
    tableView->setSortingEnabled(true);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->hide();

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(csvModel);
    tableView->setModel(proxyModel);

    tableView->hideColumn(2); // month
    tableView->hideColumn(3); // day
    tableView->hideColumn(4); // year
    tableView->hideColumn(5); // format
    tableView->hideColumn(8); // Metacritic Critic Score
    tableView->hideColumn(9); // Metacritic Reviews
    tableView->hideColumn(10); // Metacritic User Score
    tableView->hideColumn(11); // Metacritic User Reviews
    tableView->hideColumn(12); // AOTY Critic Score
    tableView->hideColumn(13); // AOTY Critic Reviews
    tableView->hideColumn(14); // AOTY User Score
    tableView->hideColumn(15); // AOTY User Reviews


    searchBar = new QLineEdit(this);

    categoryBox = new QComboBox(this);
    QList<int> sortableColumns = {0, 1, 6, 7};
    for (int i = 0; i < csvModel->columnCount(); ++i) {
        if (sortableColumns.contains(i)) {
            categoryBox->addItem(csvModel->headerData(i, Qt::Horizontal).toString(), i);
        }
    }


    int size = 200;
    searchBar->setFixedSize(size, searchBar->height());
    categoryBox->setFixedSize(size + 5, categoryBox->height());
    aboutWindow = new AboutWindow(this);

    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *topLayout = new QHBoxLayout;
    QHBoxLayout *bottomLayout = new QHBoxLayout;

    QPushButton *resetButton = new QPushButton("Reset", this);
    resetButton->setFixedSize(200, 30);

    QPushButton *aboutButton = new QPushButton("About", this);
    aboutButton->setFixedSize(200, 30);

    QPushButton *addRowButton = new QPushButton("Add Row", this);

    QPushButton *favoritesButton = new QPushButton("Favorites", this);
    favoritesButton->setFixedSize(size, categoryBox->height());

    QPushButton *deleteRowButton = new QPushButton("Delete Row", this);
    deleteRowButton->setFixedSize(200, 30);


    topLayout->addWidget(aboutButton, 0, Qt::AlignLeft);
    bottomLayout->addWidget(resetButton, 0, Qt::AlignLeft);

    bottomLayout->addWidget(favoritesButton, 0, Qt::AlignCenter);
    topLayout->addWidget(deleteRowButton, 0, Qt::AlignCenter);

    topLayout->addWidget(categoryBox, 0,  Qt::AlignRight);
    bottomLayout->addWidget(searchBar, 0, Qt::AlignRight);

    layout->addLayout(topLayout);
    layout->addLayout(bottomLayout);
    layout->addWidget(tableView);
    layout->addWidget(addRowButton);

    QWidget *mainWidget = new QWidget(this);
    mainWidget->setLayout(layout);

    artistInfoWidget = new QWidget(this);
    QVBoxLayout *artistLayout = new QVBoxLayout;
    artistInfoLabel = new QLabel(this);
    backButton = new QPushButton("Back", this);
    connect(backButton, &QPushButton::clicked, [=](){ stackedWidget->setCurrentIndex(0); });
    artistLayout->addWidget(artistInfoLabel);
    artistLayout->addWidget(backButton);
    artistInfoWidget->setLayout(artistLayout);
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(mainWidget);
    stackedWidget->addWidget(artistInfoWidget);
    setCentralWidget(stackedWidget);

    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    resize(screenGeometry.width() / 1.5, screenGeometry.height() / 1.5);


    connect(resetButton, &QPushButton::clicked, this, &MainWindow::resetTable);
    connect(searchBar, &QLineEdit::textChanged, this, &MainWindow::filterTable);
    connect(tableView, &QTableView::doubleClicked, this, &MainWindow::showArtistInfo);
    connect(artistInfoLabel, &QLabel::linkActivated, this, &MainWindow::toggleFavorite);
    connect(favoritesButton, &QPushButton::clicked, this, &MainWindow::showFavorites);
    connect(tableView, &QTableView::clicked, this, &MainWindow::albumClicked);
    connect(addRowButton, &QPushButton::clicked, this, &MainWindow::openAddRowDialog);
    connect(aboutButton, &QPushButton::clicked, this, [=]() {
        aboutWindow->exec();
    });
    connect(deleteRowButton, &QPushButton::clicked, this, &MainWindow::deleteRow);

}

void MainWindow::deleteRow()
{
    QModelIndexList selectedIndexes = tableView->selectionModel()->selectedIndexes();

    if (!selectedIndexes.isEmpty()) {
        QModelIndex sourceIndex = proxyModel->mapToSource(selectedIndexes.first());
        int row = sourceIndex.row();
        QString albumName = csvModel->index(row, 1).data().toString();

        QMessageBox::StandardButton confirmation = QMessageBox::question(this, "Delete Row", "Are you sure you want to delete the album \"" + albumName + "\"?", QMessageBox::Yes | QMessageBox::No);
        if (confirmation == QMessageBox::Yes) {
            csvModel->removeRow(row);
            csvModel->saveCsv("/Users/mikzar/Desktop/BigHW/album_ratings.csv");
        }
    }
}




void MainWindow::openAddRowDialog()
{
    if (!addRowDialog)
    {
        addRowDialog = new AddRowDialog(this);
    }

    if (addRowDialog->exec() == QDialog::Accepted)
    {

        QString artistName = addRowDialog->getArtistName();
        QString albumName = addRowDialog->getAlbumName();
        QDate date = addRowDialog->getDate();
        QString format = addRowDialog->getFormat();
        QString label = addRowDialog->getLabel();
        QString genre = addRowDialog->getGenre();
        QString metacriticCriticScore = addRowDialog->getMetacriticCriticScore();
        QString metacriticReviews = addRowDialog->getMetacriticReviews();
        QString metacriticUserScore = addRowDialog->getMetacriticUserScore();
        QString metacriticUserReviews = addRowDialog->getMetacriticUserReviews();
        QString aotyCriticScore = addRowDialog->getAotyCriticScore();
        QString aotyCriticReviews = addRowDialog->getAotyCriticReviews();
        QString aotyUserScore = addRowDialog->getAotyUserScore();
        QString aotyUserReviews = addRowDialog->getAotyUserReviews();


        csvModel->addRow(QStringList() << artistName << albumName << monthText(date.month()) << QString::number(date.day())
                                       << QString::number(date.year()) << format << label << genre << metacriticCriticScore
                                       << metacriticReviews << metacriticUserScore << metacriticUserReviews << aotyCriticScore
                                       << aotyCriticReviews << aotyUserScore << aotyUserReviews);

        csvModel->saveCsv("/Users/mikzar/Desktop/BigHW/album_ratings.csv");

        tableView->scrollToTop();
    }
}

QString MainWindow::monthText(int month)
{
    static const QStringList monthNames = {"January", "February", "March", "April",
                                           "May", "June", "July", "August",
                                           "September", "October", "November", "December"};

    if (month >= 1 && month <= 12)
        return monthNames.at(month - 1);

    return "";
}

void MainWindow::showArtistInfo(const QModelIndex &index)
{
    currentArtistIndex = index;

    if (index.column() == 0) {
        QString artistName = index.data().toString();
        QString encodedArtistName = encodeArtistName(artistName);

        QMultiMap<int, QString> albumsByRating;
        QMultiMap<int, QString> albumsByDate;

        for (int i = 0; i < csvModel->rowCount(); ++i) {
            if (csvModel->index(i, 0).data().toString() == artistName) {
                int rating = csvModel->index(i, 8).data().toInt(); // rating
                int year = csvModel->index(i, 4).data().toInt(); // year
                int month = csvModel->index(i, 2).data().toInt(); // month
                int day = csvModel->index(i, 3).data().toInt(); // day
                QDate date(year, month, day);
                QString album = csvModel->index(i, 1).data().toString();
                albumsByRating.insert(rating, album);
                albumsByDate.insert(date.toJulianDay(), album);
            }
        }

        QStringList sortedAlbumsByRating;
        QMultiMap<int, QString>::const_iterator i = albumsByRating.constEnd();
        while (i != albumsByRating.constBegin()) {
            --i;
            sortedAlbumsByRating.append(i.value());
        }

        QStringList sortedAlbumsByDate;
        QMultiMap<int, QString>::const_iterator j = albumsByDate.constEnd();
        while (j != albumsByDate.constBegin()) {
            --j;
            sortedAlbumsByDate.append(j.value());
        }

        QString heart = favoriteArtists.contains(artistName) ? "❤️" : "♡";
                            QString artistLine = "<a href='artist:" + encodedArtistName + "'>" + heart + "</a> " + artistName;

        QStringList albumLines;
        for (const QString &album : sortedAlbumsByDate) {
            heart = favoriteAlbums.contains(album) ? "❤️" : "♡";
                        albumLines.append("<a href='album:" + album + "'>" + heart + "</a> " + album);
        }

        artistInfoLabel->setText("<div style='text-align: center; font-size:26px; font-weight:bold; color:#FFFFFF;'>"
                                 + artistLine +
                                 "</div>"
                                 "<div style='display: grid; grid-template-columns: 1fr 1fr;'>"
                                 "<div style='text-align: left; font-size:20px; color:#FFFFFF;'>"
                                 "<br><br>Top Album by Rating:<br>" + sortedAlbumsByRating.first() +
                                 "<br><br>Latest Album:<br>" + sortedAlbumsByDate.first() +
                                 "</div>"
                                 "<div style='text-align: left; font-size:20px; color:#FFFFFF;'>"
                                 "<br><br><br>All Albums:<br><br>" + albumLines.join("<br>") +
                                 "</div>"
                                 "</div>");

        stackedWidget->setCurrentIndex(1);
    }
}

void MainWindow::showAlbumInfo(const QString &albumName)
{
    QWidget *albumWidget = new QWidget(this);
    QVBoxLayout *albumLayout = new QVBoxLayout;
    QHBoxLayout *topLayout = new QHBoxLayout;

    QPushButton *backButton = new QPushButton("Back", this);
    connect(backButton, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(0); });

    topLayout->addWidget(backButton, 0, Qt::AlignRight);
    albumLayout->addLayout(topLayout);

    QString heart = favoriteAlbums.contains(albumName) ? "❤️" : "♡";
                        QLabel *albumTitleLabel = new QLabel(this);
    albumTitleLabel->setText("<div style='text-align: center; font-size:26px; font-weight:bold; color:#FFFFFF;'>"
                             "<a href='album:" + encodeAlbumName(albumName) + "'>" + heart + "</a> " + albumName +
                             "</div>");


    albumTitleLabel->setOpenExternalLinks(false);
    connect(albumTitleLabel, &QLabel::linkActivated, this, &MainWindow::toggleFavorite);
    albumLayout->addWidget(albumTitleLabel, 0, Qt::AlignTop);

    for (int i = 0; i < csvModel->rowCount(); ++i) {
        if (csvModel->index(i, 1).data().toString() == albumName) {
                        int year = csvModel->index(i, 4).data().toInt(); // year
                        QString month = csvModel->index(i, 2).data().toString(); // month
                        int day = csvModel->index(i, 3).data().toInt(); // day

                        QString dateString = month + ' ' + QString::number(day).rightJustified(2, '0') + '.' + QString::number(year);

                        int rating = csvModel->index(i, 8).data().toInt(); // rating
                        QString format = csvModel->index(i, 5).data().toString(); // format
                        QString genre = csvModel->index(i, 7).data().toString(); // genre
                        QString artist = csvModel->index(i, 0).data().toString(); // artist


                        QLabel *albumInfoLabel = new QLabel(this);
                        albumInfoLabel->setText("<div style='text-align: left; font-size:20px; color:#FFFFFF;'>"
                                                "<br><br>Artist:<br>" + artist +
                                                "<br><br>Date:<br>" + dateString +
                                                "<br><br>Rating:<br>" + QString::number(rating) +
                                                "<br><br>Format:<br>" + format +
                                                "<br><br>Genre:<br>" + genre +
                                                "</div>");

                        albumLayout->addWidget(albumInfoLabel, 0, Qt::AlignTop);
                        break;
        }
    }

    albumWidget->setLayout(albumLayout);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(albumWidget);
    scrollArea->setWidgetResizable(true);

    stackedWidget->addWidget(scrollArea);
    stackedWidget->setCurrentIndex(stackedWidget->count() - 1);
}

QString MainWindow::encodeAlbumName(QString albumName) {
    albumName.replace("'", "&apos;");
    albumName.replace(":", "&colon;");
    return albumName;
}

QString MainWindow::decodeAlbumName(QString encodedAlbumName) {
    encodedAlbumName.replace("&apos;", "'");
    encodedAlbumName.replace("&colon;", ":");
    return encodedAlbumName;
}

QString MainWindow::encodeArtistName(QString artistName) {
    artistName.replace("'", "&apos;");
    artistName.replace(":", "&colon;");
    return artistName;
}

QString MainWindow::decodeArtistName(QString encodedArtistName) {
    encodedArtistName.replace("&apos;", "'");
    encodedArtistName.replace("&colon;", ":");
    return encodedArtistName;
}

void MainWindow::toggleFavorite(const QString &link)
{
    int colonIndex = link.indexOf(':');
    if (colonIndex == -1) return;

    QString type = link.left(colonIndex);
    QString name = decodeAlbumName(link.mid(colonIndex + 1));

    if (type == "artist") {
        if (favoriteArtists.contains(name)) {
                        favoriteArtists.remove(name);
        } else {
                        favoriteArtists.insert(name);
        }
        showArtistInfo(currentArtistIndex);
    } else if (type == "album") {
        if (favoriteAlbums.contains(name)) {
                        favoriteAlbums.remove(name);
        } else {
                        favoriteAlbums.insert(name);
        }
        if (stackedWidget->currentWidget() == artistInfoWidget) {
                        showArtistInfo(currentArtistIndex);
        } else {
                        showAlbumInfo(name);
        }
    }
}

void MainWindow::albumClicked(const QModelIndex &index)
{
    if (index.column() == 1) {
        QString albumName = index.data().toString();
        showAlbumInfo(albumName);
    }
}

void MainWindow::filterTable(const QString &text)
{
    int column = categoryBox->currentData().toInt();
    proxyModel->setFilterKeyColumn(column);
    proxyModel->setFilterFixedString(text);
}

void MainWindow::resetTable()
{
    delete csvModel;

    csvModel = new CsvModel(this);
    csvModel->loadCsv("/Users/mikzar/Desktop/BigHW/album_ratings.csv");

    proxyModel->setSourceModel(csvModel);
    tableView->setModel(proxyModel);

    proxyModel->setFilterKeyColumn(0);
    proxyModel->setFilterFixedString("");
    searchBar->clear();
    categoryBox->setCurrentIndex(0);
    tableView->sortByColumn(-1, Qt::AscendingOrder);
}

void MainWindow::showFavorites()
{
    QWidget *favoritesWidget = new QWidget(this);
    QVBoxLayout *favoritesLayout = new QVBoxLayout;
    QHBoxLayout *topLayout = new QHBoxLayout;

    QPushButton *backButton = new QPushButton("Back", this);
    connect(backButton, &QPushButton::clicked, [=](){ stackedWidget->setCurrentIndex(0); });

    topLayout->addWidget(backButton, 0, Qt::AlignRight);
    favoritesLayout->addLayout(topLayout);

    for (const QString &artist : favoriteArtists) {
        QLabel *artistLabel = new QLabel(this);
        artistLabel->setText("<br><div style='text-align: left; font-size:22px; font-weight:bold; color:#FFFFFF;'>"
                                 + artist + "<br>" +
                             "</div>");
        favoritesLayout->addWidget(artistLabel, 0, Qt::AlignTop);

        for (const QString &album : favoriteAlbums) {
                        if (isAlbumByArtist(album, artist)) {
                QLabel *albumLabel = new QLabel(this);
                albumLabel->setText("<div style='text-align: left; font-size:20px; color:#FFFFFF;'>"
                                    + album +
                                    "</div>");
                favoritesLayout->addWidget(albumLabel, 0, Qt::AlignTop);
                        }
        }
    }

    bool hasAlbumsWithoutFavoritedArtist = false;
    for (const QString &album : favoriteAlbums) {
        bool isArtistFavorited = false;
        for (const QString &artist : favoriteArtists) {
                        if (isAlbumByArtist(album, artist)) {
                isArtistFavorited = true;
                break;
                        }
        }

        if (!isArtistFavorited) {
                        hasAlbumsWithoutFavoritedArtist = true;
                        break;
        }
    }

    if (hasAlbumsWithoutFavoritedArtist) {
        QLabel *otherAlbumsLabel = new QLabel(this);
        otherAlbumsLabel->setText("<div style='text-align: left; font-size:24px; font-weight:bold; color:#FFFFFF;'>"
                                  "<br><br>Other albums: "
                                  "</div>");
        favoritesLayout->addWidget(otherAlbumsLabel, 0, Qt::AlignTop);

        for (const QString &album : favoriteAlbums) {
                        bool isArtistFavorited = false;
                        for (const QString &artist : favoriteArtists) {
                if (isAlbumByArtist(album, artist)) {
                    isArtistFavorited = true;
                    break;
                }
                        }

                        if (!isArtistFavorited) {
                QLabel *albumLabel = new QLabel(this);
                albumLabel->setText("<div style='text-align: left; font-size:20px; color:#FFFFFF;'>"
                                    + album +
                                    "</div>");
                favoritesLayout->addWidget(albumLabel, 0, Qt::AlignTop);
                        }
        }
    }

    favoritesWidget->setLayout(favoritesLayout);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(favoritesWidget);
    scrollArea->setWidgetResizable(true);

    stackedWidget->addWidget(scrollArea);
    stackedWidget->setCurrentIndex(stackedWidget->count() - 1);
}

bool MainWindow::isAlbumByArtist(const QString &album, const QString &artist)
{
    for (int i = 0; i < csvModel->rowCount(); ++i) {
        if (csvModel->index(i, 0).data().toString() == artist &&
            csvModel->index(i, 1).data().toString() == album) {
                        return true;
        }
    }
    return false;
}
