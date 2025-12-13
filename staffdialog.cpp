#include "staffdialog.h"
#include "ui_staffdialog.h"

#include <QRegularExpressionValidator>

StaffDialog::StaffDialog(Staff* staff, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StaffDialog)
{
    ui->setupUi(this);

    if (staff)
    {
        ui->num_certificate_edit->setText(staff->GetNumCertificate());
        ui->surname_edit->setText(staff->GetSurname());
        ui->name_edit->setText(staff->GetName());
        ui->patronym_edit->setText(staff->GetPatronym());
        ui->profession_box->setCurrentIndex(staff->GetProfession());
    }

    QRegularExpressionValidator* val1 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val2 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val3 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val4 = new QRegularExpressionValidator(this);

    val1->setRegularExpression(QRegularExpression("(БП|ПЛ|ИН)-[0-9]{6}"));
    val2->setRegularExpression(QRegularExpression("([A-Z][a-z]+-[A-Z][a-z]+|[А-Я][а-я]+-[А-Я][а-я]+)"));
    val3->setRegularExpression(QRegularExpression("([A-Z][a-z]+-[A-Z][a-z]+|[А-Я][а-я]+-[А-Я][а-я]+)"));
    val4->setRegularExpression(QRegularExpression("([A-Z][a-z]+-[A-Z][a-z]+|[А-Я][а-я]+-[А-Я][а-я]+)"));

    ui->num_certificate_edit->setValidator(val1);
    ui->surname_edit->setValidator(val2);
    ui->name_edit->setValidator(val3);
    ui->patronym_edit->setValidator(val4);

    connect(ui->num_certificate_edit, &QLineEdit::textChanged, this, &StaffDialog::Validation);
    connect(ui->surname_edit, &QLineEdit::textChanged, this, &StaffDialog::Validation);
    connect(ui->name_edit, &QLineEdit::textChanged, this, &StaffDialog::Validation);
    connect(ui->patronym_edit, &QLineEdit::textChanged, this, &StaffDialog::Validation);
    connect(ui->profession_box, &QComboBox::currentIndexChanged, this, &StaffDialog::Validation);
}

StaffDialog::~StaffDialog()
{
    delete ui;
}

void StaffDialog::Validation() const
{
    if (ui->num_certificate_edit->text().length() == 9 &&
        ui->surname_edit->text().length() > 0 && ui->surname_edit->text().length() <= 20 &&
        ui->name_edit->text().length() > 0 && ui->name_edit->text().length() <= 20 &&
        ui->patronym_edit->text().length() > 0 && ui->patronym_edit->text().length() <= 20)
        ui->buttonBox->setEnabled(true);
    else
        ui->buttonBox->setEnabled(false);
}

Staff StaffDialog::GetData() const
{
    return Staff(ui->num_certificate_edit->text(), ui->surname_edit->text(), ui->name_edit->text(),
                 ui->patronym_edit->text(), (Profession)ui->profession_box->currentIndex());
}
