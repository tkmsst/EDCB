#include "StdAfx.h"
#include "TSBuffUtil.h"

CTSBuffUtil::CTSBuffUtil(void)
{
	this->lastPID = 0xFFFF;
	this->lastCounter = 0xFF;

	this->creatingBuff = NULL;
	this->lastGetBuff = NULL;

	this->duplicateFlag = FALSE;
}

CTSBuffUtil::~CTSBuffUtil(void)
{
	Clear();
	SAFE_DELETE(this->lastGetBuff);
}

void CTSBuffUtil::Clear()
{
	for(size_t i=0; i<this->packetList.size(); i++ ){
		SAFE_DELETE(this->packetList[i]);
	}
	this->packetList.clear();

	this->lastPID = 0xFFFF;
	this->lastCounter = 0xFF;

	SAFE_DELETE(this->creatingBuff);
}

BOOL CTSBuffUtil::CheckCounter(CTSPacketUtil* tsPacket)
{
	if( tsPacket->PID == 0x1FFF ){
		//NULLパケット時は意味なし
		this->duplicateFlag = FALSE;
		return TRUE;
	}
	if( this->lastPID != 0xFFFF || this->lastCounter != 0xFF ){
		if( this->lastPID != tsPacket->PID ){
			//PID変更されたので不連続
			this->duplicateFlag = FALSE;
			return FALSE;
		}else{
			if( tsPacket->adaptation_field_control == 0x00 || tsPacket->adaptation_field_control == 0x02 ){
				//ペイロードが存在しない場合は意味なし
				this->duplicateFlag = FALSE;
				if( tsPacket->adaptation_field_control == 0x02 || tsPacket->adaptation_field_control == 0x03 ){
					if(tsPacket->discontinuity_indicator == 1){
						//不連続の判定が必要
						return FALSE;
					}else{
						return TRUE;
					}
				}else{
					return TRUE;
				}
			}
			if( this->lastCounter == tsPacket->continuity_counter ){
				if( tsPacket->adaptation_field_control == 0x01 || tsPacket->adaptation_field_control == 0x03 ){
					if( this->duplicateFlag == FALSE ){
						//重送？一応連続と判定
						this->duplicateFlag = TRUE;
						if( tsPacket->adaptation_field_control == 0x02 || tsPacket->adaptation_field_control == 0x03 ){
							if(tsPacket->discontinuity_indicator == 1){
								//不連続の判定が必要
								return FALSE;
							}else{
								return TRUE;
							}
						}else{
							return TRUE;
						}
					}else{
						//前回重送と判断してるので不連続
						this->duplicateFlag = FALSE;
						return FALSE;
					}
				}
			}
			if( this->lastCounter+1 != tsPacket->continuity_counter ){
				if( this->lastCounter != 0x0F && tsPacket->continuity_counter != 0x00 ){
					//カウンターが飛んだので不連続
					return FALSE;
				}
			}
		}
	}
	return TRUE;
}

DWORD CTSBuffUtil::Add188TS(CTSPacketUtil* tsPacket)
{
	if( tsPacket == NULL ){
		return FALSE;
	}

	//カウンターチェック
	if( CheckCounter(tsPacket) == FALSE ){
		Clear();
	}
	//スクランブルのチェック
	if( tsPacket->transport_scrambling_control != 0 ){
		//スクランブルパケットなので解析できない
		Clear();
		return ERR_NOT_SUPPORT;
	}

	if( this->lastPID == 0xFFFF && this->lastCounter == 0xFF ){
		//初回
		if( tsPacket->payload_unit_start_indicator == 1 ){
			if( tsPacket->data_byteSize < 3 ){
				//サイズが小さすぎる
				return FALSE;
			}
			if(tsPacket->data_byte[0] == 0x00 && tsPacket->data_byte[1] == 0x00 && tsPacket->data_byte[2] == 0x01){
				//PES
				return ERR_NOT_SUPPORT;
			}else{
				//PSI
				this->lastPID = tsPacket->PID;
				this->lastCounter = tsPacket->continuity_counter;
				return AddSectionBuff(tsPacket);
			}
		}else{
			//スタート位置ではない
			return ERR_ADD_NEXT;
		}
	}else{
		this->lastPID = tsPacket->PID;
		this->lastCounter = tsPacket->continuity_counter;
		return AddSectionBuff(tsPacket);
	}

}

