#include "purposewindow.h"
#include "ui_purposewindow.h"

#include <QMessageBox>
#include "purposedialog.h"
#include "nominationdialog.h"

PurposeWindow::PurposeWindow(DataBase* db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PurposeWindow)
{
    ui->setupUi(this);

    this->database = db;

    this->source_model = new PurposeTableModel(this->database, this);

    this->proxy_model = new PurposeProxyModel(ui->num_flight_edit, ui->num_certificate_edit, ui->nomination_box, this);

    this->proxy_model->setSourceModel(this->source_model);

    ui->purpose_table->setModel(this->proxy_model);

    QRegularExpressionValidator* val1 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val2 = new QRegularExpressionValidator(this);

    val1->setRegularExpression(QRegularExpression("[A-Z]{3}-[0-9]{3}"));
    val2->setRegularExpression(QRegularExpression("(БП|ПЛ|ИН)-[0-9]{6}"));

    ui->num_flight_edit->setValidator(val1);
    ui->num_certificate_edit->setValidator(val2);

    connect(ui->add_button, &QPushButton::clicked, this, &PurposeWindow::AddPurpose);
    connect(ui->change_button, &QPushButton::clicked, this, &PurposeWindow::ChangePurpose);
    connect(ui->delete_button, &QPushButton::clicked, this, &PurposeWindow::RemovePurpose);
}

PurposeWindow::~PurposeWindow()
{
    delete ui;
}

void PurposeWindow::AddPurpose()
{
    PurposeDialog add_dialog(NULL, this);
    QMessageBox box;

    box.setWindowTitle("Уведомление");
    box.setIcon(QMessageBox::Warning);

    if (add_dialog.exec() == 1)
    {
        Purpose purpose = add_dialog.GetData();
        bool (*func)(const Purpose&, const Purpose&) = [](const Purpose& a, const Purpose& b)
        {
            return a.GetNumFlight() == b.GetNumFlight() && a.GetNumCertificate() == b.GetNumCertificate();
        };

        // Проверка на существование назначения с такими параметрами
        if (this->database->FindPurpose(purpose, func) != -1)
        {
            box.setText("Назначение с такими параметрами уже есть в системе!");
            box.exec();
        }
        else
        {
            // Проверка на существование рейса
            bool (*findFlightFunc)(const Flight&, const Flight&) = [](const Flight& a, const Flight& b)
            {
                return a.GetNumFlight() == b.GetNumFlight();
            };

            if (this->database->FindFlight(Flight(purpose.GetNumFlight(), "", "", "", QDate(), QTime(), FlightState::ON_TIME, 0, 0), findFlightFunc) == -1)
            {
                box.setText("Система не смогла добавить назначение!");
                box.exec();
                return;
            }

            // Проверка на существование сотрудника
            bool (*findStaffFunc)(const Staff&, const Staff&) = [](const Staff& a, const Staff& b)
            {
                return a.GetNumCertificate() == b.GetNumCertificate();
            };

            if (this->database->FindStaff(Staff(purpose.GetNumCertificate(), "", "", "", Profession::PILOT), findStaffFunc) == -1)
            {
                box.setText("Система не смогла добавить назначение!");
                box.exec();
                return;
            }

            this->database->AddPurpose(purpose, true);

            box.setText("Назначение добавлено в систему!");
            box.exec();
        }
    }
}

void PurposeWindow::ChangePurpose()
{
    NominationDialog old_dialog(this);
    QMessageBox box;

    box.setWindowTitle("Уведомление");
    box.setIcon(QMessageBox::Warning);

    if (old_dialog.exec() == 1)
    {
        QStringList old_nomination = old_dialog.GetData().split("*");
        QString old_num_flight = old_nomination[0];
        QString old_num_certificate = old_nomination[1];

        bool (*func)(const Purpose&, const Purpose&) = [](const Purpose& a, const Purpose& b)
        {
            return a.GetNumFlight() == b.GetNumFlight() && a.GetNumCertificate() == b.GetNumCertificate();
        };

        int i = this->database->FindPurpose(Purpose(Nomination::FIRST_PILOT, old_num_flight, old_num_certificate), func);

        if (i == -1)
        {
            box.setText("Назначения с такими параметрами нет в системе!");
            box.exec();
        }
        else
        {
            Purpose purpose = this->database->GetPurpose(i);
            PurposeDialog upd_dialog(&purpose, this);

            if (upd_dialog.exec() == 1)
            {
                Purpose new_purpose = upd_dialog.GetData();

                int j = this->database->FindPurpose(new_purpose, func);

                if (j != -1)
                {
                    box.setText("Система не смогла обновить назначение!");
                    box.exec();
                }
                else
                {
                    this->database->UpdatePurpose(new_purpose, i, true);
                    box.setText("Система обновила назначение!");
                    box.exec();
                }
            }
        }
    }
}

void PurposeWindow::RemovePurpose()
{
    NominationDialog del_dialog(this);
    QMessageBox box;

    box.setWindowTitle("Уведомление");
    box.setIcon(QMessageBox::Warning);

    if (del_dialog.exec() == 1)
    {
        QStringList nomination = del_dialog.GetData().split("*");
        QString num_flight = nomination[0];
        QString num_certificate = nomination[1];
        bool (*func)(const Purpose&, const Purpose&) = [](const Purpose& a, const Purpose& b)
        {
            return a.GetNumFlight() == b.GetNumFlight() && a.GetNumCertificate() == b.GetNumCertificate();
        };

        if (this->database->FindPurpose(Purpose(Nomination::FIRST_PILOT, num_flight, num_certificate), func) == -1)
        {
            box.setText("Назначения с такими параметрами нет в системе!");
            box.exec();
        }
        else
        {
            this->database->RemovePurpose(this->database->FindPurpose(Purpose(Nomination::FIRST_PILOT, num_flight, num_certificate), func), true);

            box.setText("Назначение и связанные с ним данные удалены из системы!");
            box.exec();
        }
    }
}
