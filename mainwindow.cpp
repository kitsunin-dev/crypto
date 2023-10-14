#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "encrypt.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    const QStringList ciphers = {"Choose cipher...", "Atbash", "Caesar", "Playfair", "Vigenère"};

    this->setFixedSize(QSize(450, 400));
    this->setWindowTitle("Cryptographer 0.1");

    ui->setupUi(this);

    ui->caesarLabel->setVisible(false);
    ui->keyLabel->setVisible(false);
    ui->spinBox->setVisible(false);
    ui->keyEdit->setVisible(false);

    ui->inputText->setPlaceholderText("Enter a message to encrypt...");
    ui->outputText->setPlaceholderText("Encrypted message will appear here...");
    ui->comboBox->addItems(ciphers);

    connect(ui->encrButton, &QPushButton::clicked, this, &MainWindow::cipherText);
}

void MainWindow::cipherText()
{
    QString text = ui->inputText->toPlainText();
    Encrypt encrypter(text);

    switch(ui->comboBox->currentIndex())
    {
        case 1:
            ui->outputText->setPlainText(encrypter.atbash());
            break;
        case 2:
            ui->outputText->setPlainText(encrypter.caesar(ui->spinBox->value()));
            break;
        case 3:
            ui->outputText->setPlainText(encrypter.playfair(ui->keyEdit->text()));
            break;
        case 4:
            ui->outputText->setPlainText(encrypter.vigenere(ui->keyEdit->text()));
            break;
        default:
            break;
    }
}

void MainWindow::on_comboBox_activated(int index)
{
    switch(index)
    {
        case 2:
            ui->caesarLabel->setVisible(true);
            ui->keyLabel->setVisible(false);
            ui->spinBox->setVisible(true);
            ui->keyEdit->setVisible(false);
            break;
        case 3:
        case 4:
            ui->caesarLabel->setVisible(false);
            ui->keyLabel->setVisible(true);
            ui->spinBox->setVisible(false);
            ui->keyEdit->setVisible(true);
            break;
        default:
            ui->caesarLabel->setVisible(false);
            ui->keyLabel->setVisible(false);
            ui->spinBox->setVisible(false);
            ui->keyEdit->setVisible(false);
            break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
