#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(200, 211, 213));
    ui->stackedWidget->widget(0)->setAutoFillBackground(true);
    ui->stackedWidget->widget(0)->setPalette(pal);

    ui->stackedWidget->widget(1)->setAutoFillBackground(true);
    ui->stackedWidget->widget(1)->setPalette(pal);

    ui->stackedWidget->widget(2)->setAutoFillBackground(true);
    ui->stackedWidget->widget(2)->setPalette(pal);

    ui->centralwidget->setAutoFillBackground(true);
    ui->centralwidget->setPalette(pal);

    this->loadAssets();
    ui->discountLabel->setPixmap(discountImage);
    ui->roomPreviewLabel->setPixmap(queenStandardImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadAssets()
{

    QString discountFilePath = ":/assets/Discount.png";
    if (discountImage.load(discountFilePath)) {
        std::cout << "Loaded Discount image" << std::endl;
        discountImage = discountImage.scaled(ui->discountLabel->size(), Qt::KeepAspectRatioByExpanding);
    }

    QString queenStandardFilePath = ":/assets/queen_standard.jpg";
    QString queenAtriumFilePath = ":/assets/queen_atrium.jpg";

    QString kingStandardFilePath = ":/assets/king_standard.jpg";
    QString kingAtriumFilePath = ":/assets/king_atrium.jpg";

    if (queenStandardImage.load(queenStandardFilePath)) {
        std::cout << "Loaded Queen Standard image" << std::endl;
        queenStandardImage = queenStandardImage.scaled(ui->discountLabel->size(), Qt::KeepAspectRatioByExpanding);
    }

    if (queenAtriumImage.load(queenAtriumFilePath)) {
        std::cout << "Loaded Queen Atrium image" << std::endl;
        queenAtriumImage = queenAtriumImage.scaled(ui->discountLabel->size(), Qt::KeepAspectRatioByExpanding);
    }

    if (kingStandardImage.load(kingStandardFilePath)) {
        std::cout << "Loaded King Standard image" << std::endl;
        kingStandardImage = kingStandardImage.scaled(ui->discountLabel->size(), Qt::KeepAspectRatioByExpanding);
    }

    if (kingAtriumImage.load(kingAtriumFilePath)) {
        std::cout << "Loaded Queen Atrium image" << std::endl;
        kingAtriumImage = kingAtriumImage.scaled(ui->discountLabel->size(), Qt::KeepAspectRatioByExpanding);
    }
}

void MainWindow::on_bookButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

    std::stringstream ss;

    ss << std::setprecision(2) << std::fixed << (roomCost * nights);
    std::string labelUpdate = "$" + ss.str();
    ui->roomCostLabel->setText(QString(labelUpdate.c_str()));

    if (parking) {
        ss.str("");
        ss << std::setprecision(2) << std::fixed << (12.75 * nights);
        labelUpdate = "$" + ss.str();
        ui->parkingFeeLabel->setText(QString(labelUpdate.c_str()));
        ui->parkingLabel->setText("Yes");
    }

    ui->resortFeeLabel->setText("$15.00");

    ss.str("");
    ss << std::setprecision(2) << std::fixed << (currentCost + 15.00);
    labelUpdate = "$" + ss.str();
    ui->totalLabel->setText(QString(labelUpdate.c_str()));
    ui->confirmCharge->setText(QString(labelUpdate.c_str()));
    ui->checkInDateConfirm->setDate(this->checkInDate);
    ui->nightsConfirm->setNum(this->nights);
    ui->adultsLabelConfirm->setNum(this->numOfAdults);
    ui->childrenLabelConfirm->setNum(this->numOfChildren);
}

void MainWindow::on_checkoutButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->cardConfirmLabel->setText(QString(this->creditCardEnd.c_str()));
}

void MainWindow::on_confirmButton_clicked()
{
    QApplication::exit();
}

void MainWindow::on_nameTextField_textChanged()
{
    this->clientName = ui->nameTextField->toPlainText();
}

void MainWindow::on_sizeQueenButton_clicked()
{
    this->roomSize = RoomSize::queen;
    this->updateCost();
}

void MainWindow::on_sizeKingButton_clicked()
{
    this->roomSize = RoomSize::king;
    this->updateCost();
}

