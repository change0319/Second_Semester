#pragma once
#include"fileopen.h"
namespace File {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::Button^ button1;
	protected:

	private:
		FileInfo* NewFile;
		System::String^ FileName;
		System::String^ SaveRoad;
	private: System::Windows::Forms::Label^ label1;


	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog1;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Label^ label2;



		   System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->button1->Font = (gcnew System::Drawing::Font(L"Magneto", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(446, 136);
			this->button1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(105, 57);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Open";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::OnClick);
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::White;
			this->label1->Dock = System::Windows::Forms::DockStyle::Top;
			this->label1->Font = (gcnew System::Drawing::Font(L"Magneto", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(0, 0);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(586, 133);
			this->label1->TabIndex = 1;
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->button3->Font = (gcnew System::Drawing::Font(L"Magneto", 13.8F, System::Drawing::FontStyle::Bold));
			this->button3->Location = System::Drawing::Point(446, 488);
			this->button3->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(105, 57);
			this->button3->TabIndex = 4;
			this->button3->Text = L"Save";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::OnClick2);
			// 
			// label2
			// 
			this->label2->BackColor = System::Drawing::Color::White;
			this->label2->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->label2->Font = (gcnew System::Drawing::Font(L"Magneto", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(0, 547);
			this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(586, 65);
			this->label2->TabIndex = 5;
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->ClientSize = System::Drawing::Size(586, 612);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void OnClick(System::Object^ sender, System::EventArgs^ e) {
		this->openFileDialog1->InitialDirectory = "c:\\";
		this->openFileDialog1->Filter = "wav files (*.wav)|*.wav";
		this->openFileDialog1->FilterIndex = 2;
		this->openFileDialog1->RestoreDirectory = true;
		if (this->openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			FileName = this->openFileDialog1->FileName;
			this->label1->Text = this->openFileDialog1->SafeFileName;
		}	
	}
	private: System::Void OnClick2(System::Object^ sender, System::EventArgs^ e) {
		this->folderBrowserDialog1->Description = "Find folder";
		this->label2->Text = "";
		if (this->folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			this->label2->Text = "Maked";
			SaveRoad = this->folderBrowserDialog1->SelectedPath;
			MakeFiles(FileName, SaveRoad);
			this->label2->Text = "Saved";
		}	
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		System::Drawing::Drawing2D::GraphicsPath^ Button_Path = gcnew System::Drawing::Drawing2D::GraphicsPath();
	}
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}