#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

QHBoxLayout* coverWithHLayout(QWidget* widget) {
    QHBoxLayout *coverringLayout = new QHBoxLayout();

    coverringLayout->addStretch();
    coverringLayout->addWidget(widget);
    coverringLayout->addStretch();

    return coverringLayout;
}

QHBoxLayout* coverWithoutStretchHLayout(QWidget* widget) {
    QHBoxLayout *coverringLayout = new QHBoxLayout();

    coverringLayout->addWidget(widget);

    return coverringLayout;
}

QVBoxLayout* coverWithVLayout(QWidget* widget) {
    QVBoxLayout *coverringLayout = new QVBoxLayout();

    coverringLayout->addStretch();
    coverringLayout->addWidget(widget);
    coverringLayout->addStretch();

    return coverringLayout;
}

QVBoxLayout* coverWithoutStretchVLayout(QWidget* widget) {
    QVBoxLayout *coverringLayout = new QVBoxLayout();

    coverringLayout->addWidget(widget);

    return coverringLayout;
}

QWidget* coverLayoutWithWidget(QBoxLayout* layout) {
    QWidget* coverringWidget = new QWidget();

    coverringWidget->setLayout(layout);

    return coverringWidget;
}
