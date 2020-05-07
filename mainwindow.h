#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum RoomSize {queen, king};
    enum RoomType {standard, atrium};

private slots:
    void on_bookButton_clicked();

    void on_confirmButton_clicked();

    void on_nameTextField_textChanged();

    void on_sizeQueenButton_clicked();

    void on_viewStandardButton_clicked();

    void on_viewAtriumButton_clicked();

    void on_adultSpinbox_valueChanged(int arg1);

    void on_childSpinbox_valueChanged(int arg1);

    void on_checkInDate_userDateChanged(const QDate &date);

    void on_nightsSpinbox_valueChanged(int arg1);

    void on_sizeKingButton_clicked();

    void on_parkingButton_clicked();

    void on_checkoutButton_clicked();

    void on_creditCardTextField_textChanged();

    void on_agreementBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QString clientName;

    QPixmap discountImage;

    QPixmap queenStandardImage;
    QPixmap queenAtriumImage;
    QPixmap kingStandardImage;
    QPixmap kingAtriumImage;

    RoomSize roomSize = RoomSize::queen;
    RoomType roomType = RoomType::standard;

    double roomCost = 284.00;
    double currentCost = 284.00;

    int numOfAdults = 1;
    int numOfChildren = 0;

    QDate checkInDate;
    int nights = 1;

    bool parking = false;

    void updateCost();
    void loadAssets();

    std::string creditCardEnd;
};
#endif // MAINWINDOW_H
