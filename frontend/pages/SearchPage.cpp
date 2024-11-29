#include "../headers/components/AuthorCard.h"
#include "../headers/components/MusicCard.h"
#include "../headers/pages/SearchPage.h"
#include "../headers/utils/HttpClient.h"
#include "../headers/utils/EnvFile.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

SearchPage::SearchPage(const QString& key, QWidget *parent) : QWidget(parent) {
    filterText = new QLabel("Показать результаты: ");
    filterText->setStyleSheet("height: 20px; background: #121212; padding: 0px; margin: 0px 0px 0px 7px; color: #EDEDED;");

    empty = new QLabel("Пусто...");
    empty->setStyleSheet("font-size: 30px; background: #121212; padding: 0px; margin: 0px 0px 0px 7px; color: #EDEDED;");

    musics = new QPushButton("Только треки");
    musics->setStyleSheet("QPushButton { width: 200px; height: 20px; background: #121212; padding: 0px; margin: 0px; color: #EDEDED; }"
        "QPushButton:hover { text-decoration: underline; }");
    musics->connect(musics, &QPushButton::clicked, this, SearchPage::musicsClicked);

    authors = new QPushButton("Только исполнители");
    authors->setStyleSheet("QPushButton { width: 200px; height: 20px; background: #121212; padding: 0px; margin: 0px; color: #EDEDED; }"
        "QPushButton:hover { text-decoration: underline; }");
    authors->connect(authors, &QPushButton::clicked, this, SearchPage::authorsClicked);

    QHBoxLayout* topTextLayout = new QHBoxLayout();
    topTextLayout->addWidget(filterText);
    topTextLayout->addWidget(musics);
    topTextLayout->addWidget(authors);
    topTextLayout->setAlignment(Qt::AlignLeft);


    resultLayout = new QVBoxLayout();
    mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addLayout(topTextLayout);
    mainLayout->addLayout(resultLayout);

    qDebug() << Env::get("SERVER_DOMEN", ":/.env") + "/music/find?key=" + key;
    HttpClient::sendGetRequest(Env::get("SERVER_DOMEN", ":/.env") + "/music/find?key=" + key, [this](HttpClient::Response* response){
        if (response->statusCode < 400) {
            QJsonArray musicsArray = response->bodyJsonObj.value("musics").toArray();
            QJsonArray authorsArray = response->bodyJsonObj.value("authors").toArray();

            for(int i = 0; i < musicsArray.size(); i++) {
                this->foundMusics.push_back(std::make_shared<MusicObject>(musicsArray[i].toObject()));
            }

            for(int i = 0; i < authorsArray.size(); i++) {
                this->foundAuthors.push_back(std::make_shared<AuthorObject>(authorsArray[i].toObject()));
            }

            if(musicsArray.size() != 0) {
                currentPage = 1;

                for(int i = 0; i < this->foundMusics.size(); i++) {
                    this->resultLayout->addWidget(new MusicCard(this->foundMusics[i]));
                }
            } else if(authorsArray.size() != 0) {
                currentPage = 2;

                for(int i = 0; i < this->foundAuthors.size(); i++) {
                    this->resultLayout->addWidget(new AuthorCard(this->foundAuthors[i]));
                }
            } else {
                this->resultLayout->addWidget(this->empty);
            }

        }
    });


}

void SearchPage::musicsClicked() {
    this->currentPage = 1;

    QLayoutItem *item;
    while ((item = this->resultLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    if(this->foundMusics.size() == 0) {
        this->resultLayout->addWidget(this->empty);
        return;
    }

    for(int i = 0; i < this->foundMusics.size(); i++) {
        this->resultLayout->addWidget(new MusicCard(this->foundMusics[i]));
    }
}

void SearchPage::authorsClicked() {
    this->currentPage = 2;

    QLayoutItem *item;
    while ((item = this->resultLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    if(this->foundAuthors.size() == 0) {
        this->resultLayout->addWidget(this->empty);
        return;
    }

    for(int i = 0; i < this->foundAuthors.size(); i++) {
        this->resultLayout->addWidget(new AuthorCard(this->foundAuthors[i]));
    }
}
