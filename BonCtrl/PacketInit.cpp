#include "StdAfx.h"
#include "PacketInit.h"

CPacketInit::CPacketInit(void)
{
	this->nextStartSize = 0;
	this->nextStartBuff = new BYTE[256];
	this->TSMode = TS_188;
	this->lastOffset = 0;

	this->copyBuff = NULL;
	this->copyBuffSize = 0;
}

CPacketInit::~CPacketInit(void)
{
	SAFE_DELETE_ARRAY(this->nextStartBuff);
	SAFE_DELETE_ARRAY(this->copyBuff);
}

void CPacketInit::ClearBuff()
{
	this->nextStartSize = 0;
	this->TSMode = TS_188;
	this->lastOffset = 0;
}

//入力バッファを188バイト単位のTSにするoffset位置と1パケットのサイズを取得する
//戻り値：
// TRUE（成功）、FALSE（失敗）
//引数：
// data				[IN]入力TSデータ
// size				[IN]dataのサイズ（BYTE単位）
// offset			[OUT]nextStartBuffの先頭を0とした開始オフセット位置
// packetSize		[OUT]1パケットのサイズ
BOOL CPacketInit::CheckSync(
	BYTE* data,
	DWORD size,
	DWORD* offset,
	DWORD* packetSize
)
{
	DWORD maxCheckSize = 204;
	if( this->nextStartSize + size < 204 ){
		maxCheckSize = this->nextStartSize + size;
	}
	//188バイト単位かチェック
	for( DWORD pos = 0; pos<maxCheckSize; pos++ ){
		if( pos < this->nextStartSize ){
			//前回の残りチェック
			if( this->nextStartBuff[pos] == 0x47 ){
				BOOL AllOK = TRUE;
				for( DWORD j=pos; j<this->nextStartSize + size; j+=188 ){
					//前回の残りチェック
					if( j < this->nextStartSize ){
						if( this->nextStartBuff[j] != 0x47 ){
							AllOK = FALSE;
							break;
						}
					}else{
						if( data[j-this->nextStartSize] != 0x47 ){
							AllOK = FALSE;
							break;
						}
					}
				}
				if( AllOK == TRUE ){
					*offset = pos;
					*packetSize = 188;
					return TRUE;
				}
			}
		}else{
			//今回のデータ部分
			if( data[pos-this->nextStartSize] == 0x47 ){
				BOOL AllOK = TRUE;
				for( DWORD j=pos; j<this->nextStartSize + size; j+=188 ){
					if( data[j-this->nextStartSize] != 0x47 ){
						AllOK = FALSE;
						break;
					}
				}
				if( AllOK == TRUE ){
					*offset = pos;
					*packetSize = 188;
					return TRUE;
				}
			}
		}
	}
	//192バイト単位かチェック
	for( DWORD pos = 0; pos<maxCheckSize; pos++ ){
		if( pos < this->nextStartSize ){
			//前回の残りチェック
			if( this->nextStartBuff[pos] == 0x47 ){
				BOOL AllOK = TRUE;
				for( DWORD j=pos; j<this->nextStartSize + size; j+=192 ){
					//前回の残りチェック
					if( j < this->nextStartSize ){
						if( this->nextStartBuff[j] != 0x47 ){
							AllOK = FALSE;
							break;
						}
					}else{
						if( data[j-this->nextStartSize] != 0x47 ){
							AllOK = FALSE;
							break;
						}
					}
				}
				if( AllOK == TRUE ){
					*offset = pos;
					*packetSize = 192;
					return TRUE;
				}
			}
		}else{
			//今回のデータ部分
			if( data[pos-this->nextStartSize] == 0x47 ){
				BOOL AllOK = TRUE;
				for( DWORD j=pos; j<this->nextStartSize + size; j+=192 ){
					if( data[j-this->nextStartSize] != 0x47 ){
						AllOK = FALSE;
						break;
					}
				}
				if( AllOK == TRUE ){
					*offset = pos;
					*packetSize = 192;
					return TRUE;
				}
			}
		}
	}
	//204バイト単位かチェック
	for( DWORD pos = 0; pos<maxCheckSize; pos++ ){
		if( pos < this->nextStartSize ){
			//前回の残りチェック
			if( this->nextStartBuff[pos] == 0x47 ){
				BOOL AllOK = TRUE;
				for( DWORD j=pos; j<this->nextStartSize + size; j+=204 ){
					//前回の残りチェック
					if( j < this->nextStartSize ){
						if( this->nextStartBuff[j] != 0x47 ){
							AllOK = FALSE;
							break;
						}
					}else{
						if( data[j-this->nextStartSize] != 0x47 ){
							AllOK = FALSE;
							break;
						}
					}
				}
				if( AllOK == TRUE ){
					*offset = pos;
					*packetSize = 204;
					return TRUE;
				}
			}
		}else{
			//今回のデータ部分
			if( data[pos-this->nextStartSize] == 0x47 ){
				BOOL AllOK = TRUE;
				for( DWORD j=pos; j<this->nextStartSize + size; j+=204 ){
					if( data[j-this->nextStartSize] != 0x47 ){
						AllOK = FALSE;
						break;
					}
				}
				if( AllOK == TRUE ){
					*offset = pos;
					*packetSize = 204;
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

//入力バッファを188バイト単位のTSに変換し、188の倍数になるようにそろえる
//戻り値：
// TRUE（成功）、FALSE（失敗）
//引数：
// inData			[IN]入力TSデータ
// inSize			[IN]inDataのサイズ（BYTE単位）
// outData			[OUT]188バイトに整列したバッファ（呼び出し元でdeleteする必要あり）
// outSize			[OUT]outDataのサイズ（BYTE単位）
BOOL CPacketInit::GetTSData(
	BYTE* inData,
	DWORD inSize,
	BYTE** outData,
	DWORD* outSize
)
{
	if( inData == NULL || inSize == 0 || outData == NULL || outSize == NULL ){
		this->nextStartSize = 0;
		return FALSE;
	}

	DWORD offset = 0;
	DWORD packetSize = 0;
	if( CheckSync(inData, inSize, &offset, &packetSize) == FALSE ){
		this->nextStartSize = 0;
		return FALSE;
	}

	*outSize = 188 * (((this->nextStartSize + inSize)-offset)/packetSize);
	*outData = new BYTE[*outSize];

	if( packetSize == 188 ){
		DWORD copyOffset = 0;
		DWORD copySize = 0;
		if( offset < this->nextStartSize ){
			copyOffset = this->nextStartSize - offset;
			if(*outSize == 0){
				// 出力できるパケットがないので断片として取り込む
				memmove( this->nextStartBuff, this->nextStartBuff + offset, copyOffset);
				memcpy( this->nextStartBuff + copyOffset, inData, inSize);
				this->nextStartSize = copyOffset + inSize;
			}
			else {
				copySize = *outSize-copyOffset;

				memcpy( *outData, this->nextStartBuff + offset, copyOffset);
				memcpy( (*outData) + copyOffset, inData, copySize);

				this->nextStartSize = inSize - copySize;
				if( this->nextStartSize > 0 ){
					memcpy( this->nextStartBuff, inData+copySize, this->nextStartSize);
				}
			}
		}else{
			copyOffset = offset - this->nextStartSize;
			copySize = *outSize+copyOffset;

			memcpy( (*outData), inData + copyOffset, *outSize);

			this->nextStartSize = inSize - copySize;
			if( this->nextStartSize > 0 ){
				memcpy( this->nextStartBuff, inData+copySize, this->nextStartSize);
			}
		}
	}else{
		if( this->nextStartSize + inSize > this->copyBuffSize ){
			SAFE_DELETE_ARRAY(this->copyBuff);
			this->copyBuffSize = (this->nextStartSize + inSize)*2;
			this->copyBuff = new BYTE[this->copyBuffSize];
		}
		DWORD buffSize = 0;
		if( this->nextStartSize > 0 ){
			memcpy(this->copyBuff, this->nextStartBuff, this->nextStartSize);
			buffSize += this->nextStartSize;
		}
		memcpy(this->copyBuff + buffSize, inData, inSize);
		buffSize += inSize;

		DWORD copyPos = 0;
		for( DWORD i=offset; i<buffSize; i+=packetSize){
			memcpy( (*outData) + copyPos, this->copyBuff + i, 188);
			copyPos += 188;
		}
		this->nextStartSize = (buffSize-offset)%packetSize;
		if( this->nextStartSize > 0 ){
			memcpy(this->nextStartBuff, this->copyBuff + (buffSize-this->nextStartSize), this->nextStartSize);
		}
	}
	return TRUE;
}
