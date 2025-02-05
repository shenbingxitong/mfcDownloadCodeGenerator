#pragma once
#include <mutex>

#include "FileItem.h"

// CListBoxEx

enum class ProcType
{
	FILE_PROG,
	INC_FILE,
	ERR_FILE
};

typedef void(*f_proc_file_callback) (ProcType type, double progress, CFileItem* pItem, void* extra);
class CListBoxEx : public CListBox
{
	DECLARE_DYNAMIC(CListBoxEx)
private:
	std::mutex mutex;
	static HICON m_hIconTick;
	static CString m_sPlaceholder;
	static HFONT m_systemFont;
	bool m_bStop = false;

public:
	CListBoxEx();
	virtual ~CListBoxEx();

	COLORREF m_bgSelected = RGB(204, 232, 255); // #cce8ff
	COLORREF m_bgClear    = RGB(255, 255, 255);
	COLORREF m_text = RGB(0, 0, 0);
	COLORREF m_textSelected = RGB(0, 0, 0);
	COLORREF m_descText = RGB(109, 109, 109);
	COLORREF m_descTextSelected = RGB(109, 109, 109);

protected:
	DECLARE_MESSAGE_MAP()

public:
	void GetVisibleRange(int& s, int& e);
	bool ItemIsVisible(int nIndex);
	bool RedrawIfVisible(int i);
	void ProcessFiles(f_proc_file_callback cb, void* extra);
	void StopProcessing();

	afx_msg void OnPaint();
	virtual void MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	virtual void PreSubclassWindow();

	void DrawItemData(LPDRAWITEMSTRUCT lpDrawItemStruct, CFileItem* pItem);

	int AddItem(const CString& srcDir, const CString& filename);
	void CopySelectedHashes();
	int VKeyToItem(UINT /*nKey*/, UINT /*nIndex*/);
	virtual INT_PTR OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
	BOOL OnToolTipText(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
};


