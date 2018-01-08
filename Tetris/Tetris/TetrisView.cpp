
// TetrisView.cpp : CTetrisView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Tetris.h"
#endif

#include "TetrisDoc.h"
#include "TetrisView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define TIMERNAME 0
#define ActiveBrickSize 20

#define ShowP1ActiveBrickLoc_Y  350
#define ShowP1ActiveBrickLoc_X  30

#define ShowP2ActiveBrickLoc_Y  350
#define ShowP2ActiveBrickLoc_X  940

#define NUM_BRICK_TYPES 5
#define NUM_TURNS_PER_STEP 5


#define NUM_BRICK_TYPES1 5
#define NUM_TURNS_PER_STEP1 5

#define COLOR_CHANGE 60

// CTetrisView

IMPLEMENT_DYNCREATE(CTetrisView, CView)

BEGIN_MESSAGE_MAP(CTetrisView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_GAME_START, &CTetrisView::OnGameStart)
	ON_COMMAND(ID_DIFF_EASY, &CTetrisView::OnDiffEasy)
	ON_COMMAND(ID_DIFF_MID, &CTetrisView::OnDiffMid)
	ON_COMMAND(ID_DIFF_SUP, &CTetrisView::OnDiffSup)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CTetrisView ����/����

CTetrisView::CTetrisView()
{
	//��ҵ�bin
	bin = new CBin(10+ LocateOfPlayer1Game, 20);
	activeBrick = NULL;
	gameOver = 1;
	brickInFlight = 1;
	brickType = 0;
	initOrientation = 0;
	notCollide = 0;
	numLines = 0;
	difficulty = 500;
	outputImage = new unsigned char*[20];
	for (int i = 0; i<20; i++) 
	{
		outputImage[i] = new unsigned char[LocateOfPlayer1Game+10];
	}
	bin->getImage(outputImage);


	//���1��bin
	bin1 = new CBin(10 + LocateOfPlayer2Game, 20);
	activeBrick1 = NULL;
	gameOver1 = 1;
	brickInFlight1 = 1;
	brickType1 = 0;
	initOrientation1 = 0;
	notCollide1 = 0;
	numLines1 = 0;
	outputImage1 = new unsigned char*[20];
	for (int i = 0; i<20; i++)
	{
		outputImage1[i] = new unsigned char[LocateOfPlayer2Game + 10];
	}
	bin1->getImage(outputImage1);



}

CTetrisView::~CTetrisView()
{
	delete bin;
	delete bin1;
}

BOOL CTetrisView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CTetrisView ����

void CTetrisView::OnDraw(CDC* pDC)
{
	CTetrisDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int m_nWidth, m_nHeight;
	int nWidth, nHeight;
	CRect windowRect;
	GetClientRect(&windowRect);
	nWidth = windowRect.Width();
	nHeight = windowRect.Height();

	CDC MemDC; //���ȶ���һ����ʾ�豸����
	CBitmap MemBitmap;//����һ��λͼ����//���������Ļ��ʾ���ݵ��ڴ���ʾ�豸
	MemDC.CreateCompatibleDC(NULL);//��ʱ�����ܻ�ͼ����Ϊû�еط���
	MemBitmap.CreateCompatibleBitmap(pDC, nWidth, nHeight);//����һ������Ļ��ʾ���ݵ�λͼ������λͼ�Ĵ�С������ô��ڵĴ�С��Ҳ�����Լ�����
	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);//��λͼѡ�뵽�ڴ���ʾ�豸��
													 //ֻ��ѡ����λͼ���ڴ���ʾ�豸���еط���ͼ������ָ����λͼ��
	MemDC.FillSolidRect(0, 0, nWidth, nHeight, RGB(0, 0, 0));//���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ��������Ҳ�������Լ�Ӧ���õ���ɫ

	//����ͼƬ
	CDC TempMemDC;
	CBitmap b1;
	b1.LoadBitmap(IDB_BITMAP3);
	TempMemDC.CreateCompatibleDC(pDC);
	TempMemDC.SelectObject(&b1);// MemDC2��ͼƬ����
	MemDC.BitBlt(0, 0, nWidth, nHeight, &TempMemDC, 0, 0, SRCCOPY);

	//��ʾ���1�ĵ�ǰ����
	ShowActiveBrick(&MemDC);
	//���ƽ���
	DrawImage(bin, outputImage, &MemDC);
	DrawImage(bin1, outputImage1, &MemDC);
	
	pDC->BitBlt(0, 0, nWidth, nHeight, &MemDC, 0, 0, SRCCOPY);//���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ
	MemDC.SelectObject(pOldBit);
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();
}


