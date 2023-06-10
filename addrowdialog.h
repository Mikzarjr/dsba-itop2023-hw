#ifndef ADDROWDIALOG_H
#define ADDROWDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>

class AddRowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRowDialog(QWidget *parent = nullptr);

    QString getArtistName() const;
    QString getAlbumName() const;
    QDate getDate() const;
    QString getFormat() const;
    QString getLabel() const;
    QString getGenre() const;
    QString getMetacriticCriticScore() const;
    QString getMetacriticReviews() const;
    QString getMetacriticUserScore() const;
    QString getMetacriticUserReviews() const;
    QString getAotyCriticScore() const;
    QString getAotyCriticReviews() const;
    QString getAotyUserScore() const;
    QString getAotyUserReviews() const;

private:
    QLineEdit *artistNameLineEdit;
    QLineEdit *albumNameLineEdit;
    QDateEdit *dateEdit;
    QComboBox *formatComboBox;
    QLineEdit *labelLineEdit;
    QLineEdit *genreLineEdit;
    QLineEdit *metacriticCriticScoreLineEdit;
    QLineEdit *metacriticReviewsLineEdit;
    QLineEdit *metacriticUserScoreLineEdit;
    QLineEdit *metacriticUserReviewsLineEdit;
    QLineEdit *aotyCriticScoreLineEdit;
    QLineEdit *aotyCriticReviewsLineEdit;
    QLineEdit *aotyUserScoreLineEdit;
    QLineEdit *aotyUserReviewsLineEdit;
};

#endif // ADDROWDIALOG_H
