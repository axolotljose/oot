/*
 * File: z_en_younglink.c
 * Overlay: ovl_En_YoungLink
 * Description: Young Link NPC Companion
 */

#include "z_en_younglink.h"

#include "array_count.h"
#include "gfx.h"
#include "gfx_setupdl.h"
#include "printf.h"
#include "rand.h"
#include "sfx.h"
#include "stack_pad.h"
#include "sys_matrix.h"
#include "z_lib.h"
#include "play_state.h"
#include "player.h"

#define FLAGS (ACTOR_FLAG_ATTENTION_ENABLED | ACTOR_FLAG_FRIENDLY)

void EnYoungLink_Init(Actor* thisx, PlayState* play);
void EnYoungLink_Destroy(Actor* thisx, PlayState* play);
void EnYoungLink_Update(Actor* thisx, PlayState* play);
void EnYoungLink_Draw(Actor* thisx, PlayState* play);

void EnYoungLink_IdleStand(EnYoungLink* this, PlayState* play);

ActorProfile En_YoungLink_Profile = {
    /**/ ACTOR_EN_YOUNGLINK,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_LINK_CHILD,
    /**/ sizeof(EnYoungLink),
    /**/ EnYoungLink_Init,
    /**/ EnYoungLink_Destroy,
    /**/ EnYoungLink_Update,
    /**/ EnYoungLink_Draw,
};

void EnYoungLink_SetupAction(EnYoungLink* this, EnYoungLinkActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void EnYoungLink_IdleStand(EnYoungLink* this, PlayState* play) {
    // Placeholder: Just stand there doing nothing
    // No interaction yet - purely visual
}

void EnYoungLink_Init(Actor* thisx, PlayState* play) {
    EnYoungLink* this = (EnYoungLink*)thisx;

    // Initialize actor shape and shadow
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);

    // Initialize skeletal animation with child Link skeleton
    // Using stand animation from gameplay_keep
    SkelAnime_InitFlex(play, &this->skelAnime, &gLinkChildSkel, 
                       &gLinkChildStandAnim, this->jointTable, this->morphTable, 17);

    // Basic actor setup
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    Actor_SetScale(&this->actor, 1.0f);
    this->actor.attentionRangeType = ATTENTION_RANGE_3;  // Default range
    
    // Blink system
    this->eyeIndex = 0;  // Open eyes
    this->blinkTimer = 20;

    // Set initial action
    EnYoungLink_SetupAction(this, EnYoungLink_IdleStand);
}

void EnYoungLink_Destroy(Actor* thisx, PlayState* play) {
    // No cleanup needed for now
}

void EnYoungLink_Update(Actor* thisx, PlayState* play) {
    EnYoungLink* this = (EnYoungLink*)thisx;

    // Update animation
    SkelAnime_Update(&this->skelAnime);

    // Update background collision
    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, UPDBGCHECKINFO_FLAG_2);

    // Call action function
    this->actionFunc(this, play);
}

void EnYoungLink_Draw(Actor* thisx, PlayState* play) {
    EnYoungLink* this = (EnYoungLink*)thisx;

    OPEN_DISPS(play->state.gfxCtx, "../z_en_younglink.c", 150);

    Gfx_SetupDL_37Opa(play->state.gfxCtx);

    // Draw skeleton animation
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, 
                          this->skelAnime.dListCount, NULL, NULL, this);

    CLOSE_DISPS(play->state.gfxCtx, "../z_en_younglink.c", 160);
}
