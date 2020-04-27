#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "backend.h"
using namespace std;

node_avl *T;
static Node *root;
static splay *S;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // AVL Tree

    scene_avl = new QGraphicsScene;

    ui->graphicsView->setScene(scene_avl);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //scene_avl->setSceneRect(0, 0, 800, 600);

    T = nullptr;
    T = insert_avl(T, 10);
    T = insert_avl(T, 20);
    T = insert_avl(T, 30);
    T = insert_avl(T, 40);
    T = insert_avl(T, 50);

    // RB Tree

    scene_rb = new QGraphicsScene;

    ui->graphicsView_2->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->graphicsView_2->setScene(scene_rb);

    //scene_rb->setSceneRect(0, 0, 800, 600);

    root = nullptr;

    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);
    root = insertNode(root, 50);

    // Splay Tree

    scene_splay = new QGraphicsScene;

    ui->graphicsView_3->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_3->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->graphicsView_3->setScene(scene_splay);

   // scene_splay->setSceneRect(0, 0, 800, 600);

    S = nullptr;

    S = Insert(10, S);
    S = Insert(20, S);
    S = Insert(30, S);
    S = Insert(40, S);
    S = Insert(50, S);

    repaint();
}

int64_t x_need_avl, x_plus_avl, y_plus_avl;

void MainWindow::out_avltree(node_avl *v, int64_t y_need, int64_t x_prev, int64_t y_prev, int64_t need_left) {
    if (v == nullptr) {
        return;
    }

    out_avltree(v->left, y_need + y_plus_avl, x_plus_avl * (get_size_avl(v->left) + 1 + need_left), y_need, need_left);
    int64_t x_this = x_need_avl;
    if (x_prev != -1) {
        scene_avl->addLine(x_need_avl, y_need, x_prev, y_prev, QPen(QColor(49, 10, 10, 250)));
    }

    x_need_avl += x_plus_avl;

    out_avltree(v->right, y_need + y_plus_avl, x_plus_avl * (get_size_avl(v->left) + 1 + need_left), y_need, need_left + 1 + get_size_avl(v->left));

    int len_num = QString::number(v->val).size();
    int len_ell = len_num * 15 < 30 ? 30 : len_num * 15;
    len_ell = len_ell > 7 * 15 ? 7 * 15 : len_ell;

    int delta = len_num / 2 * 15 < 15 ? 15 : len_num / 2 * 15;
    delta = len_num / 2 * 15 > 15 * 3 ? 15 * 3 : len_num / 2 * 15;

    int x_delta = len_num * 5 < 6 ? 6 : len_num * 4;
    x_delta = len_num * 4 > 50 ? 50 : len_num * 4;

    scene_avl->addEllipse(x_this, y_need - 15, len_ell, 30, QPen(QColor(250, 0, 0, 250)),QBrush(QColor(250, 0, 0, 250)));
    QGraphicsTextItem *text = scene_avl->addText(QString::number(v->val), QFont("Ubuntu"));
    text->setHtml("<center><p style=\"color:white;\">" + QString::number(v->val) + "</p></center>");
    text->setTextWidth(len_ell);
    text->setPos(x_this, y_need - 10);
}

int64_t x_need_rb, x_plus_rb, y_plus_rb;

void MainWindow::out_rbtree(Node * v, int64_t y_need, int64_t x_prev, int64_t y_prev, int64_t need_left) {
    if (v == nullptr) {
        return;
    }

    out_rbtree(v->left, y_need + y_plus_rb, x_plus_rb * (size_rb(v->left) + 1 + need_left), y_need, need_left);
    int64_t x_this = x_need_rb;
    if (x_prev != -1) {
        scene_rb->addLine(x_need_rb, y_need, x_prev, y_prev, QPen(QColor(49, 10, 10, 250)));
    }

    x_need_rb += x_plus_rb;

    out_rbtree(v->right, y_need + y_plus_rb, x_plus_rb * (size_rb(v->left) + 1 + need_left), y_need, need_left + 1 + size_rb(v->left));

    int len_num = QString::number(v->val).size();
    int len_ell = len_num * 15 < 30 ? 30 : len_num * 15;
    len_ell = len_ell > 7 * 15 ? 7 * 15 : len_ell;

    int delta = len_num / 2 * 15 < 15 ? 15 : len_num / 2 * 15;
    delta = len_num / 2 * 15 > 15 * 3 ? 15 * 3 : len_num / 2 * 15;

    int x_delta = len_num * 5 < 10 ? 10 : len_num * 4;
    x_delta = len_num * 4 > 50 ? 50 : len_num * 4;

    if (v->color == RED) {
        scene_rb->addEllipse(x_this, y_need - 15, len_ell, 30, QPen(QColor(39, 72, 50, 250)),QBrush(QColor(250, 0, 0, 250)));
    } else {
        scene_rb->addEllipse(x_this, y_need - 15, len_ell, 30, QPen(QColor(39, 72, 50, 250)),QBrush(QColor(39, 72, 50, 250)));
    }

    QGraphicsTextItem *text = scene_rb->addText(QString::number(v->val), QFont("Ubuntu"));
    text->setHtml("<center><p style=\"color:white;\">" + QString::number(v->val) + "</p></center>");
    text->setTextWidth(len_ell);
    text->setPos(x_this, y_need - 10);
}

