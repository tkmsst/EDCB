#include "StdAfx.h"
#include "Descriptor.h"
#include "UnkownDesc.h"

CDescriptor::CDescriptor(void)
{
}

CDescriptor::~CDescriptor(void)
{
}

void CDescriptor::Clear(vector<DESCRIPTOR_DATA*>* descriptorList)
{
	if( descriptorList != NULL ){
		vector<DESCRIPTOR_DATA*>::iterator itr;
		for( itr = descriptorList->begin(); itr != descriptorList->end(); itr++ ){
			SAFE_DELETE(*itr);
		}
		descriptorList->clear();
	}
}

BOOL CDescriptor::Decode( BYTE* data, DWORD dataSize, vector<DESCRIPTOR_DATA*>* descriptorList, DWORD* decodeReadSize )
{
	if( data == NULL || dataSize == 0 || descriptorList == NULL ){
		return FALSE;
	}
	DWORD decodeSize = 0;
	while( decodeSize < dataSize ){
		CUnkownDesc unknown;
		DWORD readSize = 0;
		if( unknown.Decode( data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
			Clear(descriptorList);
			return FALSE;
		}

		DESCRIPTOR_DATA* item = new DESCRIPTOR_DATA;
		switch(unknown.descriptor_tag){
			case 0x09:
				{
					item->CA = new CCADesc;
					if( item->CA->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xC4:
				{
					item->audioComponent = new CAudioComponentDesc;
					if( item->audioComponent->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0x2A:
				{
					item->AVCTimingHRD = new CAVCTimingHRDDesc;
					if( item->AVCTimingHRD->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0x28:
				{
					item->AVCVideo = new CAVCVideoDesc;
					if( item->AVCVideo->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xDB:
				{
					item->boardInfo = new CBoardInfoDesc;
					if( item->boardInfo->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0x47:
				{
					item->bouquetName = new CBouquetNameDesc;
					if( item->bouquetName->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xD8:
				{
					item->broadcasterName = new CBroadcasterNameDesc;
					if( item->broadcasterName->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0x53:
				{
					item->CAIdentifier = new CCAIdentifierDesc;
					if( item->CAIdentifier->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0x50:
				{
					item->component = new CComponentDesc;
					if( item->component->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xD9:
				{
					item->componentGroup = new CComponentGroupDesc;
					if( item->componentGroup->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xDD:
				{
					item->connectedTransmission = new CConnectedTransmissionDesc;
					if( item->connectedTransmission->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xDE:
				{
					item->contentAvailability = new CContentAvailabilityDesc;
					if( item->contentAvailability->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0x54:
				{
					item->content = new CContentDesc;
					if( item->content->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0x49:
				{
					item->countryAvailability = new CCountryAvailabilityDesc;
					if( item->countryAvailability->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xFD:
				{
					item->dataComponent = new CDataComponentDesc;
					if( item->dataComponent->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xC7:
				{
					item->dataContent = new CDataContentDesc;
					if( item->dataContent->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xC1:
				{
					item->digitalCopyCtrl = new CDigitalCopyCtrlDesc;
					if( item->digitalCopyCtrl->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xFC:
				{
					item->emergencyInfo = new CEmergencyInfoDesc;
					if( item->emergencyInfo->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xD6:
				{
					item->eventGroup = new CEventGroupDesc;
					if( item->eventGroup->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xCE:
				{
					item->extendedBroadcaster = new CExtendedBroadcasterDesc;
					if( item->extendedBroadcaster->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0x4E:
				{
					item->extendedEvent = new CExtendedEventDesc;
					if( item->extendedEvent->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xC0:
				{
					item->hierarchicalTransmission = new CHierarchicalTransmissionDesc;
					if( item->hierarchicalTransmission->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xC5:
				{
					item->hyperlink = new CHyperlinkDesc;
					if( item->hyperlink->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xDC:
				{
					item->LDTLinkage = new CLDTLinkageDesc;
					if( item->LDTLinkage->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0x4A:
				{
					item->linkage = new CLinkageDesc;
					if( item->linkage->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0x58:
				{
					item->localTimeOffset = new CLocalTimeOffsetDesc;
					if( item->localTimeOffset->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xCF:
				{
					item->logoTransmission = new CLogoTransmissionDesc;
					if( item->logoTransmission->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0x51:
				{
					item->mosaic = new CMosaicDesc;
					if( item->mosaic->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xC2:
				{
					item->networkIdentification = new CNetworkIdentification;
					if( item->networkIdentification->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0x40:
				{
					item->networkName = new CNetworkNameDesc;
					if( item->networkName->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0x4B:
				{
					item->NVODReference = new CNVODReferenceDesc;
					if( item->NVODReference->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0x55:
				{
					item->parentalRating = new CParentalRatingDesc;
					if( item->parentalRating->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xFB:
				{
					item->partialReception = new CPartialReceptionDesc;
					if( item->partialReception->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0x63:
				{
					item->partialTransportStream = new CPartialTransportStreamDesc;
					if( item->partialTransportStream->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xC3:
				{
					item->partialTSTime = new CPartialTSTimeDesc;
					if( item->partialTSTime->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0x43:
				{
					item->satelliteDeliverySys = new CSatelliteDeliverySysDesc;
					if( item->satelliteDeliverySys->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xD5:
				{
					item->series = new CSeriesDesc;
					if( item->series->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0x48:
				{
					item->service = new CServiceDesc;
					if( item->service->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xE0:
				{
					item->serviceGroup = new CServiceGroupDesc;
					if( item->serviceGroup->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0x41:
				{
					item->serviceList = new CServiceListDesc;
					if( item->serviceList->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0x4D:
				{
					item->shortEvent = new CShortEventDesc;
					if( item->shortEvent->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xD7:
				{
					item->SIParameter = new CSIParameterDesc;
					if( item->SIParameter->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xDA:
				{
					item->SIPrime_ts = new CSIPrime_tsDesc;
					if( item->SIPrime_ts->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0x52:
				{
					item->streamIdentifier = new CStreamIdentifierDesc;
					if( item->streamIdentifier->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0x42:
				{
					item->stuffing = new CStuffingDesc;
					if( item->stuffing->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xFE:
				{
					item->systemManagement = new CSystemManagementDesc;
					if( item->systemManagement->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xC6:
				{
					item->targetRegion = new CTargetRegionDesc;
					if( item->targetRegion->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xFA:
				{
					item->terrestrialDeliverySys = new CTerrestrialDeliverySysDesc;
					if( item->terrestrialDeliverySys->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0x4F:
				{
					item->timeShiftedEvent = new CTimeShiftedEventDesc;
					if( item->timeShiftedEvent->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0x4C:
				{
					item->timeShiftedService = new CTimeShiftedServiceDesc;
					if( item->timeShiftedService->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xCD:
				{
					item->TSInfo = new CTSInfoDesc;
					if( item->TSInfo->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xC8:
				{
					item->videoDecodeCtrl = new CVideoDecodeCtrlDesc;
					if( item->videoDecodeCtrl->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			case 0xC9:
				{
					item->downloadContent = new CDownloadContentDesc;
					if( item->downloadContent->Decode(data + decodeSize, dataSize-decodeSize, &readSize ) == FALSE ){
						SAFE_DELETE(item);
						Clear(descriptorList);
						return FALSE;
					}else{
						descriptorList->push_back(item);
					}
				}
				break;
			default:
//				_OutputDebugString(L"++CDescriptor:: err UnknownDescriptor 0x%02X\r\n", unknown.descriptor_tag);
				SAFE_DELETE(item);
				break;
		}
		decodeSize += readSize;
	}
	if( decodeReadSize != NULL ){
		*decodeReadSize = dataSize;
	}
	return TRUE;
}
