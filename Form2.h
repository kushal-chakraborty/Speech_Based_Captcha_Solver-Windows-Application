#pragma once
#include "hmm_backend.h"

namespace duplicate{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form2
	/// </summary>
	public ref class Form2 : public System::Windows::Forms::Form
	{
	public:
		String^ username;
	public:
		Form2(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		Form2(String^ SetValueForUserName)
		{
			InitializeComponent();
			username=SetValueForUserName;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form2()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  train;
	private: System::Windows::Forms::TextBox^  textBox1;


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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->train = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::Purple;
			this->label1->Location = System::Drawing::Point(70, 31);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(116, 37);
			this->label1->TabIndex = 0;
			this->label1->Text = L"username";
			this->label1->Click += gcnew System::EventHandler(this, &Form2::label1_Click);
			// 
			// train
			// 
			this->train->Location = System::Drawing::Point(77, 368);
			this->train->Name = L"train";
			this->train->Size = System::Drawing::Size(208, 34);
			this->train->TabIndex = 1;
			this->train->Text = L"Live Training";
			this->train->UseVisualStyleBackColor = true;
			this->train->Click += gcnew System::EventHandler(this, &Form2::train_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(77, 71);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(610, 291);
			this->textBox1->TabIndex = 2;
			// 
			// Form2
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::MediumAquamarine;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(921, 441);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->train);
			this->Controls->Add(this->label1);
			this->Name = L"Form2";
			this->Text = L"Welcome";
			this->Load += gcnew System::EventHandler(this, &Form2::Form2_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Form2_Load(System::Object^  sender, System::EventArgs^  e) {

							this->label1->Text=username;
						
			 }
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {

						//string txt="Welcome ";//+username;
						//String^ str =gcnew String(txt.c_str());
						//this->label1->Text=str;
			 }
	private: System::Void train_Click(System::Object^  sender, System::EventArgs^  e) {

					live_training();
			 }
};
}