int64_t x_need_splay, x_plus_splay, y_plus_splay;

void MainWindow::out_splay(splay * v, int64_t y_need, int64_t x_prev, int64_t y_prev, int64_t need_left) {
    if (v == nullptr) {
        return;
    }

    out_splay(v->left, y_need + y_plus_splay, x_plus_splay * (size_splay(v->left) + 1 + need_left), y_need, need_left);
    int64_t x_this = x_need_splay;
    if (x_prev != -1) {
        scene_splay->addLine(x_need_splay, y_need, x_prev, y_prev, QPen(QColor(49, 10, 10, 250)));
    }

    x_need_splay += x_plus_splay;

    out_splay(v->right, y_need + y_plus_splay, x_plus_splay * (size_splay(v->left) + 1 + need_left), y_need, need_left + 1 + size_splay(v->left));

    int len_num = QString::number(v->val).size();
    int len_ell = len_num * 15 < 30 ? 30 : len_num * 15;
    len_ell = len_ell > 7 * 15 ? 7 * 15 : len_ell;

    int delta = len_num / 2 * 15 < 15 ? 15 : len_num / 2 * 15;
    delta = len_num / 2 * 15 > 15 * 3 ? 15 * 3 : len_num / 2 * 15;

    int x_delta = len_num * 5 < 6 ? 6 : len_num * 4;
    x_delta = len_num * 4 > 50 ? 50 : len_num * 4;

    scene_splay->addEllipse(x_this, y_need - 15, len_ell, 30, QPen(QColor(39, 72, 50, 250)),QBrush(QColor(39, 72, 50, 250)));
    QGraphicsTextItem *text = scene_splay->addText(QString::number(v->val), QFont("Ubuntu"));
    text->setHtml("<center><p style=\"color:white;\">" + QString::number(v->val) + "</p></center>");
    text->setTextWidth(len_ell);
    text->setPos(x_this, y_need - 10);
}

void MainWindow::paintEvent(QPaintEvent *event) {
    if (T == nullptr) {
        goto end1;
    }

    scene_avl->clear();
    x_plus_avl = x_need_avl = 800 / (T -> size + 1);
    y_plus_avl = 600 / (T -> h + 1);
    out_avltree(T, y_plus_avl, -1, -1, 0);

    end1:;

    if (root == nullptr)
        goto end2;
    scene_rb->clear();
    x_plus_rb = x_need_rb = 800 / (size_rb(root) + 1);
    y_plus_rb = 600 / height_rb(root);
    out_rbtree(root, y_plus_rb, -1, -1, 0);

    end2:;

    if (S == nullptr) {
        goto end3;
    }
    scene_splay->clear();
    x_plus_splay = x_need_splay = 800 / (size_splay(S) + 1);
    y_plus_splay = 600 / height_splay(S);
    out_splay(S, y_plus_rb, -1, -1, 0);

    end3:;
}


bool is_number(QString inp) {
    if (!inp.size()) {
        return 0;
    }
    if (inp[0] == '0' && inp.size() > 1) {
        return 0;
    }
    for (int i = 0; i < inp.size(); ++i) {
        if (inp[i] == '-' && !i) {
            continue;
        }
        if (inp[i] < '0' || inp[i] > '9') {
            return 0;
        }
    }
    return 1;
}

void MainWindow::on_button_insert_avl_clicked() {
    if (is_number(ui->input_avl->text())){
        T = insert_avl(T, ui->input_avl->text().toLongLong());
        repaint();
    }
}

void MainWindow::on_button_delete_avl_clicked() {
    if (is_number(ui->input_avl->text())) {
        T = erase_avl(T, ui->input_avl->text().toLongLong());
        repaint();
    }
}

void MainWindow::on_button_insert_rb_clicked() {
    if (is_number(ui->input_rb->text())){
        root = insertNode(root, ui->input_rb->text().toLongLong());
        repaint();
    }
}

void MainWindow::on_button_delete_rb_clicked() {
    if (is_number(ui->input_rb->text())) {
        root = deleteNode(root, findNode(root, ui->input_rb->text().toLongLong()));
        repaint();
    }
}

void MainWindow::on_button_insert_splay_clicked() {
    if (is_number(ui->input_splay->text())){
        S = Insert(ui->input_splay->text().toLongLong(), S);
        repaint();
    }
}

void MainWindow::on_button_delete_splay_clicked() {
    if (is_number(ui->input_splay->text())) {
        S = Delete(ui->input_splay->text().toLongLong(), S);
        repaint();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    if (key == Qt :: Key_Enter){
        if (is_number(ui->input_avl->text())){
            T = insert_avl(T, ui->input_avl->text().toLongLong());
            repaint();
        } else if (is_number(ui->input_rb->text())) {
            root = insertNode(root, ui->input_rb->text().toLongLong());
            repaint();
        } else if (is_number(ui->input_splay->text())) {
            S = Insert(ui->input_splay->text().toLongLong(), S);
            repaint();
        }
        repaint();
        return;
    } else if (key == Qt :: Key_Delete){
        if (is_number(ui->input_avl->text())){
            T = erase_avl(T, ui->input_avl->text().toLongLong());
            repaint();
        }
        repaint();
        return;
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