// CTetrisView ��ӡ

BOOL CTetrisView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CTetrisView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CTetrisView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CTetrisView ���

#ifdef _DEBUG
void CTetrisView::AssertValid() const
{
	CView::AssertValid();
}

void CTetrisView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTetrisDoc* CTetrisView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTetrisDoc)));
	return (CTetrisDoc*)m_pDocument;
}

void CTetrisView::DrawImage(CBin *bin, unsigned char** image, CDC *pDC)
{
	unsigned int width, i, j;
	unsigned int height;
	width = bin->getWidth();
	height = bin->getHeight();
	int nSize = 30;


	CPen pen;
	pen.CreatePen(PS_DASH, 2, RGB(72, 61, 139));
	pDC->SelectObject(&pen);
	pDC->MoveTo(LocateOfPlayer1Game * 30, 0);
	pDC->LineTo(300+LocateOfPlayer1Game * 30, 0);
	pDC->LineTo(300 + LocateOfPlayer1Game * 30, 600);
	pDC->LineTo(LocateOfPlayer1Game * 30, 600);
	pDC->LineTo(LocateOfPlayer1Game * 30, 0);

	pDC->MoveTo(LocateOfPlayer2Game * 30, 0);
	pDC->LineTo(300 + LocateOfPlayer2Game * 30, 0);
	pDC->LineTo(300 + LocateOfPlayer2Game * 30, 600);
	pDC->LineTo(LocateOfPlayer2Game * 30, 600);
	pDC->LineTo(LocateOfPlayer2Game * 30, 0);

	pDC->MoveTo(0, 235);
	pDC->LineTo(LocateOfPlayer1Game * 30, 235);
	pDC->MoveTo(0, 450);
	pDC->LineTo(LocateOfPlayer1Game * 30, 450);


	pDC->MoveTo(900, 250);
	pDC->LineTo(1100, 250);
	pDC->MoveTo(900, 450);
	pDC->LineTo(1100, 450);

	CPen pen1;
	pen1.CreatePen(PS_DASH, 1, RGB(255, 255, 255));
	pDC->SelectObject(&pen1);

	//ȥ������ɫ
	pDC->SetBkMode(TRANSPARENT);
	//����������ɫ
	pDC->SetTextColor(RGB(251, 163, 100));
	char buf[20];
	sprintf_s(buf, "������%d", numLines * 10);
	pDC->TextOut(20, 280, "���1");
	pDC->TextOut(20, 300, buf);
	if (numLines == 2 || numLines == 2 && difficulty > 50)
	{
		difficulty -= 50;
	}

	if (numLines == 4 || numLines == 4 && difficulty > 50)
	{
		difficulty -= 50;
	}

	if (numLines == 8 || numLines == 8 && difficulty > 50)
	{
		difficulty -= 100;
	}

	//ȥ������ɫ
	pDC->SetBkMode(TRANSPARENT);
	//����������ɫ
	pDC->SetTextColor(RGB(251, 163, 100));

	char buf1[20];
	sprintf_s(buf1, "������%d", numLines1 * 10);
	pDC->TextOut(930, 280, "���2");
	pDC->TextOut(930, 300, buf1);

	pDC->TextOut(510, 180, "��Ϸ�Ѷ�");
	if (difficulty > 400)
		pDC->TextOut(530, 200, "��");
	else if(difficulty > 250 && difficulty <= 400)
		pDC->TextOut(530, 200, "�е�");
	else if (difficulty < 100)
		pDC->TextOut(530, 200, "����");

	CRect rc;
	CRect rc1;
	COLORREF BrickColor[8] = {0xFF0000,0x00FF00,0x0000FF, 0x00FFFF, 0xFFFF00, 0x800080, 0xDEB887};
	if (width == 10 + LocateOfPlayer1Game)
	{
		for (i = 0; i < height; i++)
		{
			for (j = LocateOfPlayer1Game; j < width; j++)
			{
				rc = CRect(j*nSize, i*nSize, (j + 1)*nSize, (i + 1)*nSize);
				//�������
				if (image[i][j] != 0)
				{
					pDC->FillRect(rc, &CBrush(BrickColor[image[i][j]]));
					pDC->Draw3dRect(rc, GetLightColor(BrickColor[image[i][j]]), GetDarkColor(BrickColor[image[i][j]]));
				}
			}
		}
	}
	
	else if (width == 10 + LocateOfPlayer2Game)
	{
		for (i = 0; i < height; i++)
		{
			for (j = LocateOfPlayer2Game; j < width; j++)
			{
				rc1 = CRect(j*nSize, i*nSize, (j + 1)*nSize, (i + 1)*nSize);
				//�������
				if (image[i][j] != 0)
				{
					pDC->FillRect(rc1, &CBrush(BrickColor[image[i][j]]));
					pDC->Draw3dRect(rc1, GetLightColor(BrickColor[image[i][j]]), GetDarkColor(BrickColor[image[i][j]]));
				}
			}
		}
	}
}
#endif //_DEBUG


