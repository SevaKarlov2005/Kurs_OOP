#include "passengerdialog.h"
#include "ui_passengerdialog.h"

PassengerDialog::PassengerDialog(Passenger* passenger, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PassengerDialog)
{
    ui->setupUi(this);

    if (passenger)
    {
        ui->num_passport_edit->setText(passenger->GetNumPassport());
        ui->place_passport_edit->setText(passenger->GetPlacePassport());
        ui->date_passport_date->setDate(passenger->GetDatePassport());
        ui->surname_edit->setText(passenger->GetSurname());
        ui->name_edit->setText(passenger->GetName());
        ui->patronym_edit->setText(passenger->GetPatronym());
        ui->birthday_date->setDate(passenger->GetBirthday());
    }

    QRegularExpressionValidator* val1 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val2 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val3 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val4 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val5 = new QRegularExpressionValidator(this);

    val1->setRegularExpression(QRegularExpression("[0-9]{4}-[0-9]{6}"));
    val2->setRegularExpression(QRegularExpression("([A-Z][a-z]+[- ][A-Z][a-z]+|[А-Я][а-я]+[- ][А-Я][а-я]+)"));
    val3->setRegularExpression(QRegularExpression("([A-Z][a-z]+-[A-Z][a-z]+|[А-Я][а-я]+-[А-Я][а-я]+)"));
    val4->setRegularExpression(QRegularExpression("([A-Z][a-z]+-[A-Z][a-z]+|[А-Я][а-я]+-[А-Я][а-я]+)"));
    val5->setRegularExpression(QRegularExpression("([A-Z][a-z]+-[A-Z][a-z]+|[А-Я][а-я]+-[А-Я][а-я]+)"));

    ui->num_passport_edit->setValidator(val1);
    ui->place_passport_edit->setValidator(val2);
    ui->surname_edit->setValidator(val3);
    ui->name_edit->setValidator(val4);
    ui->patronym_edit->setValidator(val5);

    connect(ui->num_passport_edit, &QLineEdit::textChanged, this, &PassengerDialog::Validation);
    connect(ui->place_passport_edit, &QLineEdit::textChanged, this, &PassengerDialog::Validation);
    connect(ui->date_passport_date, &QDateEdit::dateChanged, this, &PassengerDialog::Validation);
    connect(ui->surname_edit, &QLineEdit::textChanged, this, &PassengerDialog::Validation);
    connect(ui->name_edit, &QLineEdit::textChanged, this, &PassengerDialog::Validation);
    connect(ui->patronym_edit, &QLineEdit::textChanged, this, &PassengerDialog::Validation);
    connect(ui->birthday_date, &QDateEdit::dateChanged, this, &PassengerDialog::Validation);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

PassengerDialog::~PassengerDialog()
{
    delete ui;
}

void PassengerDialog::Validation() const
{
    if (ui->num_passport_edit->text().length() == 11 &&
        ui->place_passport_edit->text().length() > 0 && ui->place_passport_edit->text().length() <= 50 &&
        (ui->date_passport_date->date().year() - ui->birthday_date->date().year() -
        (ui->date_passport_date->date().dayOfYear() < ui->birthday_date->date().dayOfYear())) >= 14 &&
        ui->surname_edit->text().length() > 0 && ui->surname_edit->text().length() <= 20 &&
        ui->name_edit->text().length() > 0 && ui->name_edit->text().length() <= 20 &&
        ui->patronym_edit->text().length() > 0 && ui->patronym_edit->text().length() <= 20 &&
        ui->date_passport_date->date() < QDate::currentDate())
        ui->buttonBox->setEnabled(true);
    else
        ui->buttonBox->setEnabled(false);
}

Passenger PassengerDialog::GetData() const
{
    return Passenger(ui->num_passport_edit->text(), ui->place_passport_edit->text(), ui->date_passport_date->date(),
                     ui->surname_edit->text(), ui->name_edit->text(), ui->patronym_edit->text(), ui->birthday_date->date());
}
