#include "StdAfx.h"
#include "CreatePATPacket.h"

CCreatePATPacket::CCreatePATPacket(void)
{
	this->version = 0;
	this->counter = 0;

	this->packetSize = 0;
	this->packet = NULL;

	this->PSISize = 0;
	this->PSI = NULL;
}

CCreatePATPacket::~CCreatePATPacket(void)
{
	SAFE_DELETE_ARRAY(this->packet);
	SAFE_DELETE_ARRAY(this->PSI);
}

//作成PATのパラメータを設定
//引数：
// TSID				[IN]TransportStreamID
// PIDMap			[IN]PMTのリスト
void CCreatePATPacket::SetParam(
	WORD TSID,
	map<WORD, PROGRAM_PID_INFO>* PIDMap
)
{
	//変更なければ変える必要なし
	if( this->TSID == TSID && this->PIDMap.size() == PIDMap->size() ){
		if( this->PIDMap.size() != 0 ){
			BOOL bChg = FALSE;
			map<WORD, PROGRAM_PID_INFO>::iterator itr1;
			map<WORD, PROGRAM_PID_INFO>::iterator itr2;
			for( itr1 = this->PIDMap.begin(); itr1 != this->PIDMap.end(); itr1++ ){
				itr2 = PIDMap->find(itr1->first);
				if( itr2 == PIDMap->end() ){
					bChg = TRUE;
					break;
				}else{
					if( itr1->second.PMTPID != itr2->second.PMTPID ||
					itr1->second.SID != itr2->second.SID ){
						bChg = TRUE;
						break;
					}
				}
			}
			if( bChg == FALSE ){
				return ;
			}
		}
	}
	this->TSID = TSID;
	this->PIDMap = *PIDMap;

	this->version++;
	if( this->version > 31 ){
		this->version = 0;
	}

	CreatePAT();
}

//作成PATのバッファポインタを取得
//戻り値：作成PATのバッファポインタ
BOOL CCreatePATPacket::GetPacket(
	BYTE** pbBuff,				//[OUT] 作成したPATパケットへのポインタ（次回呼び出し時まで有効）
	DWORD* pdwSize,				//[OUT] pbBuffのサイズ
	BOOL incrementFlag			//[IN] TSパケットのCounterをインクリメントするかどうか（TRUE:する、FALSE：しない）
)
{
	if( incrementFlag == TRUE ){
		IncrementCounter();
	}
	if( this->packet != NULL ){
		*pbBuff = this->packet;
		*pdwSize = (DWORD)this->packetSize;
	}else{
		return FALSE;
	}
	return TRUE;
}

//作成PATのバッファをクリア
void CCreatePATPacket::Clear()
{
	this->packetSize = 0;
	SAFE_DELETE_ARRAY(this->packet);
	this->PSISize = 0;
	SAFE_DELETE_ARRAY(this->PSI);
}

void CCreatePATPacket::CreatePAT()
{
	this->PSISize = 0;
	SAFE_DELETE_ARRAY(this->PSI);

	//まずPSI作成
	//pointer_field + last_section_numberまで+PID+CRCのサイズ
	this->PSISize = 1 + 8 + (int)this->PIDMap.size()*4 + 4;
	this->PSI = new BYTE[this->PSISize];
	memset( this->PSI, 0xFF, this->PSISize );

	this->PSI[0] = 0;
	this->PSI[1] = 0;
	this->PSI[2] = (BYTE)(((this->PSISize-4)&0x00000F00)>>8);
	this->PSI[2] |= 0xB0; 
	this->PSI[3] = (BYTE)((this->PSISize-4)&0x000000FF);
	this->PSI[4] = (BYTE)((this->TSID&0xFF00)>>8);
	this->PSI[5] = (BYTE)(this->TSID&0x00FF);
	this->PSI[6] = this->version<<1;
	this->PSI[6] |= 0xC1;
	this->PSI[7] = 0;
	this->PSI[8] = 0;

	DWORD dwCreateSize = 0;
	map<WORD, PROGRAM_PID_INFO>::iterator itr;
	for( itr = this->PIDMap.begin(); itr != this->PIDMap.end(); itr++ ){
		this->PSI[9+dwCreateSize] = (BYTE)((itr->second.SID&0xFF00)>>8);
		this->PSI[9+dwCreateSize+1] = (BYTE)(itr->second.SID&0x00FF);
		this->PSI[9+dwCreateSize+2] = (BYTE)((itr->second.PMTPID&0xFF00)>>8);
		this->PSI[9+dwCreateSize+3] = (BYTE)(itr->second.PMTPID&0x00FF);
		dwCreateSize+=4;
	}

	unsigned long ulCrc = _Crc32(8+dwCreateSize,this->PSI+1);
	this->PSI[this->PSISize-4] = (BYTE)((ulCrc&0xFF000000)>>24);
	this->PSI[this->PSISize-3] = (BYTE)((ulCrc&0x00FF0000)>>16);
	this->PSI[this->PSISize-2] = (BYTE)((ulCrc&0x0000FF00)>>8);
	this->PSI[this->PSISize-1] = (BYTE)(ulCrc&0x000000FF);

	CreatePacket();
}

void CCreatePATPacket::CreatePacket()
{
	this->packetSize = 0;
	SAFE_DELETE_ARRAY(this->packet);

	//TSパケットを作成
	int iPacketNum = (this->PSISize/184) + 1;
	this->packetSize = 188*iPacketNum;

	this->packet = new BYTE[this->packetSize];
	memset(this->packet, 0xFF, this->packetSize);

	for( int i = 0 ; i<iPacketNum; i++ ){
		DWORD dwHead = 0x10000047;
		if( i==0 ){
			//payload_unit_start_indicator
			dwHead |= 0x00006000;
		}

		memcpy(this->packet + 188*i, &dwHead, 4 );
		if( 184*(i+1) <= this->PSISize ){
			memcpy(this->packet + (188*i) + 4, this->PSI + (184*i), 184);
		}else{
			memcpy(this->packet + (188*i) + 4, this->PSI + (184*i), this->PSISize-(184*i));
		}
	}
}

void CCreatePATPacket::IncrementCounter()
{
	if( this->packet == NULL ){
		return ;
	}

	for( int i = 0 ; i<this->packetSize; i+=188 ){
		this->packet[i+3] = (BYTE)(this->counter | 0x10);
		this->counter++;
		if( this->counter >= 16 ){
			this->counter = 0;
		}
	}
}
