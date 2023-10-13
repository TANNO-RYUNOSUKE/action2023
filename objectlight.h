//================================
//ライトヘッダ
//================================
#include "main.h"
#include "object.h"

#ifndef _ObjectLight_H_
#define _ObjectLight_H_



class CObjectLight : public CObject
{
public:
	CObjectLight();
	~CObjectLight();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static	CObjectLight * Create(D3DLIGHTTYPE type, D3DXCOLOR Diffuse, D3DXVECTOR3 pos, float fRange);
	D3DLIGHT9 *GetLight(void) { return m_pLight; }
	
private:
	D3DLIGHT9 * m_pLight;
	int m_nID;
};


#endif // !_ObjectLight_H_

