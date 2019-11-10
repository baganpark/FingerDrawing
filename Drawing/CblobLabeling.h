#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <opencv2\opencv.hpp>

typedef struct _Visited
{
	bool	bVisitedFlag;
	CvPoint ptReturnPoint;
} Visited;

class  CBlobLabeling
{
public:
	CBlobLabeling(void);
public:
	~CBlobLabeling(void);

public:
	IplImage*	m_Image;				// 레이블링을 위한 이미지
	int			m_nThreshold;			// 레이블링 스레스홀드 값
	Visited*	m_vPoint;				// 레이블링시 방문정보
	int			m_nBlobs;				// 레이블의 갯수
	CvRect*		m_recBlobs;				// 각 레이블 정보
	int*		m_intBlobs;				// 각 레이블 인덱스


public:
	// 레이블링 이미지 선택
	void		SetParam(IplImage* image, int nThreshold);

	// 레이블링(실행)
	void		DoLabeling();

private:
	// 레이블링(동작)
	int		 Labeling(IplImage* image, int nThreshold);

	// 포인트 초기화
	void	 InitvPoint(int nWidth, int nHeight);
	void	 DeletevPoint();

	// 레이블링 결과 얻기
	void	 DetectLabelingRegion(int nLabelNumber, unsigned char *DataBuf, int nWidth, int nHeight);

	// 레이블링(실제 알고리즘)
	int		_Labeling(unsigned char *DataBuf, int nWidth, int nHeight, int nThreshold);
	
	// _Labling 내부 사용 함수
	int		__NRFIndNeighbor(unsigned char *DataBuf, int nWidth, int nHeight, int nPosX, int nPosY, int *StartX, int *StartY, int *EndX, int *EndY );
	int		__Area(unsigned char *DataBuf, int StartX, int StartY, int EndX, int EndY, int nWidth, int nLevel);
	
		
	// 가로, 세로 크기가 비교값보다 작은 레이블이면 제거
public:
	void	BlobSmallSizeConstraint(int nWidth, int nHeight);
private:
	void	_BlobSmallSizeConstraint(int nWidth, int nHeight, CvRect* rect, int *label, int* nRecNumber);

	// 가로, 세로 크기가 비교값보다 큰 레이블이면 제거
public:
	void	BlobBigSizeConstraint(int nWidth, int nHeight);
private:
	void	_BlobBigSizeConstraint(int nWidth, int nHeight, CvRect* rect, int *label, int* nRecNumber);

	
	// 원하는 Blob의 이미지 정보만 가져온다.
public:
	void	GetBlobImage(IplImage *dest, int nLabel);
};

