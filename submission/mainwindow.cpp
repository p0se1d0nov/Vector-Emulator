#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

#include <algorithm>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ApplyModel();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::ApplyModel() {
    // Реализуйте этот метод.
    if(vector_model_.items.empty()){
        ui->btn_pop_back->setDisabled(true);
    }
    else {
        ui->btn_pop_back->setDisabled(false);
    }

    auto preserve_iter = vector_model_.iterator;
    ui->list_widget->clear();
    for(size_t i = 0; i < vector_model_.items.size(); i++){
        ui->list_widget->addItem(QString::fromStdString(std::format("{}: {}", i, vector_model_.items[i])));
    }
    ui->list_widget->addItem(QString::fromStdString("end"));

    vector_model_.iterator = preserve_iter;

    ui->txt_size->setText(QString::number(vector_model_.items.size()));
    ui->txt_capacity->setText(QString::number(vector_model_.items.capacity()));

    ApplyIterator();
}

void MainWindow::ApplyIterator()
{
    int iter_offset = std::distance(vector_model_.items.begin(), vector_model_.iterator);
    ui->list_widget->setCurrentRow(iter_offset);

    if(vector_model_.iterator == vector_model_.items.end()){
        ui->btn_edit->setDisabled(true);
        ui->btn_erase->setDisabled(true);
        ui->btn_incr->setDisabled(true);
    }
    else{
        ui->btn_edit->setDisabled(false);
        ui->btn_erase->setDisabled(false);
        ui->btn_incr->setDisabled(false);
    }

    if(vector_model_.iterator == vector_model_.items.begin()){
        ui->btn_decr->setDisabled(true);
    }
    else {
        ui->btn_decr->setDisabled(false);
    }

    if(vector_model_.iterator == vector_model_.items.end()){
        ui->txt_elem_content->setText("");
    }
    else {
        ui->txt_elem_content->setText(QString::fromStdString(*vector_model_.iterator));
    }


}

void MainWindow::on_btn_push_back_clicked() {
    auto text = ui->txt_elem_content->text().toStdString();
    vector_model_.items.push_back(text);
    vector_model_.iterator = vector_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_pop_back_clicked()
{
    vector_model_.items.pop_back();
    vector_model_.iterator = vector_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_clear_clicked()
{
    vector_model_.items.clear();
    vector_model_.iterator = vector_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_week_days_clicked()
{
    static std::vector<std::string> days_of_week = {
        "Понедельник",
        "Вторник",
        "Среда",
        "Четверг",
        "Пятница",
        "Суббота",
        "Воскресенье"
    };


    vector_model_.items = days_of_week;
    vector_model_.iterator = vector_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_monthes_clicked()
{
    static std::vector<std::string> months_of_year = {
        "Январь",
        "Февраль",
        "Март",
        "Апрель",
        "Май",
        "Июнь",
        "Июль",
        "Август",
        "Сентябрь",
        "Октябрь",
        "Ноябрь",
        "Декабрь"
    };

    vector_model_.items = months_of_year;
    vector_model_.iterator = vector_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_list_widget_currentRowChanged(int currentRow) {
    if (currentRow == -1) return;

    if (currentRow == static_cast<int>(vector_model_.items.size())) {
        // Выбран элемент "end"
        vector_model_.iterator = vector_model_.items.end();
    } else {
        vector_model_.iterator = vector_model_.items.begin() + currentRow;
    }
    ApplyIterator();
}


void MainWindow::on_btn_edit_clicked()
{
    if(vector_model_.iterator == vector_model_.items.end()) return;

    *vector_model_.iterator = ui->txt_elem_content->text().toStdString();
    ApplyModel();
}


void MainWindow::on_btn_erase_clicked()
{
    if(vector_model_.iterator == vector_model_.items.end()) return;

    vector_model_.items.erase(vector_model_.iterator);
    vector_model_.iterator = vector_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_insert_clicked()
{
    vector_model_.items.insert(vector_model_.iterator, ui->txt_elem_content->text().toStdString());
    vector_model_.iterator = vector_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_decr_clicked()
{
    if(vector_model_.iterator == vector_model_.items.begin()) return;

    vector_model_.iterator--;
    ApplyIterator();
}


void MainWindow::on_btn_incr_clicked()
{
    if(vector_model_.iterator == vector_model_.items.end()) return;

    vector_model_.iterator++;
    ApplyIterator();
}


void MainWindow::on_btn_begin_clicked()
{
    vector_model_.iterator = vector_model_.items.begin();
    ApplyIterator();
}


void MainWindow::on_btn_end_clicked()
{
    vector_model_.iterator = vector_model_.items.end();
    ApplyIterator();
}


void MainWindow::on_btn_resize_clicked()
{

    vector_model_.items.resize(ui->txt_size->text().toInt());
    vector_model_.iterator = vector_model_.items.begin();
    ApplyModel();

}


void MainWindow::on_btn_reserve_clicked()
{
    vector_model_.items.reserve(ui->txt_capacity->text().toInt());
    vector_model_.iterator = vector_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_find_clicked()
{
    vector_model_.iterator = std::find(vector_model_.iterator, vector_model_.items.end(), ui->txt_elem_content->text().toStdString());

    ApplyIterator();
}


void MainWindow::on_btn_count_clicked()
{
    int count_elems = std::count(vector_model_.items.begin(), vector_model_.items.end(), ui->le_count->text().toStdString());
    ui->lbl_count->setText(QString::number(count_elems));
}


void MainWindow::on_btn_min_element_clicked()
{
    vector_model_.iterator = std::min_element(vector_model_.items.begin(), vector_model_.items.end());

    ApplyIterator();
}


void MainWindow::on_btn_max_element_clicked()
{
    vector_model_.iterator = std::max_element(vector_model_.items.begin(), vector_model_.items.end());

    ApplyIterator();
}


void MainWindow::on_btn_sort_clicked()
{
    std::sort(vector_model_.items.begin(), vector_model_.items.end());

    ApplyModel();
}

bool case_insensitive_equal(char a, char b) {
    return std::tolower(static_cast<unsigned char>(a)) ==
           std::tolower(static_cast<unsigned char>(b));
}

void MainWindow::on_btn_sOrT_clicked()
{
    std::sort(vector_model_.items.begin(), vector_model_.items.end(), [](std::string s1, std::string s2){
        for(auto& el : s1){
            el = std::tolower(el);
        }
        for(auto& el : s2){
            el = std::tolower(el);
        }

        return s1 < s2;
    });

    ApplyModel();
}


void MainWindow::on_btn_unique_clicked()
{
    if(std::is_sorted(vector_model_.items.begin(), vector_model_.items.end())){
        auto to_del = std::unique(vector_model_.items.begin(), vector_model_.items.end());
        vector_model_.items.erase(to_del, vector_model_.items.end());
        vector_model_.iterator = vector_model_.items.begin();
    }
    ApplyModel();
}


void MainWindow::on_btn_reverse_clicked()
{
    std::reverse(vector_model_.items.begin(), vector_model_.items.end());

    ApplyModel();
}


void MainWindow::on_btn_shuffle_clicked()
{
    std::shuffle(vector_model_.items.begin(), vector_model_.items.end(), gen_);

    ApplyModel();
}

void MainWindow::SetRandomGen(const std::mt19937& random_gen){
    gen_ = random_gen;
}
