
// SameGameDoc.h: интерфейс класса CSameGameDoc 
//


#pragma once

#include "CSameGameBoard.h"


class CSameGameDoc : public CDocument
{
protected: // создать только из сериализации
	CSameGameDoc() noexcept;
	DECLARE_DYNCREATE(CSameGameDoc)

// Атрибуты
public:

// Операции
public:
	// Геттеры для получения информации о параметрах игрового поля
	COLORREF GetBoardSpace(int p_row, int p_col)
	{
		return m_board.GetBoardSpace(p_row, p_col);
	}
	void SetupBoard()  { m_board.SetupBoard();        }
	int GetWidth()     { return m_board.GetWidth();   }
	int GetHeight()    { return m_board.GetHeight();  }
	int GetCols()      { return m_board.GetCols(); }
	int GetRows()      { return m_board.GetRows();    }
	void DeleteBoard() { m_board.DeleteBoard();       }

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS
protected:
	CSameGameBoard m_board;

// Реализация
public:
	virtual ~CSameGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
