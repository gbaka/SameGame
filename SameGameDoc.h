// SameGameDoc.h: интерфейс класса CSameGameDoc 
//


#pragma once

#include "CSameGameBoard.h"
#include <stack>


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
		return m_board->GetBoardSpace(p_row, p_col);
	}

	int DeleteBlocks(int row, int col);

	int GetRemainingCount()
	{
		return m_board->GetRemainingCount();
	}

	void SetupBoard()  { m_board->SetupBoard();        }
	int GetWidth()     { return m_board->GetWidth();   }
	int GetHeight()    { return m_board->GetHeight();  }
	int GetCols()      { return m_board->GetCols();    }
	int GetRows()      { return m_board->GetRows();    }

	void SetWidth(int p_width)   { m_board->SetWidth(p_width);   }
	void SetHeight(int p_height) { m_board->SetHeight(p_height); }
	void SetColumns(int p_cols)  { m_board->SetColumns(p_cols);  }
	void SetRows(int p_rows)     { m_board->SetRows(p_rows);     }

	void DeleteBoard() { m_board->DeleteBoard();       }
	bool IsGameOver()  { return m_board->IsGameOver(); }

	void SetNumColors(int p_colors);
	int GetNumColors();

	bool CanRedo();
	bool CanUndo();
	void UndoLast();
	void RedoLast();
	
// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS
protected:
	// Экземпляр класса игровой доски
	CSameGameBoard* m_board;

	// Стек "Отмена"
	std::stack<CSameGameBoard*> m_undo;

	// Стек "Повтор"
	std::stack<CSameGameBoard*> m_redo;
protected:
	// Функции очистки стеков «Отмена/Повтор»
	void ClearUndo();
	void ClearRedo();

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
