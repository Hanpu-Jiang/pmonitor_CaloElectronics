// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME saHCal_dict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "saHCal.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace {
  void TriggerDictionaryInitialization_saHCal_dict_Impl() {
    static const char* headers[] = {
"saHCal.h",
nullptr
    };
    static const char* includePaths[] = {
"/cvmfs/sphenix.sdcc.bnl.gov/gcc-12.1.0/release/release_new/new.6/include",
"/cvmfs/sphenix.sdcc.bnl.gov/gcc-12.1.0/release/release_new/new.6/include",
"/cvmfs/sphenix.sdcc.bnl.gov/gcc-12.1.0/opt/sphenix/core/root-6.26.06.p01/include/",
"/gpfs/mnt/gpfs02/sphenix/user/hanpuj/standalone/pmonitor_CaloElectronics/macro/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "saHCal_dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "saHCal_dict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "saHCal.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"find_hot_tower", payloadCode, "@",
"frequency_threshold", payloadCode, "@",
"get_runtype", payloadCode, "@",
"index_packet_emcal", payloadCode, "@",
"index_packet_ihcal", payloadCode, "@",
"index_packet_mbd", payloadCode, "@",
"index_packet_ohcal", payloadCode, "@",
"index_packet_sepd", payloadCode, "@",
"index_packet_zdc", payloadCode, "@",
"length_packet_emcal", payloadCode, "@",
"length_packet_ihcal", payloadCode, "@",
"length_packet_mbd", payloadCode, "@",
"length_packet_ohcal", payloadCode, "@",
"length_packet_sepd", payloadCode, "@",
"length_packet_zdc", payloadCode, "@",
"mean_threshold", payloadCode, "@",
"n_packet_emcal", payloadCode, "@",
"n_packet_ihcal", payloadCode, "@",
"n_packet_mbd", payloadCode, "@",
"n_packet_ohcal", payloadCode, "@",
"n_packet_sepd", payloadCode, "@",
"n_packet_zdc", payloadCode, "@",
"n_sample", payloadCode, "@",
"nchannel_packet_emcal", payloadCode, "@",
"nchannel_packet_ihcal", payloadCode, "@",
"nchannel_packet_mbd", payloadCode, "@",
"nchannel_packet_ohcal", payloadCode, "@",
"nchannel_packet_sepd", payloadCode, "@",
"nchannel_packet_zdc", payloadCode, "@",
"output_hot_tower", payloadCode, "@",
"process_event", payloadCode, "@",
"rms_threhold", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("saHCal_dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_saHCal_dict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_saHCal_dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_saHCal_dict() {
  TriggerDictionaryInitialization_saHCal_dict_Impl();
}