void MainWindow::on_viewStandardButton_clicked()
{
    this->roomType = RoomType::standard;
    this->updateCost();
}

void MainWindow::on_viewAtriumButton_clicked()
{
    this->roomType = RoomType::atrium;
    this->updateCost();
}

void MainWindow::on_adultSpinbox_valueChanged(int arg1)
{
    if (roomSize == RoomSize::king && ui->childSpinbox->value() + arg1 <= 3) {
        this->numOfAdults = arg1;
    } else if (roomSize == RoomSize::queen && ui->childSpinbox->value() + arg1 <= 4) {
        this->numOfAdults = arg1;
    } else {
        ui->adultSpinbox->setValue(arg1 - 1);
    }
}

void MainWindow::on_childSpinbox_valueChanged(int arg1)
{
    if (roomSize == RoomSize::king && ui->adultSpinbox->value() + arg1 <= 3) {
        this->numOfChildren = arg1;
    } else if (roomSize == RoomSize::queen && ui->adultSpinbox->value() + arg1 <= 4) {
        this->numOfChildren = arg1;
    } else {
        ui->childSpinbox->setValue(arg1 - 1);
    }
}

void MainWindow::on_checkInDate_userDateChanged(const QDate &date)
{
    this->checkInDate = date;
}

void MainWindow::on_nightsSpinbox_valueChanged(int arg1)
{
    this->nights = arg1;
    this->updateCost();
}

void MainWindow::updateCost()
{
    if (this->roomType == RoomType::standard && this->roomSize == RoomSize::queen) {
        this->roomCost = 284.00;
        this->currentCost = roomCost * nights;
        ui->roomPreviewLabel->setPixmap(queenStandardImage);
    } else if (this->roomType == RoomType::atrium && this->roomSize == RoomSize::queen) {
        this->roomCost = 325.00;
        this->currentCost = roomCost * nights;
        ui->roomPreviewLabel->setPixmap(queenAtriumImage);
    } else if (this->roomType == RoomType::standard && this->roomSize == RoomSize::king) {
        this->roomCost = 290.00;
        this->currentCost = roomCost * nights;
        ui->roomPreviewLabel->setPixmap(kingStandardImage);
    } else if (this->roomType == RoomType::atrium && this->roomSize == RoomSize::king) {
        this->roomCost = 350.00;
        this->currentCost = roomCost * nights;
        ui->roomPreviewLabel->setPixmap(kingAtriumImage);
    } else {
        // Something Broke
    }

    if (parking) {
        this->currentCost += (12.75 * this->nights);
    }

    std::stringstream ss;
    ss << std::setprecision(2) << std::fixed << currentCost;
    std::string labelUpdate = "$" + ss.str();
    ui->priceLabel->setText(QString(labelUpdate.c_str()));
}

void MainWindow::on_parkingButton_clicked()
{
    this->parking = ui->parkingButton->isChecked();
    this->updateCost();
}

void MainWindow::on_creditCardTextField_textChanged()
{
    std::string ccField = ui->creditCardTextField->toPlainText().toStdString();
    std::stringstream ss;
    if (ccField[0] == '3' && ccField.length() == 15) {
        ui->checkoutButton->setEnabled(true);
        ss << ccField[11] << ccField[12] << ccField[13] << ccField[14];
        this->creditCardEnd = ss.str();
        ui->cardTypeLabel->setText("American Express");
    } else if ((ccField[0] == '4' || ccField[0] == '5' || ccField[0] == '6') && ccField.length() == 16) {
        ui->checkoutButton->setEnabled(true);
        ss << ccField[12] << ccField[13] << ccField[14] << ccField[15];
        this->creditCardEnd = ss.str();

        if (ccField[0] == '4') {
            ui->cardTypeLabel->setText("Visa");
        } else if (ccField[0] == '5') {
            ui->cardTypeLabel->setText("Mastercard");
        } else if (ccField[0] == '6') {
            ui->cardTypeLabel->setText("Discover");
        } else {
            ui->cardTypeLabel->setText("Other Card");
        }
    } else {
        ui->checkoutButton->setEnabled(false);
    }
}


void MainWindow::on_agreementBox_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        ui->confirmButton->setEnabled(true);
    } else {
        ui->confirmButton->setEnabled(false);
    }
}
