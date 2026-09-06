#ifndef GUARD_FIELD_RUNTIME_FLAGS_H
#define GUARD_FIELD_RUNTIME_FLAGS_H

#include "global.h"

struct FieldNestedFlagContainer;
struct FieldNestedFlagRecord;
struct FieldNestedFlagRequest;
struct ScriptExecutionState;

#define field_clear_nested_flags_1788 sub_80F7590
#define field_set_nested_flags_1788 sub_80F75B4
#define field_wait_for_nested_state_179d_clear sub_80F7D3C
#define field_wait_for_runtime_flag_10_clear sub_80F7E84
#define field_set_indexed_runtime_byte_350 sub_80F7EA4
#define field_set_mode_3a5_and_mark_pending sub_81069B4
#define field_set_nested_flags_1788_and_1798 sub_80F75D8
#define field_clear_record_flag_0200_when_nested_flag_4000 sub_80F8C60
#define field_submit_nested_request_and_mark_pending sub_80F7770
#define field_runtime_test_flag_10 sub_8082B00

void field_clear_nested_flags_1788(u32 mask);
void field_set_nested_flags_1788(u32 mask);
s32 field_wait_for_nested_state_179d_clear(
    struct FieldNestedFlagContainer* container,
    struct ScriptExecutionState* state);
s32 field_wait_for_runtime_flag_10_clear(
    void* context, struct ScriptExecutionState* state);
s32 field_set_indexed_runtime_byte_350(
    void* context, void* state, const s32* arguments);
void field_set_mode_3a5_and_mark_pending(s8 mode);
void field_set_nested_flags_1788_and_1798(u32 mask);
void field_clear_record_flag_0200_when_nested_flag_4000(
    struct FieldNestedFlagContainer* container,
    struct FieldNestedFlagRecord* record);
void field_submit_nested_request_and_mark_pending(
    struct FieldNestedFlagRequest* request);
s32 field_runtime_test_flag_10(void);

#endif
