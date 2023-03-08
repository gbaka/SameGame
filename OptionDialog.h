#pragma once


// Диалоговое окно COptionDialog

class COptionDialog : public CDialog
{
	DECLARE_DYNAMIC(COptionDialog)

public:
	COptionDialog(bool bRowColumn, CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~COptionDialog();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OPTIONS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_ctrl_static_text_1;
	CStatic m_ctrl_static_text_2;
	int m_value1;
	int m_value2;
	afx_msg void OnBnClickedButtonDefaults();
	virtual BOOL OnInitDialog();
private:
	// Является ли это диалоговое окно для строки/столбца (true) или для ширины/высоты (false)?
	bool m_bRowColumnDialog;
public:
	afx_msg void OnStnClickedStaticText2();
	afx_msg void OnStnClickedStaticText1();
};