// CTetrisView ��Ϣ�������


void CTetrisView::OnGameStart()
{
	gameOver = 0;
	brickInFlight = 0;
	numLines = 0;
	for (unsigned int i = 0; i<20; i++)
	{
		for (unsigned int j = LocateOfPlayer1Game; j<LocateOfPlayer1Game +10; j++)
			outputImage[i][j] = 0;
	}
	bin->setImage(outputImage);

	gameOver1 = 0;
	brickInFlight1 = 0;
	numLines1 = 0;
	for (unsigned int i = 0; i<20; i++)
	{
		for (unsigned int j = LocateOfPlayer2Game; j<LocateOfPlayer2Game + 10; j++)
			outputImage1[i][j] = 0;
	}
	bin1->setImage(outputImage1);
	SetTimer(TIMERNAME, difficulty, NULL);
	// TODO: �ڴ���������������
}


void CTetrisView::OnDiffEasy()
{
	difficulty = 450;
	OnGameStart();
	// TODO: �ڴ���������������
}


void CTetrisView::OnDiffMid()
{
	difficulty = 350;
	OnGameStart();
	// TODO: �ڴ���������������
}


void CTetrisView::OnDiffSup()
{
	difficulty = 50;
	OnGameStart();
	// TODO: �ڴ���������������
}

