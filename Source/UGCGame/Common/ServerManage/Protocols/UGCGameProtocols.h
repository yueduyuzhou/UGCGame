#pragma once

#include "CoreMinimal.h"
#include "Protocols/SimpleNetProtocols.h"
#include "SimpleProtocolsDefinition.h"

DEFINITION_SIMPLE_PROTOCOLS(C2D_DATA_REQUEST, 100);
DEFINITION_SIMPLE_PROTOCOLS(D2C_DATA_RESPONSE, 101);

DEFINITION_SIMPLE_PROTOCOLS(C2D_UGC_MAP_ELEMENT_INFO_REQUEST, 150);	/* int32 MapID */
DEFINITION_SIMPLE_PROTOCOLS(D2C_UGC_MAP_ELEMENT_INFO_RESPONSE, 151);	/* int32 MapID, int32[], float[] */

DEFINITION_SIMPLE_PROTOCOLS(C2D_UGC_MAP_INFO_REQUEST, 152);
DEFINITION_SIMPLE_PROTOCOLS(D2C_UGC_MAP_INFO_RESPONSE, 153);	/*  */