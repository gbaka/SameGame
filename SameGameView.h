
// SameGameView.h: интерфейс класса CSameGameView
//

#pragma once


class CSameGameView : public CView
{
protected: // создать только из сериализации
	CSameGameView() noexcept;
	DECLARE_DYNCREATE(CSameGameView)

// Атрибуты
public:
	CSameGameDoc* GetDocument() const;
	void setColorCount(int numColors);
	void CSameGameView::checkTheBox(CCmdUI* pCmdUI, int numColor);

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Реализация
public:
	virtual ~CSameGameView();
	void ResizeWindow();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLevel3colors();
	afx_msg void OnUpdateLevel3colors(CCmdUI* pCmdUI);
	afx_msg void OnLevel4colors();
	afx_msg void OnUpdateLevel4colors(CCmdUI* pCmdUI);
	afx_msg void OnLevel5colors();
	afx_msg void OnUpdateLevel5colors(CCmdUI* pCmdUI);
	afx_msg void OnLevel6colors();
	afx_msg void OnUpdateLevel6colors(CCmdUI* pCmdUI);
	afx_msg void OnLevel7colors();
	afx_msg void OnUpdateLevel7colors(CCmdUI* pCmdUI);
	afx_msg void OnSetupBlockcount();
	afx_msg void OnSetupBlocksize();

	// Функции для меню «Отмена/Повтор»
	afx_msg void On32771();
	afx_msg void OnUpdate32771(CCmdUI* pCmdUI);
	// Функции для обновления меню «Отмена/Повтор»
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // версия отладки в SameGameView.cpp
inline CSameGameDoc* CSameGameView::GetDocument() const
   { return reinterpret_cast<CSameGameDoc*>(m_pDocument); }
#endif