void CTetrisView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	unsigned int binWidth, binHeight;
	unsigned int i = 0;
	unsigned int j = 0;
	CDC *pDC = GetDC();
	binWidth = bin->getWidth();
	binHeight = bin->getHeight();
	// start the game
	if (!brickInFlight&&!gameOver)
	{
		//brickType = (rand() % NUM_BRICK_TYPES) + 1;
		//initOrientation = (unsigned int)(rand() % 5);
		//��ֹ rand ����ÿ�����н��һ��
		 CTime time=CTime::GetCurrentTime();
		int q=int(time.GetSecond());
		brickType = ((q+1) % NUM_BRICK_TYPES)+ 1;
		//initOrientation = (unsigned int) (q % 4);
		if (brickType == 1)
			activeBrick = new CIBrick;
		else if (brickType == 2)
			activeBrick = new CLBrick;
		else if (brickType == 3)
			activeBrick = new CSBrick;
		else if (brickType == 4)
			activeBrick = new COBrick;
		else if (brickType == 5)
			activeBrick = new CTBrick;
		activeBrick->setColour((unsigned char)brickType);
		activeBrick->putAtTop(initOrientation, (binWidth + LocateOfPlayer1Game) / 2);
		notCollide = activeBrick->checkCollision(bin);
		if (notCollide)
		{
			brickInFlight = 1;
				bin->getImage(outputImage);
			activeBrick->operator>>(outputImage);
			Invalidate(FALSE);
		}
		else
		{ //�������
			gameOver = 1;
			delete activeBrick;
			brickInFlight = 0;
		}
	}
	if (brickInFlight&&!gameOver)
	{
		notCollide = activeBrick->shiftDown(bin);
		if (notCollide)
		{
			bin->getImage(outputImage);
			activeBrick->operator>>(outputImage);
		}
		else
		{
			brickInFlight = 0;
			bin->getImage(outputImage);
			activeBrick->operator>>(outputImage);
			bin->setImage(outputImage);
			Invalidate(FALSE);
			numLines = numLines + bin->removeFullLines();
			bin->getImage(outputImage);
		}
		Invalidate(FALSE);
	}
	if (gameOver) 
	{
		KillTimer(TIMERNAME);
			if (MessageBox(_T("                   ���2ʤ��! \n\n   �Ƿ����¿�ʼ��Ϸ\n\n"), _T("��Ϸ����"), MB_YESNO) == IDYES)
				OnGameStart();
			else
			{
				PostQuitMessage(0);
				//�����ַ����������˳�����
				//exit(0);
				
			}
	}
///////////////////////////////////////////////////////////////////
/////////////���1��//////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
	unsigned int bin1Width, bin1Height;
	bin1Width = bin1->getWidth();
	bin1Height = bin1->getHeight();

	// start the game
	if (!brickInFlight1&&!gameOver1)
	{
		//brickType1 = (rand() % NUM_BRICK_TYPES1) + 1;
		//initOrientation1 = (unsigned int)(rand() % 4);
		//��ֹ rand ����ÿ�����н��һ��
		CTime time1 = CTime::GetCurrentTime();
		int q1 = int(time1.GetSecond());
		brickType1 = (q1 % NUM_BRICK_TYPES) + 1;
	//	initOrientation1 = (unsigned int) (q1 % 4);
		if (brickType1 == 1)
			activeBrick1 = new CIBrick;
		else if (brickType1 == 2)
			activeBrick1 = new CLBrick;
		else if (brickType1 == 3)
			activeBrick1 = new CSBrick;
		else if (brickType1 == 4)
			activeBrick1 = new COBrick;
		else if (brickType1 == 5)
			activeBrick1 = new CTBrick;

		activeBrick1->setColour((unsigned char)brickType1);
		activeBrick1->putAtTop(initOrientation1, (bin1Width + LocateOfPlayer2Game) / 2);
		notCollide1 = activeBrick1->checkCollision(bin1);

		if (notCollide1)
		{
			brickInFlight1 = 1;
			bin1->getImage(outputImage1);
			activeBrick1->operator>>(outputImage1);
			Invalidate(FALSE);
		}
		else
		{ //�������
			gameOver1 = 1;
			delete activeBrick1;
			brickInFlight1 = 0;
		}
	}
	if (brickInFlight1&&!gameOver1)
	{
		notCollide1 = activeBrick1->shiftDown(bin1);
		if (notCollide1)
		{
			bin1->getImage(outputImage1);
			activeBrick1->operator>>(outputImage1);
		}
		else
		{
			brickInFlight1 = 0;
			bin1->getImage(outputImage1);
			activeBrick1->operator>>(outputImage1);
			bin1->setImage(outputImage1);
			Invalidate(FALSE);
			numLines1 = numLines1 + bin1->removeFullLines();
			bin1->getImage(outputImage1);
		}
		Invalidate(FALSE);
	}
	if (gameOver1)
	{
		KillTimer(TIMERNAME);
		if (MessageBox(_T("                    ��� 1 ʤ��! \n\n�Ƿ����¿�ʼ��Ϸ��\n\n"), _T("��Ϸ����"), MB_YESNO) == IDYES)
			OnGameStart();
		else
		{
			exit(0);
			//�����ַ����������˳�����
		}
			
	}
	CView::OnTimer(nIDEvent);
}


