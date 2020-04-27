#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "backend.h"

#include <QMainWindow>
#include <QPainter>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <bits/stdc++.h>
#include <QGraphicsTextItem>
#include <QString>
#include <QColor>

using namespace std;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);

public:
    explicit MainWindow(QWidget *parent = 0);

    void out_avltree(node_avl * v, int64_t y_need, int64_t x_prev, int64_t y_prev, int64_t need_left);
    void out_rbtree(Node * v, int64_t y_need, int64_t x_prev, int64_t y_prev, int64_t need_left);
    void out_splay(splay * v, int64_t y_need, int64_t x_prev, int64_t y_prev, int64_t need_left);

    QGraphicsScene *scene_avl;
    QGraphicsScene *scene_rb;
    QGraphicsScene *scene_splay; // TODO

    ~MainWindow();

private slots:
    void on_button_insert_avl_clicked();
    void on_button_delete_avl_clicked();

    void on_button_insert_rb_clicked();
    void on_button_delete_rb_clicked();

    void on_button_insert_splay_clicked();
    void on_button_delete_splay_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
