#pragma once

#include <QMainWindow>
#include <QStringListModel>
#include <QListWidgetItem>

#include <random>

#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetRandomGen(const std::mt19937& random_gen);

private slots:

    void on_btn_push_back_clicked();

    void on_btn_pop_back_clicked();

    void on_btn_clear_clicked();

    void on_btn_week_days_clicked();

    void on_btn_monthes_clicked();



    void on_list_widget_currentRowChanged(int currentRow);

    void on_btn_edit_clicked();

    void on_btn_erase_clicked();

    void on_btn_insert_clicked();

    void on_btn_decr_clicked();

    void on_btn_incr_clicked();

    void on_btn_begin_clicked();

    void on_btn_end_clicked();

    void on_btn_resize_clicked();

    void on_btn_reserve_clicked();

    void on_btn_find_clicked();

    void on_btn_count_clicked();

    void on_btn_min_element_clicked();

    void on_btn_max_element_clicked();

    void on_btn_sort_clicked();

    void on_btn_sOrT_clicked();

    void on_btn_unique_clicked();

    void on_btn_reverse_clicked();

    void on_btn_shuffle_clicked();

private:
    void ApplyModel();
    void ApplyIterator();
    bool case_insensitive_equal(char a, char b);

private:

    std::mt19937 gen_;
    Model vector_model_;
    Ui::MainWindow *ui;
};