void CTetrisView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nChar == VK_RIGHT)
		activeBrick1->shiftRight(bin1);
	else if (nChar == VK_LEFT)
		activeBrick1->shiftLeft(bin1);
	else if (nChar == VK_UP)
		activeBrick1->rotateClockwise(bin1);
	else if (nChar == VK_DOWN)
		activeBrick1->shiftDown(bin1);


	else if (nChar == 68)
		activeBrick->shiftRight(bin);
	else if (nChar == 65)
		activeBrick->shiftLeft(bin);
	else if (nChar == 87)
		activeBrick->rotateClockwise(bin);
	else if (nChar == 83)
		activeBrick->shiftDown(bin);
	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

COLORREF CTetrisView::GetLightColor(COLORREF m_crBody)
{
	BYTE r = GetRValue(m_crBody);
	BYTE g = GetGValue(m_crBody);
	BYTE b = GetBValue(m_crBody);
	r = r + COLOR_CHANGE>255 ? 255 : r + COLOR_CHANGE;
	g = g + COLOR_CHANGE>255 ? 255 : g + COLOR_CHANGE;
	b = b + COLOR_CHANGE>255 ? 255 : b + COLOR_CHANGE;
	return RGB(r, g, b);
}


COLORREF CTetrisView::GetDarkColor(COLORREF m_crBody)
{
	BYTE r = GetRValue(m_crBody);
	BYTE g = GetGValue(m_crBody);
	BYTE b = GetBValue(m_crBody);
	r = r - COLOR_CHANGE<0 ? 0 : r - COLOR_CHANGE;
	g = g - COLOR_CHANGE<0 ? 0 : g - COLOR_CHANGE;
	b = b - COLOR_CHANGE<0 ? 0 : b - COLOR_CHANGE;
	return RGB(r, g, b);
}