BOOL CTSBuffUtil::GetSectionBuff(BYTE** sectionData, WORD* dataSize)
{
	SAFE_DELETE(lastGetBuff);
	if( packetList.size() == 0 ){
		return FALSE;
	}

	lastGetBuff = packetList[0];
	packetList.erase(packetList.begin());

	*sectionData = lastGetBuff->data;
	*dataSize = lastGetBuff->dataSize;

	return TRUE;
}

DWORD CTSBuffUtil::AddSectionBuff(CTSPacketUtil* tsPacket)
{
	if( tsPacket == NULL ){
		return FALSE;
	}
	if( tsPacket->data_byteSize == 0 || tsPacket->data_byte == NULL ){
		return ERR_ADD_NEXT;
	}
	if( tsPacket->payload_unit_start_indicator != 1 && creatingBuff == NULL ){
		return ERR_ADD_NEXT;
	}

	BYTE readSize = 0;
	if( tsPacket->payload_unit_start_indicator == 1 ){
		BOOL addBuff = FALSE;
		BYTE pointer_field = tsPacket->data_byte[0];
		readSize++;
		if( pointer_field != 0 ){
			//マルチセクション
			if( creatingBuff != NULL ){
				if( creatingBuff->dataSize - creatingBuff->copySize == pointer_field ){
					memcpy(creatingBuff->data + creatingBuff->copySize, tsPacket->data_byte + readSize, pointer_field);
					creatingBuff->copySize += pointer_field;
					packetList.push_back(creatingBuff);
					creatingBuff = NULL;
					addBuff = TRUE;
				}else{
					//サイズがおかしいのでクリア
					_OutputDebugString(L"multi section size err");
					SAFE_DELETE(creatingBuff);
				}
			}
		}
		readSize+=pointer_field;

		if( readSize + 3 > tsPacket->data_byteSize ){
			//サイズが小さすぎる
			_OutputDebugString(L"psi size err");
			if( addBuff == TRUE ){
				return TRUE;
			}else{
				return FALSE;
			}
		}

		SECTION_BUFF* buff = new SECTION_BUFF;
		creatingBuff = buff;
		buff->dataSize = (((WORD)tsPacket->data_byte[readSize+1]&0x0F) << 8 | tsPacket->data_byte[readSize+2]) + 3;
		buff->data = new BYTE[buff->dataSize];

//		_OutputDebugString(L"need size 0x%04x %d\r\n", tsPacket->PID, buff->dataSize);

		if( buff->dataSize <= tsPacket->data_byteSize - readSize ){
			buff->copySize = buff->dataSize;
		}else{
			buff->copySize = tsPacket->data_byteSize - readSize;
		}

		memcpy( buff->data, tsPacket->data_byte+readSize, buff->copySize );

		if( buff->copySize == buff->dataSize ){
			//このパケットだけで完結
			packetList.push_back(creatingBuff);
			creatingBuff = NULL;
			return TRUE;
		}else{
			//次のパケット必要
			if( addBuff == TRUE ){
				return TRUE;
			}else{
				return ERR_ADD_NEXT;
			}
		}
	}else{
		//複数パケットにまたがっている
		WORD copySize = 0;
		WORD needSize = creatingBuff->dataSize - creatingBuff->copySize;

		if( needSize <= tsPacket->data_byteSize ){
			copySize = needSize;
		}else{
			copySize = tsPacket->data_byteSize;
		}

		memcpy( creatingBuff->data + creatingBuff->copySize, tsPacket->data_byte, copySize );

		creatingBuff->copySize += copySize;
		if( creatingBuff->dataSize == creatingBuff->copySize ){
			packetList.push_back(creatingBuff);
			creatingBuff = NULL;
			return TRUE;
		}else{
			return ERR_ADD_NEXT;
		}
	}
}

