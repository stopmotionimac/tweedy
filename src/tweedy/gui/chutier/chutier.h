#ifndef CHUTIER_H
#define CHUTIER_H

#include <QtGui/QWidget>
#include <QtGui/QListWidget>
#include <QtGui/QListWidgetItem>

namespace Ui {
    class Chutier;
}

class Chutier : public QWidget
{
    Q_OBJECT

public:
    explicit Chutier(QWidget *parent = 0);
    ~Chutier();

public Q_SLOTS:
    void on_photo_selected(QListWidgetItem * item);

private:
    Ui::Chutier *ui;
    QListWidget * listWidget;
    QListWidget * listImport;
};

#endif // CHUTIER_H
