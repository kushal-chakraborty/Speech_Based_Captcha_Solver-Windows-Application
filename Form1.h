
#pragma once
#include "Form2.h"
#include "hmm_backend.h"
//#include "Form2.h"


namespace duplicate {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	//using namespace MySql::Data::MySqlClient;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  Speak;

	private: System::Windows::Forms::Label^  Captcha;
	private: System::Windows::Forms::Button^  ShowCaptcha;


	private: System::Windows::Forms::TextBox^  usr_name_val;
	private: System::Windows::Forms::TextBox^  password_val;


	private: System::Windows::Forms::Label^  user_id;
	private: System::Windows::Forms::Label^  password;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;


	protected: 

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->Speak = (gcnew System::Windows::Forms::Button());
			this->Captcha = (gcnew System::Windows::Forms::Label());
			this->ShowCaptcha = (gcnew System::Windows::Forms::Button());
			this->usr_name_val = (gcnew System::Windows::Forms::TextBox());
			this->password_val = (gcnew System::Windows::Forms::TextBox());
			this->user_id = (gcnew System::Windows::Forms::Label());
			this->password = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// Speak
			// 
			this->Speak->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->Speak->Location = System::Drawing::Point(191, 219);
			this->Speak->Name = L"Speak";
			this->Speak->Size = System::Drawing::Size(124, 27);
			this->Speak->TabIndex = 0;
			this->Speak->Text = L"Speak";
			this->Speak->UseVisualStyleBackColor = true;
			this->Speak->Visible = false;
			this->Speak->Click += gcnew System::EventHandler(this, &Form1::Speak_Click);
			// 
			// Captcha
			// 
			this->Captcha->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->Captcha->AutoSize = true;
			this->Captcha->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Captcha->Location = System::Drawing::Point(223, 182);
			this->Captcha->Name = L"Captcha";
			this->Captcha->Size = System::Drawing::Size(71, 20);
			this->Captcha->TabIndex = 2;
			this->Captcha->Text = L"Captcha";
			this->Captcha->Visible = false;
			// 
			// ShowCaptcha
			// 
			this->ShowCaptcha->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left));
			this->ShowCaptcha->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->ShowCaptcha->FlatAppearance->MouseOverBackColor = System::Drawing::Color::MediumTurquoise;
			this->ShowCaptcha->ForeColor = System::Drawing::Color::Black;
			this->ShowCaptcha->Location = System::Drawing::Point(24, 176);
			this->ShowCaptcha->Name = L"ShowCaptcha";
			this->ShowCaptcha->Size = System::Drawing::Size(122, 28);
			this->ShowCaptcha->TabIndex = 3;
			this->ShowCaptcha->Text = L"Show Captcha";
			this->ShowCaptcha->UseVisualStyleBackColor = true;
			this->ShowCaptcha->Click += gcnew System::EventHandler(this, &Form1::ShowCaptcha_Click);
			// 
			// usr_name_val
			// 
			this->usr_name_val->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->usr_name_val->Location = System::Drawing::Point(160, 67);
			this->usr_name_val->Name = L"usr_name_val";
			this->usr_name_val->Size = System::Drawing::Size(192, 22);
			this->usr_name_val->TabIndex = 4;
			this->usr_name_val->TextChanged += gcnew System::EventHandler(this, &Form1::usr_name_val_TextChanged);
			// 
			// password_val
			// 
			this->password_val->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->password_val->Location = System::Drawing::Point(160, 121);
			this->password_val->Name = L"password_val";
			this->password_val->Size = System::Drawing::Size(192, 22);
			this->password_val->TabIndex = 5;
			// 
			// user_id
			// 
			this->user_id->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left));
			this->user_id->AutoSize = true;
			this->user_id->Font = (gcnew System::Drawing::Font(L"Cambria", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->user_id->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->user_id->Location = System::Drawing::Point(20, 64);
			this->user_id->Name = L"user_id";
			this->user_id->Size = System::Drawing::Size(98, 23);
			this->user_id->TabIndex = 6;
			this->user_id->Text = L"Username";
			// 
			// password
			// 
			this->password->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->password->AutoSize = true;
			this->password->Font = (gcnew System::Drawing::Font(L"Cambria", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->password->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->password->Location = System::Drawing::Point(20, 118);
			this->password->Name = L"password";
			this->password->Size = System::Drawing::Size(94, 23);
			this->password->TabIndex = 7;
			this->password->Text = L"Password";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->label1->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 22, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::MidnightBlue;
			this->label1->Location = System::Drawing::Point(275, 78);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 45);
			this->label1->TabIndex = 8;
			this->label1->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->groupBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->groupBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->groupBox1->Controls->Add(this->password);
			this->groupBox1->Controls->Add(this->user_id);
			this->groupBox1->Controls->Add(this->password_val);
			this->groupBox1->Controls->Add(this->usr_name_val);
			this->groupBox1->Controls->Add(this->ShowCaptcha);
			this->groupBox1->Controls->Add(this->Captcha);
			this->groupBox1->Controls->Add(this->Speak);
			this->groupBox1->Location = System::Drawing::Point(180, 148);
			this->groupBox1->MaximumSize = System::Drawing::Size(381, 266);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(381, 266);
			this->groupBox1->TabIndex = 9;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Sign In";
			this->groupBox1->Enter += gcnew System::EventHandler(this, &Form1::groupBox1_Enter);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(799, 102);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 10;
			this->pictureBox1->TabStop = false;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackColor = System::Drawing::Color::MediumAquamarine;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->ClientSize = System::Drawing::Size(823, 552);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Login";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Speak_Click(System::Object^  sender, System::EventArgs^  e) {

				 this->Refresh();
				 int live = test_with_live_data();
				 this->Captcha->Visible=false;
				 this->Speak->Visible=false;
				 /*
				 this->Hide();
				 string str="Welcome ";
				 String^ str7=gcnew String(str.c_str());
				 str7=str7+this->usr_name_val->Text;
				 Form2^ f2=gcnew Form2(str7);
				 f2->ShowDialog();*/
				 if(result==live){
							/*
							this->Speak->Visible=false;
							this->Captcha->Visible=false;
							this->ShowCaptcha->Visible=false;
							this->usr_name_val->Visible=false;
							this->password_val->Visible=false;
							this->user_id->Visible=false;
							this->password->Visible=false;
							this->label1->Visible=false;
							this->groupBox1->Visible=false;*/
							
							this->Hide();
							string str="Welcome ";
							String^ str7=gcnew String(str.c_str());
							str7=str7+this->usr_name_val->Text;
							Form2^ f2=gcnew Form2(str7);
							f2->ShowDialog();
				 }
				 else{
						MessageBox::Show("Incorrect answer. Please try another captcha");
						this->ShowCaptcha->Visible=true;
				 }
			 }
	private: System::Void ShowCaptcha_Click(System::Object^  sender, System::EventArgs^  e) {

				
				 this->Refresh();
				 int result=generate_captcha();
				 //MessageBox::Show("The string is "+this->ClientSize->Height);
				 this->ShowCaptcha->Visible=false;
				 this->Captcha->Visible=true;
				 String^ str3 = gcnew String(captcha_str.c_str());
				 //result=5;
				 //String^ str4 =gcnew String(to_string((long long)arg1).c_str());
				 //String^ str5 =gcnew String(to_string((long long)arg2).c_str());
				 //String^ str6 =gcnew String(to_string((long long)result).c_str());
				 //String^ str7 =gcnew String(to_string((long long)ch).c_str());
				 //MessageBox::Show(" argumenets are "+str4+" && "+str5+" ---->"+str6);
				 this->Captcha->Text=str3;
				 this->Speak->Visible=true;
			 }
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
				
		 }
private: System::Void usr_name_val_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void groupBox1_Enter(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

