#include"MyForm.h"
[System::STAThread]
int WinMain() {
	System::Windows::Forms::Application::Run(gcnew File::MyForm);
	return 0;
}