//��ʾ��ǰ״̬����
void CTetrisView::ShowActiveBrick(CDC* dc)
{
	if (brickType == 1)
	{
		CBrush pNewBrush(RGB(0, 255, 0));
		CBrush *pOldBrush = dc->SelectObject(&pNewBrush);
		dc->Rectangle(ShowP1ActiveBrickLoc_X, ShowP1ActiveBrickLoc_Y, ShowP1ActiveBrickLoc_X + ActiveBrickSize, ShowP1ActiveBrickLoc_Y + ActiveBrickSize);
		dc->Rectangle(ShowP1ActiveBrickLoc_X, ShowP1ActiveBrickLoc_Y + ActiveBrickSize, ShowP1ActiveBrickLoc_X + ActiveBrickSize, ShowP1ActiveBrickLoc_Y + ActiveBrickSize * 2);
		dc->Rectangle(ShowP1ActiveBrickLoc_X, ShowP1ActiveBrickLoc_Y + ActiveBrickSize * 2, ShowP1ActiveBrickLoc_X + ActiveBrickSize, ShowP1ActiveBrickLoc_Y + ActiveBrickSize * 3);
		dc->Rectangle(ShowP1ActiveBrickLoc_X, ShowP1ActiveBrickLoc_Y + ActiveBrickSize * 3, ShowP1ActiveBrickLoc_X + ActiveBrickSize, ShowP1ActiveBrickLoc_Y + ActiveBrickSize * 4);
		dc->SelectObject(pOldBrush);
	}
	else if (brickType == 2)
	{
		CBrush pNewBrush(RGB(255, 0, 0));
		CBrush *pOldBrush = dc->SelectObject(&pNewBrush);
		dc->Rectangle(ShowP1ActiveBrickLoc_X, ShowP1ActiveBrickLoc_Y, ShowP1ActiveBrickLoc_X + ActiveBrickSize, ShowP1ActiveBrickLoc_Y + ActiveBrickSize);
		dc->Rectangle(ShowP1ActiveBrickLoc_X, ShowP1ActiveBrickLoc_Y + ActiveBrickSize, ShowP1ActiveBrickLoc_X + ActiveBrickSize, ShowP1ActiveBrickLoc_Y + ActiveBrickSize * 2);
		dc->Rectangle(ShowP1ActiveBrickLoc_X, ShowP1ActiveBrickLoc_Y + ActiveBrickSize * 2, ShowP1ActiveBrickLoc_X + ActiveBrickSize, ShowP1ActiveBrickLoc_Y + ActiveBrickSize * 3);
		dc->Rectangle(ShowP1ActiveBrickLoc_X + ActiveBrickSize, ShowP1ActiveBrickLoc_Y + ActiveBrickSize * 2, ShowP1ActiveBrickLoc_X + ActiveBrickSize * 2, ShowP1ActiveBrickLoc_Y + ActiveBrickSize * 3);
		dc->SelectObject(pOldBrush);
	}
	else if (brickType == 3)
	{
		CBrush pNewBrush(RGB(255, 255, 0));
		CBrush *pOldBrush = dc->SelectObject(&pNewBrush);
		dc->Rectangle(ShowP1ActiveBrickLoc_X, ShowP1ActiveBrickLoc_Y, ShowP1ActiveBrickLoc_X + ActiveBrickSize, ShowP1ActiveBrickLoc_Y + ActiveBrickSize);
		dc->Rectangle(ShowP1ActiveBrickLoc_X, ShowP1ActiveBrickLoc_Y + ActiveBrickSize, ShowP1ActiveBrickLoc_X + ActiveBrickSize, ShowP1ActiveBrickLoc_Y + ActiveBrickSize * 2);
		dc->Rectangle(ShowP1ActiveBrickLoc_X + ActiveBrickSize, ShowP1ActiveBrickLoc_Y + ActiveBrickSize, ShowP1ActiveBrickLoc_X + ActiveBrickSize * 2, ShowP1ActiveBrickLoc_Y + ActiveBrickSize * 2);
		dc->Rectangle(ShowP1ActiveBrickLoc_X + ActiveBrickSize, ShowP1ActiveBrickLoc_Y + ActiveBrickSize * 2, ShowP1ActiveBrickLoc_X + ActiveBrickSize * 2, ShowP1ActiveBrickLoc_Y + ActiveBrickSize * 3);
		dc->SelectObject(pOldBrush);
	}
	else if (brickType == 4)
	{
		CBrush pNewBrush(RGB(0, 255, 255));
		CBrush *pOldBrush = dc->SelectObject(&pNewBrush);
		dc->Rectangle(ShowP1ActiveBrickLoc_X, ShowP1ActiveBrickLoc_Y, ShowP1ActiveBrickLoc_X + ActiveBrickSize, ShowP1ActiveBrickLoc_Y + ActiveBrickSize);
		dc->Rectangle(ShowP1ActiveBrickLoc_X, ShowP1ActiveBrickLoc_Y + ActiveBrickSize, ShowP1ActiveBrickLoc_X + ActiveBrickSize, ShowP1ActiveBrickLoc_Y + ActiveBrickSize * 2);
		dc->Rectangle(ShowP1ActiveBrickLoc_X + ActiveBrickSize, ShowP1ActiveBrickLoc_Y + ActiveBrickSize, ShowP1ActiveBrickLoc_X + ActiveBrickSize * 2, ShowP1ActiveBrickLoc_Y + ActiveBrickSize * 2);
		dc->Rectangle(ShowP1ActiveBrickLoc_X + ActiveBrickSize, ShowP1ActiveBrickLoc_Y, ShowP1ActiveBrickLoc_X + ActiveBrickSize * 2, ShowP1ActiveBrickLoc_Y + ActiveBrickSize);
		dc->SelectObject(pOldBrush);
	}
	else if (brickType == 5)
	{
		CBrush pNewBrush(RGB(128, 0, 128));
		CBrush *pOldBrush = dc->SelectObject(&pNewBrush);
		dc->Rectangle(ShowP1ActiveBrickLoc_X, ShowP1ActiveBrickLoc_Y, ShowP1ActiveBrickLoc_X + ActiveBrickSize, ShowP1ActiveBrickLoc_Y + ActiveBrickSize);
		dc->Rectangle(ShowP1ActiveBrickLoc_X, ShowP1ActiveBrickLoc_Y + ActiveBrickSize, ShowP1ActiveBrickLoc_X + ActiveBrickSize, ShowP1ActiveBrickLoc_Y + ActiveBrickSize * 2);
		dc->Rectangle(ShowP1ActiveBrickLoc_X + ActiveBrickSize, ShowP1ActiveBrickLoc_Y + ActiveBrickSize, ShowP1ActiveBrickLoc_X + ActiveBrickSize * 2, ShowP1ActiveBrickLoc_Y + ActiveBrickSize * 2);
		dc->Rectangle(ShowP1ActiveBrickLoc_X - ActiveBrickSize, ShowP1ActiveBrickLoc_Y + ActiveBrickSize, ShowP1ActiveBrickLoc_X, ShowP1ActiveBrickLoc_Y + ActiveBrickSize * 2);
		dc->SelectObject(pOldBrush);
	}

	//��ʾ���2�ĵ�ǰ����
	if (brickType1 == 1)
	{
		CBrush pNewBrush(RGB(0, 255, 0));
		CBrush *pOldBrush = dc->SelectObject(&pNewBrush);
		dc->Rectangle(ShowP2ActiveBrickLoc_X, ShowP2ActiveBrickLoc_Y, ShowP2ActiveBrickLoc_X + ActiveBrickSize, ShowP2ActiveBrickLoc_Y + ActiveBrickSize);
		dc->Rectangle(ShowP2ActiveBrickLoc_X, ShowP2ActiveBrickLoc_Y + ActiveBrickSize, ShowP2ActiveBrickLoc_X + ActiveBrickSize, ShowP2ActiveBrickLoc_Y + ActiveBrickSize * 2);
		dc->Rectangle(ShowP2ActiveBrickLoc_X, ShowP2ActiveBrickLoc_Y + ActiveBrickSize * 2, ShowP2ActiveBrickLoc_X + ActiveBrickSize, ShowP2ActiveBrickLoc_Y + ActiveBrickSize * 3);
		dc->Rectangle(ShowP2ActiveBrickLoc_X, ShowP2ActiveBrickLoc_Y + ActiveBrickSize * 3, ShowP2ActiveBrickLoc_X + ActiveBrickSize, ShowP2ActiveBrickLoc_Y + ActiveBrickSize * 4);
		dc->SelectObject(pOldBrush);
	}
	else if (brickType1 == 2)
	{
		CBrush pNewBrush(RGB(255, 0, 0));
		CBrush *pOldBrush = dc->SelectObject(&pNewBrush);
		dc->Rectangle(ShowP2ActiveBrickLoc_X, ShowP2ActiveBrickLoc_Y, ShowP2ActiveBrickLoc_X + ActiveBrickSize, ShowP2ActiveBrickLoc_Y + ActiveBrickSize);
		dc->Rectangle(ShowP2ActiveBrickLoc_X, ShowP2ActiveBrickLoc_Y + ActiveBrickSize, ShowP2ActiveBrickLoc_X + ActiveBrickSize, ShowP2ActiveBrickLoc_Y + ActiveBrickSize * 2);
		dc->Rectangle(ShowP2ActiveBrickLoc_X, ShowP2ActiveBrickLoc_Y + ActiveBrickSize * 2, ShowP2ActiveBrickLoc_X + ActiveBrickSize, ShowP2ActiveBrickLoc_Y + ActiveBrickSize * 3);
		dc->Rectangle(ShowP2ActiveBrickLoc_X + ActiveBrickSize, ShowP2ActiveBrickLoc_Y + ActiveBrickSize * 2, ShowP2ActiveBrickLoc_X + ActiveBrickSize * 2, ShowP2ActiveBrickLoc_Y + ActiveBrickSize * 3);
		dc->SelectObject(pOldBrush);
	}
	else if (brickType1 == 3)
	{
		CBrush pNewBrush(RGB(255, 255, 0));
		CBrush *pOldBrush = dc->SelectObject(&pNewBrush);
		dc->Rectangle(ShowP2ActiveBrickLoc_X, ShowP2ActiveBrickLoc_Y, ShowP2ActiveBrickLoc_X + ActiveBrickSize, ShowP2ActiveBrickLoc_Y + ActiveBrickSize);
		dc->Rectangle(ShowP2ActiveBrickLoc_X, ShowP2ActiveBrickLoc_Y + ActiveBrickSize, ShowP2ActiveBrickLoc_X + ActiveBrickSize, ShowP2ActiveBrickLoc_Y + ActiveBrickSize * 2);
		dc->Rectangle(ShowP2ActiveBrickLoc_X + ActiveBrickSize, ShowP2ActiveBrickLoc_Y + ActiveBrickSize, ShowP2ActiveBrickLoc_X + ActiveBrickSize * 2, ShowP2ActiveBrickLoc_Y + ActiveBrickSize * 2);
		dc->Rectangle(ShowP2ActiveBrickLoc_X + ActiveBrickSize, ShowP2ActiveBrickLoc_Y + ActiveBrickSize * 2, ShowP2ActiveBrickLoc_X + ActiveBrickSize * 2, ShowP2ActiveBrickLoc_Y + ActiveBrickSize * 3);
		dc->SelectObject(pOldBrush);
	}
	else if (brickType1 == 4)
	{
		CBrush pNewBrush(RGB(0, 255, 255));
		CBrush *pOldBrush = dc->SelectObject(&pNewBrush);
		dc->Rectangle(ShowP2ActiveBrickLoc_X, ShowP2ActiveBrickLoc_Y, ShowP2ActiveBrickLoc_X + ActiveBrickSize, ShowP2ActiveBrickLoc_Y + ActiveBrickSize);
		dc->Rectangle(ShowP2ActiveBrickLoc_X, ShowP2ActiveBrickLoc_Y + ActiveBrickSize, ShowP2ActiveBrickLoc_X + ActiveBrickSize, ShowP2ActiveBrickLoc_Y + ActiveBrickSize * 2);
		dc->Rectangle(ShowP2ActiveBrickLoc_X + ActiveBrickSize, ShowP2ActiveBrickLoc_Y + ActiveBrickSize, ShowP2ActiveBrickLoc_X + ActiveBrickSize * 2, ShowP2ActiveBrickLoc_Y + ActiveBrickSize * 2);
		dc->Rectangle(ShowP2ActiveBrickLoc_X + ActiveBrickSize, ShowP2ActiveBrickLoc_Y, ShowP2ActiveBrickLoc_X + ActiveBrickSize * 2, ShowP2ActiveBrickLoc_Y + ActiveBrickSize);
		dc->SelectObject(pOldBrush);
	}
	else if (brickType1 == 5)
	{
		CBrush pNewBrush(RGB(128, 0, 128));
		CBrush *pOldBrush = dc->SelectObject(&pNewBrush);
		dc->Rectangle(ShowP2ActiveBrickLoc_X, ShowP2ActiveBrickLoc_Y, ShowP2ActiveBrickLoc_X + ActiveBrickSize, ShowP2ActiveBrickLoc_Y + ActiveBrickSize);
		dc->Rectangle(ShowP2ActiveBrickLoc_X, ShowP2ActiveBrickLoc_Y + ActiveBrickSize, ShowP2ActiveBrickLoc_X + ActiveBrickSize, ShowP2ActiveBrickLoc_Y + ActiveBrickSize * 2);
		dc->Rectangle(ShowP2ActiveBrickLoc_X + ActiveBrickSize, ShowP2ActiveBrickLoc_Y + ActiveBrickSize, ShowP2ActiveBrickLoc_X + ActiveBrickSize * 2, ShowP2ActiveBrickLoc_Y + ActiveBrickSize * 2);
		dc->Rectangle(ShowP2ActiveBrickLoc_X - ActiveBrickSize, ShowP2ActiveBrickLoc_Y + ActiveBrickSize, ShowP2ActiveBrickLoc_X, ShowP2ActiveBrickLoc_Y + ActiveBrickSize * 2);
		dc->SelectObject(pOldBrush);
	}
}