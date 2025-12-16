#include "purposedialog.h"
#include "ui_purposedialog.h"

#include <QRegularExpressionValidator>

PurposeDialog::PurposeDialog(Purpose* purpose, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PurposeDialog)
{
    ui->setupUi(this);

    if (purpose)
    {
        ui->nomination_box->setCurrentIndex(purpose->GetName());
        ui->num_flight_edit->setText(purpose->GetNumFlight());
        ui->num_certificate_edit->setText(purpose->GetNumCertificate());
    }

    QRegularExpressionValidator* val1 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val2 = new QRegularExpressionValidator(this);

    val1->setRegularExpression(QRegularExpression("[A-Z]{3}-[0-9]{3}"));
    val2->setRegularExpression(QRegularExpression("(БП|ПЛ|ИН)-[0-9]{6}"));

    ui->num_flight_edit->setValidator(val1);
    ui->num_certificate_edit->setValidator(val2);

    connect(ui->nomination_box, &QComboBox::currentIndexChanged, this, &PurposeDialog::Validation);
    connect(ui->num_flight_edit, &QLineEdit::textChanged, this, &PurposeDialog::Validation);
    connect(ui->num_certificate_edit, &QLineEdit::textChanged, this, &PurposeDialog::Validation);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

PurposeDialog::~PurposeDialog()
{
    delete ui;
}

void PurposeDialog::Validation() const
{
    if (ui->num_flight_edit->text().length() == 7 && ui->num_certificate_edit->text().length() == 9)
        ui->buttonBox->setEnabled(true);
    else
        ui->buttonBox->setEnabled(false);
}

Purpose PurposeDialog::GetData() const
{
    return Purpose((Nomination)ui->nomination_box->currentIndex(), ui->num_flight_edit->text(), ui->num_certificate_edit->text());
}
