#include "MainForm.h"
//#include "Data.h"
#include "LoadData.h"
#include "EditForm.h"
#include "ShowingForm.h"
#include <msclr/marshal_cppstd.h>
using namespace System::Data::SqlClient;
using namespace System::IO;


using namespace System; 
using namespace System::Windows::Forms;


[System::STAThread]


void main(cli::array<System::String^>^ args) {
	System::Windows::Forms::Application::EnableVisualStyles();
	System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);

	LabaFour::MainForm from;
	System::Windows::Forms::Application::Run(% from);
}
System::Void LabaFour::MainForm::ShowTariffs_Click(Object^ sender, EventArgs^ e) {
	ShowingForm^ formmm = gcnew ShowingForm(listData);
	formmm->ShowDialog();
}
System::Void LabaFour::MainForm::AddTariff_Click(Object^ sender, EventArgs^ e) {
	EditForm^ formac = gcnew EditForm(this,listData);
	formac->ShowDialog();
}

System::Void LabaFour::MainForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	EditForm^ formac = gcnew EditForm(this, listData, 1);
	formac->ShowDialog();
}

System::Void LabaFour::MainForm::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
	try {
		// Database connection string
		String^ connectionString = "Server=(localdb)\\MSSQLLocalDB;Database=master;Trusted_Connection=True;";
		SqlConnection^ conn = gcnew SqlConnection(connectionString);
		conn->Open();

		// Query to fetch all records
		String^ query = "SELECT Destination, Price, Discount FROM Tariffs";
		SqlCommand^ cmd = gcnew SqlCommand(query, conn);
		SqlDataReader^ reader = cmd->ExecuteReader();

		// Clear existing data
		listData->Clear();

		// Read data from SQL and add to listData
		while (reader->Read()) {
			String^ destination = reader["Destination"]->ToString();
			int price = Convert::ToInt32(reader["Price"]);
			int discount = Convert::ToInt32(reader["Discount"]);
			listData->Add(gcnew ManagedData(destination, price, discount));
		}

		reader->Close();
		conn->Close();

		MessageBox::Show("Data successfully imported from the database.", "Success");
	}
	catch (Exception^ ex) {
		MessageBox::Show("Error importing data: " + ex->Message, "Error");
	}
}

System::Void LabaFour::MainForm::button3_Click(System::Object^ sender, System::EventArgs^ e)
{
	try {
		// Database connection string
		String^ connectionString = "Server=(localdb)\\MSSQLLocalDB;Database=master;Trusted_Connection=True;";
		SqlConnection^ conn = gcnew SqlConnection(connectionString);
		conn->Open();

		// Iterate over listData and insert into database
		for each (ManagedData ^ data in listData) {
			String^ query = "INSERT INTO Tariffs (Destination, Price, Discount) VALUES (@destination, @price, @discount)";
			SqlCommand^ cmd = gcnew SqlCommand(query, conn);
			cmd->Parameters->AddWithValue("@destination", data->GetDestination());
			cmd->Parameters->AddWithValue("@price", data->GetPrice());
			cmd->Parameters->AddWithValue("@discount", data->GetDiscount());
			cmd->ExecuteNonQuery();
		}

		conn->Close();
		MessageBox::Show("Data successfully exported to the database.", "Success");
	}
	catch (Exception^ ex) {
		MessageBox::Show("Error exporting data: " + ex->Message, "Error");
	}
}

//System::Void LabaFour::MainForm::ExitApp(Object^ sender, EventArgs^ e) {
//	Application::Exit();
//}
// 
// 
// 
// 
// 
// 
// 
//Airport airport;
//System::Void LabaFour::MainForm::ShowTariffs_Click (System::Object^ sender, System::EventArgs^ e) {
//	
//	//EditForm editform;
//	//editform.ShowDialog();
//}
//System::Void LabaFour::MainForm::AddTariff_Click(System::Object^ sender, System::EventArgs^ e) {
//
//}