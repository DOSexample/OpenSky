
#pragma once
#include <tchar.h>
using namespace std;

typedef struct _OBJECT_SCALE_INFO
{
	FLOAT fRateX;
	FLOAT fRateY;
	FLOAT fRateZ;

	_OBJECT_SCALE_INFO()
		:fRateX(1.0f)
		,fRateY(1.0f)
		,fRateZ(1.0f)
	{
	}
}OBJECT_SCALE_INFO;

typedef OBJECT_SCALE_INFO* LPOBJECT_SCALE_INFO;

typedef std::map<WORD , OBJECT_SCALE_INFO> GXD_OBJECT_SCALE_IN_WORLD;

class CWorldMobjectScale
{
public:
	CWorldMobjectScale(void);
	~CWorldMobjectScale(void);

private:
	GXD_OBJECT_SCALE_IN_WORLD	m_mapScaleData;
	OBJECT_SCALE_INFO				m_LastScaleRate;
	BOOL										m_bIsUsed;

private:
	BOOL ReadData(HANDLE hFile , LPVOID pBuffer , const DWORD dwReadSize );
	BOOL SaveData(HANDLE hFile , const LPVOID pBuffer , const DWORD dwWriteSize );
	
public:
	BOOL Initalize(const WORD wObjectNum);
	VOID Release();

	BOOL Load(const WORD wOBjectNum , std::string strLoadFilePath);
	BOOL Save(std::string strSaveFilePath);

public:
	BOOL SetOBjectSacle(WORD wIndex , FLOAT fScaleX , FLOAT fScaleY , FLOAT fScaleZ);
	BOOL InsertOBjectSacle( WORD wIndex, FLOAT fScaleX = 1.0f , FLOAT fScaleY= 1.0f , FLOAT fScaleZ= 1.0f);

public:
	const FLOAT GetScaleRateX(WORD wIndex);
	const FLOAT GetScaleRateY(WORD wIndex);
	const FLOAT GetScaleRateZ(WORD wIndex);

	
	const FLOAT GetLastScaleRateX(){return m_LastScaleRate.fRateX;}
	const FLOAT GetLastScaleRateY(){return m_LastScaleRate.fRateY;}
	const FLOAT GetLastScaleRateZ(){return m_LastScaleRate.fRateZ;}


	VOID  ClearLastScaleRate()
	{
		m_LastScaleRate.fRateX = 1.0f;
		m_LastScaleRate.fRateY = 1.0f;
		m_LastScaleRate.fRateZ = 1.0f;
	}

	BOOL GetUsed(){return m_bIsUsed;}
};
