#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H

#include "../utils/MusicClass.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QLabel>

class SearchPage : public QWidget {
    Q_OBJECT
public:
    explicit SearchPage(const QString& key, QWidget *parent = nullptr);
private:
    QVBoxLayout* mainLayout;
    QVBoxLayout* resultLayout;
    QLabel* filterText;
    QLabel* empty;
    QPushButton* musics;
    QPushButton* authors;
    int currentPage;

    void musicsClicked();
    void authorsClicked();

    std::vector<std::shared_ptr<AuthorObject>> foundAuthors;
    std::vector<std::shared_ptr<MusicObject>> foundMusics;
};

#endif // SEARCHPAGE_H
