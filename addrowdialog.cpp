#include "addrowdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

AddRowDialog::AddRowDialog(QWidget *parent) : QDialog(parent)
{
    artistNameLineEdit = new QLineEdit(this);
    albumNameLineEdit = new QLineEdit(this);
    dateEdit = new QDateEdit(this);
    formatComboBox = new QComboBox(this);
    labelLineEdit = new QLineEdit(this);
    genreLineEdit = new QLineEdit(this);
    metacriticCriticScoreLineEdit = new QLineEdit(this);
    metacriticReviewsLineEdit = new QLineEdit(this);
    metacriticUserScoreLineEdit = new QLineEdit(this);
    metacriticUserReviewsLineEdit = new QLineEdit(this);
    aotyCriticScoreLineEdit = new QLineEdit(this);
    aotyCriticReviewsLineEdit = new QLineEdit(this);
    aotyUserScoreLineEdit = new QLineEdit(this);
    aotyUserReviewsLineEdit = new QLineEdit(this);

    QLabel *artistNameLabel = new QLabel("Artist Name:", this);
    QLabel *albumNameLabel = new QLabel("Album Name:", this);
    QLabel *dateLabel = new QLabel("Date:", this);
    QLabel *formatLabel = new QLabel("Format:", this);
    QLabel *labelLabel = new QLabel("Label:", this);
    QLabel *genreLabel = new QLabel("Genre:", this);
    QLabel *metacriticCriticScoreLabel = new QLabel("Metacritic Critic Score:", this);
    QLabel *metacriticReviewsLabel = new QLabel("Metacritic Reviews:", this);
    QLabel *metacriticUserScoreLabel = new QLabel("Metacritic User Score:", this);
    QLabel *metacriticUserReviewsLabel = new QLabel("Metacritic User Reviews:", this);
    QLabel *aotyCriticScoreLabel = new QLabel("AOTY Critic Score:", this);
    QLabel *aotyCriticReviewsLabel = new QLabel("AOTY Critic Reviews:", this);
    QLabel *aotyUserScoreLabel = new QLabel("AOTY User Score:", this);
    QLabel *aotyUserReviewsLabel = new QLabel("AOTY User Reviews:", this);

    QPushButton *okButton = new QPushButton("OK", this);
    QPushButton *cancelButton = new QPushButton("Cancel", this);

    formatComboBox->addItem("LP");
    formatComboBox->addItem("CD");

    connect(okButton, &QPushButton::clicked, this, &AddRowDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &AddRowDialog::reject);

    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *artistLayout = new QHBoxLayout;
    QHBoxLayout *albumLayout = new QHBoxLayout;
    QHBoxLayout *dateLayout = new QHBoxLayout;
    QHBoxLayout *formatLayout = new QHBoxLayout;
    QHBoxLayout *labelLayout = new QHBoxLayout;
    QHBoxLayout *genreLayout = new QHBoxLayout;
    QHBoxLayout *metacriticCriticScoreLayout = new QHBoxLayout;
    QHBoxLayout *metacriticReviewsLayout = new QHBoxLayout;
    QHBoxLayout *metacriticUserScoreLayout = new QHBoxLayout;
    QHBoxLayout *metacriticUserReviewsLayout = new QHBoxLayout;
    QHBoxLayout *aotyCriticScoreLayout = new QHBoxLayout;
    QHBoxLayout *aotyCriticReviewsLayout = new QHBoxLayout;
    QHBoxLayout *aotyUserScoreLayout = new QHBoxLayout;
    QHBoxLayout *aotyUserReviewsLayout = new QHBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    artistLayout->addWidget(artistNameLabel);
    artistLayout->addWidget(artistNameLineEdit);

    albumLayout->addWidget(albumNameLabel);
    albumLayout->addWidget(albumNameLineEdit);

    dateLayout->addWidget(dateLabel);
    dateLayout->addWidget(dateEdit);

    formatLayout->addWidget(formatLabel);
    formatLayout->addWidget(formatComboBox);

    labelLayout->addWidget(labelLabel);
    labelLayout->addWidget(labelLineEdit);

    genreLayout->addWidget(genreLabel);
    genreLayout->addWidget(genreLineEdit);

    metacriticCriticScoreLayout->addWidget(metacriticCriticScoreLabel);
    metacriticCriticScoreLayout->addWidget(metacriticCriticScoreLineEdit);

    metacriticReviewsLayout->addWidget(metacriticReviewsLabel);
    metacriticReviewsLayout->addWidget(metacriticReviewsLineEdit);

    metacriticUserScoreLayout->addWidget(metacriticUserScoreLabel);
    metacriticUserScoreLayout->addWidget(metacriticUserScoreLineEdit);

    metacriticUserReviewsLayout->addWidget(metacriticUserReviewsLabel);
    metacriticUserReviewsLayout->addWidget(metacriticUserReviewsLineEdit);

    aotyCriticScoreLayout->addWidget(aotyCriticScoreLabel);
    aotyCriticScoreLayout->addWidget(aotyCriticScoreLineEdit);

    aotyCriticReviewsLayout->addWidget(aotyCriticReviewsLabel);
    aotyCriticReviewsLayout->addWidget(aotyCriticReviewsLineEdit);

    aotyUserScoreLayout->addWidget(aotyUserScoreLabel);
    aotyUserScoreLayout->addWidget(aotyUserScoreLineEdit);

    aotyUserReviewsLayout->addWidget(aotyUserReviewsLabel);
    aotyUserReviewsLayout->addWidget(aotyUserReviewsLineEdit);

    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    layout->addLayout(artistLayout);
    layout->addLayout(albumLayout);
    layout->addLayout(dateLayout);
    layout->addLayout(formatLayout);
    layout->addLayout(labelLayout);
    layout->addLayout(genreLayout);
    layout->addLayout(metacriticCriticScoreLayout);
    layout->addLayout(metacriticReviewsLayout);
    layout->addLayout(metacriticUserScoreLayout);
    layout->addLayout(metacriticUserReviewsLayout);
    layout->addLayout(aotyCriticScoreLayout);
    layout->addLayout(aotyCriticReviewsLayout);
    layout->addLayout(aotyUserScoreLayout);
    layout->addLayout(aotyUserReviewsLayout);
    layout->addLayout(buttonLayout);

    setLayout(layout);
}

