// OptionDialog.cpp: файл реализации
//

#include "pch.h"
#include "SameGame.h"
#include "OptionDialog.h"
#include "afxdialogex.h"


// Диалоговое окно COptionDialog

IMPLEMENT_DYNAMIC(COptionDialog, CDialog)

COptionDialog::COptionDialog(bool bRowColumn, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_OPTIONS, pParent)
	, m_value1(0)
	, m_value2(0)
	, m_bRowColumnDialog(bRowColumn)
{

}

COptionDialog::~COptionDialog()
{
}

void COptionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TEXT_1, m_ctrl_static_text_1);
	DDX_Control(pDX, IDC_STATIC_TEXT_2, m_ctrl_static_text_2);
	DDX_Text(pDX, IDC_EDIT_VALUE_1, m_value1);
	DDX_Text(pDX, IDC_EDIT_VALUE_2, m_value2);
}


BEGIN_MESSAGE_MAP(COptionDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DEFAULTS, &COptionDialog::OnBnClickedButtonDefaults)
	ON_STN_CLICKED(IDC_STATIC_TEXT_2, &COptionDialog::OnStnClickedStaticText2)
	ON_STN_CLICKED(IDC_STATIC_TEXT_1, &COptionDialog::OnStnClickedStaticText1)
END_MESSAGE_MAP()


// Обработчики сообщений COptionDialog


void COptionDialog::OnBnClickedButtonDefaults()
{
	// Отдельно рассматриваем два варианта
	if (m_bRowColumnDialog)
		m_value1 = m_value2 = 15; // размер доски 15x15
	else
		m_value1 = m_value2 = 35; // размер блоков 35x35

	// Обновляем параметры элементов до новых значений
	// прим:
	// Данный аргумент является логическим флагом, 
	// указывающим направление обмена (из переменных в элементы управления или наоборот). 
	UpdateData(false);
}


BOOL COptionDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_bRowColumnDialog)
	{
		// Сначала обновляем заголовок диалогового окна
		SetWindowText(_T("Update Block Count"));

		// Затем обновляем элементы «Static Text»
		m_ctrl_static_text_1.SetWindowText(_T("Строк"));
		m_ctrl_static_text_2.SetWindowText(_T("Столбцов"));
	}
	else
	{
		// Сначала обновляем заголовок диалогового окна
		SetWindowText(_T("Update Block Size"));

		// Затем обновляем элементы «Static Text»
		m_ctrl_static_text_1.SetWindowText(_T("Ширина блока"));
		m_ctrl_static_text_2.SetWindowText(_T("Высота блока"));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // Исключение: страница свойств OCX должна возвращать значение FALSE
}


void COptionDialog::OnStnClickedStaticText2()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void COptionDialog::OnStnClickedStaticText1()
{
	// TODO: добавьте свой код обработчика уведомлений
}
