#ifndef COVERFUNKS_H
#define COVERFUNKS_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QBoxLayout>

QHBoxLayout* coverWithHLayout(QWidget* widget);
QHBoxLayout* coverWithoutStretchHLayout(QWidget* widget);
QVBoxLayout* coverWithVLayout(QWidget* widget);
QVBoxLayout* coverWithoutStretchVLayout(QWidget* widget);
QWidget* coverLayoutWithWidget(QBoxLayout* layout);

#endif // COVERFUNKS_H