QString AddRowDialog::getArtistName() const
{
    return artistNameLineEdit->text();
}

QString AddRowDialog::getAlbumName() const
{
    return albumNameLineEdit->text();
}

QDate AddRowDialog::getDate() const
{
    return dateEdit->date();
}

QString AddRowDialog::getFormat() const
{
    return formatComboBox->currentText();
}

QString AddRowDialog::getLabel() const
{
    return labelLineEdit->text();
}

QString AddRowDialog::getGenre() const
{
    return genreLineEdit->text();
}

QString AddRowDialog::getMetacriticCriticScore() const
{
    return metacriticCriticScoreLineEdit->text();
}

QString AddRowDialog::getMetacriticReviews() const
{
    return metacriticReviewsLineEdit->text();
}

QString AddRowDialog::getMetacriticUserScore() const
{
    return metacriticUserScoreLineEdit->text();
}

QString AddRowDialog::getMetacriticUserReviews() const
{
    return metacriticUserReviewsLineEdit->text();
}

QString AddRowDialog::getAotyCriticScore() const
{
    return aotyCriticScoreLineEdit->text();
}

QString AddRowDialog::getAotyCriticReviews() const
{
    return aotyCriticReviewsLineEdit->text();
}

QString AddRowDialog::getAotyUserScore() const
{
    return aotyUserScoreLineEdit->text();
}

QString AddRowDialog::getAotyUserReviews() const
{
    return aotyUserReviewsLineEdit->text();
}
